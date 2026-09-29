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

