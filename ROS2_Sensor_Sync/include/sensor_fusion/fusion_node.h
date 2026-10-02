#ifndef FUSHION_NODE_H
#define FUSHION_NODE_H

#include <rcl\rcl.h>
#include <rclc\rclc.h>
#include <rclc\executor.h>

#include <geometry_msgs/msg/pose_stamped.h>
#include <nav_msgs/msg/odometry.h>

#include "include/sensor_fusion/fusion_queue.h"

typedef struct{
    //network communication 
    rcl_node_t rcl_node;
    rcl_allocator_t rcl_allocator;
    rclc_support_t support;
    rclc_executor_t executor;

    // listen incoming data
    rcl_subscription_t wheel_subscription;
    rcl_subscription_t gps_subscription;

    // send sensor data
    rcl_publisher_t data_publisher;

    nav_msgs__msg__Odometry wheel_msg_buffer;
    geometry_msgs__msg__PoseStamped gps_msg_buffer;

    SensorBuffer* buffer;

}Fushion_Node;

bool fushion_init(Fushion_Node* node_struct, int argc, char const* const* argv ); //already declare header file in fusion_queue.h
void fushion_remove(Fushion_Node* node_struct);
void fushion_shutdown(Fushion_Node* node_struct);

void wheel_callback(const void* msin, void* usercontext);
void gps_callback(const void* msin, void* usercontext)

#endif