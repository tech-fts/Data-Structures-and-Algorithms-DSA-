#include <stdio.h>
#include "test_buffer.c"

int main(){
    UNITY_BEGIN();
    RUN_TEST(test_save_message_once);
    RUN_TEST(test_save_message_multiple);
    RUN_TEST(test_send_message_first);
    RUN_TEST(test_send_message_on_empty_queue_does_not_crash);
    return UNITY_END();
}