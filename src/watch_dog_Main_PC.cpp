#include <ros/ros.h>
#include <std_msgs/Int32.h>

ros::Publisher pub;

void intCallback(const std_msgs::Int32::ConstPtr& msg) {
    if (msg->data == 1) {
        std_msgs::Int32 response_msg;
        response_msg.data = 2;
        pub.publish(response_msg);
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "int_subscriber_and_publisher");
    ros::NodeHandle nh;

    pub = nh.advertise<std_msgs::Int32>("int_topic_2", 1000);
    ros::Subscriber sub = nh.subscribe("int_topic_1", 1000, intCallback);

    ros::spin();

    return 0;
}
