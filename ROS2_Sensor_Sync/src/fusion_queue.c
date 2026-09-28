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

    if(buffer == NULL){
        buffer->head = newNode;
        buffer->tail = newNode;
        return;
    }
    
    if(timestamp >= buffer->head->time_stamp){
        newNode->next = buffer->head;
        buffer->head->prev = newNode;
        buffer->head = newNode;

        buffer_remove(buffer);
        return;
    }

    if(timestamp <= buffer->tail->time_stamp){
        newNode->prev = buffer->tail;
        buffer->tail->next = newNode;
        buffer->tail = newNode;

        buffer_remove(buffer);
        return;
    }

    Datapocket* current = buffer->head;

    if(current != NULL  && current->time_stamp > timestamp){
        current = current->next;
    }

    newNode->next = current;
    newNode->prev = current->next;

    if(current->next != NULL){
        current->prev->next = newNode;
    }

    current->prev = newNode;

    buffer_remove(buffer);
}