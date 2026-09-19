#include <stdio.h>
#include "buffer.h"

void save_message(Buffernode** head, const char* topic, const char* payload, uint8_t qos){
    Buffernode* new_node = (Buffernode*)malloc(sizeof(Buffernode));
    if(new_node == NULL){
        printf("Out of you memory");
        return;
    }

    new_node->message.message_id = global_message_counter++;
    new_node->message.qos_level = qos;
    strncpy(new_node->message.topic, topic, sizeof(new_node->message.topic)-1);
    strncpy(new_node->message.payload, payload, sizeof(new_node->message.topic) -1);
    new_node->next = NULL;

    if(*head == NULL){
        *head = new_node;
    }else{
        Buffernode* current = new_node;
        while(current->next != NULL){
            current = current->next;
        }

        current->next = new_node;
    }
    
}

void send_message(Buffernode** head){

}