#include <stdio.h>
#include "billing.h"

struct Person test_user[2] = {
    {userName : "aung aung", password : "password123"},
    {userName : "john_doe", password : "pass456"}
};

int test_user_login_success(void){
    int result = login(test_user, "john_doe", "pass456");
    TEST_ASSERT_EQUAL_INT(0, result);
}

int test_user_login_success_sec(void){
    int result  = login(test_user, "john_doe", "pass456");

    TEST_ASSERT_EQUAL_INT(1,result);
}

int test_user_login_failed(void){
    int result = login(test_user, "aung aung", "password123");

    TEST_ASSERT_EQUAL_INT(-1, result);
}

int main(){
    return 0;
}