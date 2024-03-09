#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <race/drive_values.h> // drive_values 메시지 헤더 포함

ros::Time last_msg_time; // 마지막으로 메시지를 받은 시간을 추적
ros::Publisher brake_pub; // 브레이크 메시지를 보낼 퍼블리셔

void intCallback(const std_msgs::Int32::ConstPtr& msg) {
    if (msg->data == 2) {
        ROS_INFO("Main PC 정상 동작 중");
        last_msg_time = ros::Time::now(); // 메시지를 받은 시간 업데이트
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "int_monitor_and_brake_publisher");
    ros::NodeHandle nh;

    last_msg_time = ros::Time::now(); // 초기화

    ros::Publisher pub = nh.advertise<std_msgs::Int32>("int_topic_1", 1000);
    ros::Subscriber sub = nh.subscribe("int_topic_2", 1000, intCallback);

    // race::drive_values 메시지 타입을 사용하는 퍼블리셔
    brake_pub = nh.advertise<race::drive_values>("control_value", 1000);

    ros::Rate loop_rate(10); // 0.1초 간격으로 메시지 전송

    while (ros::ok()) {
        std_msgs::Int32 msg;
        msg.data = 1;
        pub.publish(msg);

        // 마지막 메시지를 받은 이후로 1초가 경과했는지 확인
        if ((ros::Time::now() - last_msg_time).toSec() > 1.0) {
            ROS_WARN("Main PC로부터 1초 이상 응답 없음. 브레이크 메시지를 보냅니다.");
            race::drive_values brake_msg;
            brake_msg.brake = 1; // 브레이크 메시지 설정
            brake_pub.publish(brake_msg);
        }

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
