#include <ros/ros.h>
#include <std_msgs/Int32.h>

int main(int argc, char **argv) {
    ros::init(argc, argv, "int_publisher");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<std_msgs::Int32>("int_topic_1", 1000);
    ros::Rate loop_rate(10); // 0.1초 간격

    while (ros::ok()) {
        std_msgs::Int32 msg;
        msg.data = 1;

        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
