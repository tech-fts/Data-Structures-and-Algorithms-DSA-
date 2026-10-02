#include "include/sensor_fusion/fusion_node.h"

#include <stdio.h>
#include <math.h>

bool fusion_init(FusionNode* node_struct, int argc, char const* const* argv)
{
    // Initialization logic for the fusion node
    if(node_struct == NULL)
    {
        return false; // Return false if the node structure is NULL
    };

    // Initialize the ROS 2 allocator
    node_struct->rcl_allocator = rcl_get_default_allocator();

    // Initialize ROS 2 support
    rclc_support_init(&node_struct->support, argc, argv, &node_struct->rcl_allocator);

    rcl_ret_t ret = rclc_support_init(&node_struct->support, argc, argv, &node_struct->rcl_allocator);
    if (ret != RCL_RET_OK)
    {
        printf("[Fusion Node] Failed to initialize ROS 2 support: %s\n", rcl_get_error_string().str);
        return false; // Return false if ROS 2 support initialization fails
    }

    //initialize the ROS 2 node
    ret = rclc_node_init_default(&node_struct->rcl_node, "fusion_node", "", &node_struct->support);
    if (ret != RCL_RET_OK)
    {
        printf("[Fusion Node] Failed to initialize ROS 2 node: %s\n", rcl_get_error_string().str);
        return false; // Return false if ROS 2 node initialization fails
    }

    node_struct->buffer = NULL; // Initialize the sensor buffer to NULL

    node_struct->buffer = (SensorBuffer*)malloc(sizeof(SensorBuffer));
    if (node_struct->buffer == NULL)
    {
        printf("[Fusion Node] Failed to allocate memory for sensor buffer.\n");
        return false; // Return false if memory allocation for the sensor buffer fails
    }

    buffer_init(node_struct->buffer, 1000000000); // Initialize the sensor buffer with a max history of 1 second (1e9 nanoseconds)

    rc =
        rclc_subscription_init_default(
            &node_struct->wheel_subscription,
            &node_struct->rcl_node,
            ROSIDL_GET_MSG_TYPE_SUPPORT(
                nav_msgs,
                msg,
                Odometry),
            "/odom");

    if (rc != RCL_RET_OK)
        return false;


    rc =
        rclc_subscription_init_default(
            &node_struct->gps_subscription,
            &node_struct->rcl_node,
            ROSIDL_GET_MSG_TYPE_SUPPORT(
                geometry_msgs,
                msg,
                PoseStamped),
            "/gps");

    if (rc != RCL_RET_OK)
        return false;


    rc =
        rclc_publisher_init_default(
            &node_struct->data_publisher,
            &node_struct->rcl_node,
            ROSIDL_GET_MSG_TYPE_SUPPORT(
                geometry_msgs,
                msg,
                PoseStamped),
            "/filtered_pose");

    if (rc != RCL_RET_OK)
        return false;

    node_struct->executor = rclc_executor_get_zero_initialized_executor();

    rc =
        rclc_executor_init(
            &node_struct->executor,
            &node_struct->support.context,
            2,
            &node_struct->rcl_allocator);

    if (rc != RCL_RET_OK)
        return false;

    rc =
        rclc_executor_add_subscription(
            &node_struct->executor,
            &node_struct->wheel_subscription,
            &node_struct->wheel_msg_buffer,
            &wheel_callback,
            ON_NEW_DATA);

    if (rc != RCL_RET_OK)
        return false;


    rc =
        rclc_executor_add_subscription(
            &node_struct->executor,
            &node_struct->gps_subscription,
            &node_struct->gps_msg_buffer,
            &gps_callback,
            ON_NEW_DATA);

    if (rc != RCL_RET_OK)
        return false;


    return true; // Return true if initialization is successful
}

int main(int argc, char const* const* argv)
{
    FusionNode node;

    if(fusion_node_init(&node, argc, argv))
    {
        printf("[Fusion Node] C-based sensor fusion node initialized successfully.\n");
        fusion_spin(&node);
    }else{
        printf("[Fusion Node] C-based sensor fusion node failed to initialize.\n");
    }

    fusion_shutdown(&node);
    return 0;
}