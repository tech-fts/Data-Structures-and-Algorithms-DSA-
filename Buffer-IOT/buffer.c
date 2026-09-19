#include <stdio.h>
#include <string.h>
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
        Buffernode* current = *head; //bug not point to new_node
        while(current->next != NULL){
            current = current->next;
        }

        current->next = new_node;
    }
    printf("message %u save for topic%s", new_node->message.message_id, new_node->message.topic);
    
}

void send_message(Buffernode** head){
    if(*head == NULL){
        printf("empty memory nothing to send");
        return;
    }

    Buffernode* node_to_send = *head;

    printf("start message send");
    printf("message id: %u", node_to_send->message.message_id);
    printf("message topic: %s", node_to_send->message.topic);
    printf("message_payload: %s", node_to_send->message.payload);
    printf("message qos: %u", node_to_send->message.qos_level);
    prinf("message send successful");

    *head = node_to_send->next;

    free(node_to_send);

}