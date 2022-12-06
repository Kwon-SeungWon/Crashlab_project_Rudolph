#!/usr/bin/env python3
"""
서버에서 목적지와 방법을 받아서 pub_dest 노드로 보내는 코드
pub: dest_val
e.g. 113, 0
"""


import rospy
from rudolph_msgs.msg import web_rasp
import requests
import json
import os
import sys

if os.name == "nt":
    import msvcrt
else:
    import tty, termios


def get_dest_dict() -> dict:
    URL = "http://140.238.28.123/get_dest"
    response = requests.get(URL)

    return_dict = json.loads(response.text)
    return return_dict


def get_dest() -> str:
    result_dict: dict = get_dest_dict()
    return result_dict["dest"]  # str


def get_method() -> str:
    result_dict: dict = get_dest_dict()
    return result_dict["method"]  # str


def talker():
    if os.name != "nt":
        settings = termios.tcgetattr(sys.stdin)

    msg = web_rasp()

    msg.go = False
    msg.mid_x = 0
    msg.mid_y = 1
    msg.mid_theta = 2

    dest = get_dest()  # e.g. 113
    method = get_method()  # e.g. 0

    rospy.init_node("pub_dest")
    pub = rospy.Publisher("dest_val", web_rasp, queue_size=10)
    rate = rospy.Rate(10)  # 10hz

    while not rospy.is_shutdown():
        msg.stamp = rospy.Time.now()
        msg.fin_x = float(dest)
        msg.fin_y = float(dest) + 1
        msg.fin_theta = float(dest) + 2
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