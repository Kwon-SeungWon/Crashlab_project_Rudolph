#!/usr/bin/env python3
"""
arduino와 serial 통신하는 코드

serial 모듈 설치해야함
pip install serial

Topic: /arduino_val
"""


import rospy
from rudolph_msgs.msg import rasp_arduino
import serial
import os
import sys

if os.name == "nt":
    import msvcrt
else:
    import tty, termios


# 'COM3' 부분에 환경에 맞는 포트 입력
ser = serial.Serial("COM3", 9600)


def talker():
    if os.name != "nt":
        settings = termios.tcgetattr(sys.stdin)

    msg = rasp_arduino()  # 메시지 객체 생성

    msg.mid_arrive = 0
    msg.mid_exit = 0
    msg.final_arrive = 0
    msg.final_exit = 0

    rospy.init_node("pub_dest")
    pub = rospy.Publisher("arduino_val", rasp_arduino, queue_size=10)
    rate = rospy.Rate(10)  # 10hz

    while not rospy.is_shutdown():
        pub.publish(msg)

        rate.sleep()

    if os.name != "nt":
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)

    return None


if __name__ == "__main__":
    try:
        talker()

    except rospy.ROSInterruptException:
        pass
