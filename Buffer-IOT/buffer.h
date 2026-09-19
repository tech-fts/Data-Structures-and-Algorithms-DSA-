#ifndef BUFFER_H
#define  BUFFER_H

#include <stdint.h>

typedef struct{
    uint32_t message_id;
    uint8_t qos_level;
    char topic[65];
    char payload[256];
}Mqtt_t;

typedef struct{
    Mqtt_t message;
    struct Buffernode* next;
}Buffernode;

uint32_t global_message_counter = 1001;

void save_message(Buffernode** head, const char* topic, const char* payload, uint8_t qos);
void send_message(Buffernode** head);

#endif