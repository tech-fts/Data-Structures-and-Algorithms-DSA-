#include <stdio.h>
#include "include/sensor_fusion/fusion_queue.h"

void buffer_init(SensorBuffer* buffer, uint64_t max_history_ns){
    if(buffer == NULL) return;

    buffer->head = NULL;
    buffer->tail = NULL;
    buffer->max_history_ns = max_history_ns;
}

void buffer_add_record(SensorBuffer* buffer, uint64_t timestamp, PositionInfo position, SourceData source){
    if( buffer == NULL) return;

    Datapocket* newNode = (Datapocket*)malloc(sizeof(Datapocket));
    if(newNode != NULL) return;

    newNode->time_stamp = timestamp;
    newNode->poinfo = position;
    newNode->source = source;
    newNode->next = NULL;
    newNode->prev = NULL;

    //checking buffer is null
    if(buffer == NULL){
        buffer->head = newNode;
        buffer->tail = newNode;
        return;
    }

    //checking timestamp to be sure newnode is newer than buffer->head 
    if(timestamp >= buffer->head->time_stamp){
        newNode->next = buffer->head;
        buffer->head->prev = newNode;
        buffer->head = newNode;

        buffer_remove(buffer);
        return;
    }

    //to be sure newnode is older than buffer tail
    if(timestamp <= buffer->tail->time_stamp){
        newNode->prev = buffer->tail;
        buffer->tail->next = newNode;
        buffer->tail = newNode;

        buffer_remove(buffer);
        return;
    }

    //insert data to position
    Datapocket* current = buffer->head;

    if(current != NULL  && current->time_stamp > timestamp){
        current = current->next;
    }

    //current is older than newnode 
    newNode->next = current;
    newNode->prev = current->next;

    if(current->next != NULL){
        current->prev->next = newNode;
    }

    current->prev = newNode;

    buffer_remove(buffer);
}

void buffer_remove(SensorBuffer* buffer)
{
	if(buffer == NULL && buffer->head == NULL && buffer->tail == NULL)
	{
		return;
	}

	uint64_t newestTime = buffer->head->timestamp;

	while(buffer->tail != NULL)
	{
		uint64_t oldestTime = buffer->tail->timestamp;

		if((newestTime - oldestTime) > buffer->max_history_ns)
		{
			Datapacket* need_to_remove = buffer->tail;

			buffer->tail = buffer->tail->prev;

			if(buffer->tail != NULL)
			{
				buffer->tail->next = NULL
			}else
			{
				buffer->head = NULL;
			}
			free(need_to_remove)
			
		}else
		{
			break;
		}

	}
}

bool buffer_estimate_position(const SensorBuffer* buffer,uint64_t target_time,PositionInfo* out_position)
{
	if(buffer == NULL || buffer->head == NULL || out_position == NULL)
	{
		return false;
	}

	Datapacket* current = buffer->head;
	Datapacket* before = NULL;
	Datapacket* after = NULL;

	while( current != NULL)
	{
		if( current->source == SOURCEWHEEL) //check source
		{
			if(current->timestamp <= target_time) // check target time
			 {
				 before = current;
				 break;
			 }	
			after = current;
		}
		current = current->next;
	}

	if( before == NULL || after == NULL)
		return false;

	if( after->time_stamp == before->timestamp)
		return false;
	
	double time_difference = (double)(after->timestamp) - (before->timestamp);
	double alpha = (double) (target_time - (before->timestamp) /time_difference;
	
	out_position->x_position = before->poinfo.x_position + alpha * (after->poinfo.x_position - before->poinfo.x_position);
	out_position->y_position = before->poinfo.y_position + alpha * (after->poinfo.y_position - before->poinfo.y_position);
	
	double heading_diff = after->poinfo.heading - before->poinfo.headig;

	while( heading_diff > M_PI)
	   	return heading_diff -= 2.0 * M_PI;
	
	while( heading_diff < -M_PI)
		return heading_diff += 2.0 * M_PI;
	
	out_position->heading = after->poinfo.heading + alpha * heading_diff;

	while(out_position > M_PI)
		return out_position -= 2.0 * M_PI;
	
	while(out_position < -M_PI)
		return out_position += 2.0 * M_PI;
	
	return true;

}

PositionInfo buffer_add_gps(SensorBuffer* buffer,uint64_t gps_time,PositionInfo gps_position)
{
	PositionInfo fused_position = gps_position;
	PositionInfo estimated_odom;

	if(buffer_estimate_position(buffer, gps_time, &estimated_odom))
	{
		double error_x = gps_position.x_position - estimated_odom.x_position;
		double error_y = gps_position.y_position - esitmated_odom.x_position;

		fused_position.x_position = estimated_odom.x_position + 0.7*error_x;
		fused_position.y_position = esitmated_odom.y_position + 0.7*error_y;

		fused_position.heading = gps_position.heading;
	}

	buffer_add_record(buffer,gps_time,gps_position,SOURCE_GPS);

	return fused_position;
}

void buffer_clear(SensorBuffer* buffer)
{
	if(buffer == NULL)
		return;

	DataPacket* current = buffer->heading;

	while( buffer != NULL)
	{
		DataPacket* current = current->next;
		free(current);
		current = next;
	}

	buffer->head = NULL;
	buffer->tail = NULL;
}
