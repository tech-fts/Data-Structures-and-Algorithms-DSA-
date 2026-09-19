#include <stdio.h>
#include "buffer.h"
#include "buffer.c"

int main(){
    Buffernode* txt_buffer = NULL;

    printf("start save message for system");
    save_message(&txt_buffer, "factory/robot1/temp","{\"temp\": 42.8}", 1);
    save_message(&txt_buffer, "facroty/robot2/temp", "{\"temp\": 32.5}", 1);
    save_message(&txt_buffer, "factory/conveyor/rpm", "{\"rpm\": 1200}", 0);

    printf("network restored, send message to network");

    while(txt_buffer != NULL){
        send_message(&txt_buffer);
    }

    prinf("message sending process is finished");
    
    return 0;
}