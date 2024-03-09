# ROS-Watch-Dog-System

Mian PC Fail 상황에서 대비 긴급제동을 하도록 구현된 Watch dog 시스템입니다. 

Master Node(Sub PC)와 Slave Node(Main PC)로 구성되어 있으며, serial control node는 sub PC에서 실행시킵니다. 

이기종간 통신 인터 페이스 구축을 위한 설정은 다음과 같습니다. 동일한 네트워크에 연결하는데 있어서 수동으로 ip주소를 생성하고 해당 ip주소를 기반으로 네트워크를 공유하는 방식입니다. 

수동으로 IP 주소 설정: 다음과 같이 두 컴퓨터에 서로 다른 IP 주소를 수동으로 설정할 수 있습니다. 

예를 들어, 한 컴퓨터에는 192.168.1.1, 다른 컴퓨터에는 192.168.1.2와 같이 설정할 수 있습니다. 이때 서브넷 마스크는 255.255.255.0으로 설정합니다.

리눅스의 경우 ifconfig 또는 ip 명령어를 사용하여 IP 주소를 설정할 수 있습니다. 

sudo ifconfig eth0 192.168.1.1 netmask 255.255.255.0 up

네트워크 설정하기: 두 노트북이 같은 네트워크에 연결되어 있어야 합니다. WiFi 또는 LAN을 통해 같은 로컬 네트워크에 있어야 합니다.

호스트 이름과 IP 설정: 두 시스템 모두에서 호스트 이름과 IP 주소를 설정합니다. /etc/hosts 파일에 각 시스템의 호스트 이름과 IP 주소를 추가할 수 있습니다. 예를 들어,


192.168.1.2 laptop1
192.168.1.3 laptop2

ROS_MASTER_URI 설정하기: ROS 통신을 위해 하나의 노트북은 ROS Master 역할을 해야 하며, 다른 하나는 이 Master에 연결합니다. Master가 되는 노트북에서는 ROS_MASTER_URI 환경 변수를 자기 자신의 IP로 설정하고, 다른 노트북에서는 이 Master의 IP로 설정합니다. 예를 들어, laptop1이 Master라면 다음과 같이 설정합니다.

laptop1에서:

export ROS_MASTER_URI=http://laptop1:11311

laptop2에서:

export ROS_MASTER_URI=http://laptop1:11311
ROS_HOSTNAME 설정하기: 각 노트북에서 ROS_HOSTNAME 환경 변수를 해당 노트북의 호스트 이름이나 IP 주소로 설정합니다.

laptop1에서:

export ROS_HOSTNAME=laptop1
laptop2에서:

export ROS_HOSTNAME=laptop2

ROS 네트워크 테스트하기: 설정이 완료되면, rostopic list 또는 rosnode list 명령어를 사용하여 ROS 네트워크 연결을 테스트할 수 있습니다. 또한, ping 명령어를 사용하여 두 노트북 간의 연결을 테스트할 수 있습니다.

통신하기: 이제 두 노트북 사이에 ROS 통신을 할 수 있습니다. 예를 들어, laptop1에서 메시지를 발행하고 laptop2에서 해당 토픽을 구독할 수 있습니다.

위의 설정들은 쉘의 .bashrc 파일에 추가하여 매번 새 터미널을 열 때 자동으로 로드되게 할 수 있습니다.

ROS 네트워킹 문제가 발생한다면, 방화벽 설정이나 네트워크 구성을 확인해야 할 수도 있습니다. ROS는 기본적으로 11311 포트를 사용하는데, 이 포트가 방화벽에 의해 차단되지 않도록 해야 합니다.
