#include <stdio.h>
#include "billing.h"

struct Person test_user[2] = {
    {userName : "aung aung", password : "password123"},
    {userName : "john_doe", password : "pass456"}
};

void test_user_login_success(void){
    int result = login(test_user, "john_doe", "pass456");
    TEST_ASSERT_EQUAL_INT(0, result);
}

void test_user_login_success_sec(void){
    int result  = login(test_user, "john_doe", "pass456");

    TEST_ASSERT_EQUAL_INT(1,result);
}

void test_user_login_failed(void){
    int result = login(test_user, "aung aung", "password123");

    TEST_ASSERT_EQUAL_INT(-1, result);
}

void test_meter_usage_first(void){
    struct Meter m  = {
        .units_consumed = 10.1f
    };
    int index =0;

    struct Person people = meter_usageCalculation(m, test_user, index);
    TEST_ASSERT_EQUAL_FLOAT(50.0f, people.total_usage);
}

void test_meter_usage_zero(void){
    struct  Meter m = 
    {
        .units_consumed = 0.0f
    };
    int index = 0;

    struct Person people = meter_usageCalculation(m, test_user, index);
    TEST_ASSERT_EQUAL_FLOAT(00.00f, people.total_usage);
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(test_user_login_success);
    RUN_TEST(test_user_login_success_sec);
    RUN_TEST(test_user_login_failed);
    RUN_TEST(test_meter_usage_first);
    RUN_TEST(test_meter_usage_zero);
    return UNITY_END();
}