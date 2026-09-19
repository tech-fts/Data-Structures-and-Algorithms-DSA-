#include <stdio.h>
#include "buffer.h"

static Buffernode* test_node = NULL;

void test_save_message_once(void){
    save_message(&test_node, "factory/test/temp","{\"temp\": 42.8}", 1);

    TEST_ASSERT_NOT_NULL(test_node);
    TEST_ASSERT_EQUAL_STRING("factory/test/temp", test_node->message.topic);
    TEST_ASSERT_EQUAL_STRING("{\"temp\": 42.8}", test_node->message.payload);
    TEST_ASSERT_EQUAL_UNIT8(2, test_node->message.qos_level);
    TEST_ASSERT_EQUAL_UNIT32(1002, test_node->message.message_id);
    TEST_ASSERT_NOT_NULL(test_node->next);
}

void test_save_message_multiple(void){
    save_message(&test_node, "factory/test1/temp","{\"temp\": 2.8}", 2);
    save_message(&test_node, "factory/test2/temp","{\"temp\": 32.8}", 1);

    TEST_ASSERT_NOT_NULL(test_node);
    TEST_ASSERT_NOT_NULL(test_node->next);

    TEST_ASSERT_EQUAL_STRING("test1/temp", test_node->message.topic);
    TEST_ASSERT_EQUAL_UNIT32(1002, test_node->message.message_id);

    TEST_ASSERT_EQUAL_STRING("test2/temp", test_node->message.topic);
    TEST_ASSERT_EQUAL_UNIT32(1302, test_node->message.message_id);

    TEST_ASSERT_NOT_NULL(test_node->next);
}

void test_send_message_first(void){
    save_message(&test_node, "factory/test1/temp","{\"temp\": 2.8}", 2);
    save_message(&test_node, "factory/test2/temp","{\"temp\": 32.8}", 1);

    send_message(&test_node);

    TEST_ASSERT_NOT_NULL(test_node);
    TEST_ASSERT_EQUAL_STRING("test1/temp", test_node->message.topic);

    send_message(&test_node);

}

void test_send_message_on_empty_queue_does_not_crash(void){
    send_message(&test_node);
    TEST_ASSERT_NOT_NULL(test_node);
}
