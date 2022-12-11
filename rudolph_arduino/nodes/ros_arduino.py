#!/usr/bin/env python3
"""
arduino와 serial 통신하는 코드
목적지에 도착하면, 이미지를 업로드하고, arduino에게 목적지 도착 신호를 보낸다.

모듈:
serial
cv2

pip install serial
pip install opencv-python

Topic: /slave_val

msg: rasp_arduino

"""


import rospy
from rudolph_msgs.msg import rasp_arduino
import os
import sys


if os.name == "nt":
    import msvcrt
else:
    import tty, termios


def main():
    if os.name != "nt":
        settings = termios.tcgetattr(sys.stdin)

    pub_msg = rasp_arduino()  # 메시지 객체 생성
    pub_msg.mid_arrive = 0
    pub_msg.mid_fin = 0
    pub_msg.fin_arrive = 0
    pub_msg.fin_return = 0

    rospy.init_node("ros_arduino")
    pub = rospy.Publisher("slave_val", rasp_arduino, queue_size=10)
    rate = rospy.Rate(10)  # 10hz

    while not rospy.is_shutdown():
        pub_msg.mid_arrive = 0
        pub_msg.mid_fin = 0
        pub_msg.fin_arrive = 0
        pub_msg.fin_return = 0

        pub.publish(pub_msg)  # 메세지 발행

        rate.sleep()

    if os.name != "nt":
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)

    return None


if __name__ == "__main__":
    try:
        main()

    except rospy.ROSInterruptException:
        pass
