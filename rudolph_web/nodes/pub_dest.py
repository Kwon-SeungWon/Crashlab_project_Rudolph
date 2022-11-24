#!/usr/bin/env python


import rospy
from std_msgs.msg import String
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

    dest = get_dest()  # e.g. 113
    method = get_method()  # e.g. 0

    rospy.init_node("pub_dest")
    pub = rospy.Publisher("dest_val", String, queue_size=10)
    rate = rospy.Rate(10)  # 10hz

    while not rospy.is_shutdown():
        message = f"{dest}, {method}"
        pub.publish(message)
        rate.sleep()

    if os.name != "nt":
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)

    return None


if __name__ == "__main__":
    try:
        talker()

    except rospy.ROSInterruptException:
        pass

