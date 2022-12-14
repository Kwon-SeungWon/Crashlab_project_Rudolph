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


def convert_dest_to_coord(dest: str):
    """
    dest를 받아서 좌표로 변환하는 함수
    return: [x: float, y: float, z: float, w: float]
    """
    convert_dict = {
        "113": [42.0, 11.2, 0.097, 1.0],
        "114": [0.0, 0.0, 0.0, 0.0],
        "115": [0.0, 0.0, 0.0, 0.0],
        "116": [0.0, 0.0, 0.0, 0.0],
        "117": [0.0, 0.0, 0.0, 0.0],
        "118": [0.0, 0.0, 0.0, 0.0],
        "119": [0.0, 0.0, 0.0, 0.0],
        "120": [0.0, 0.0, 0.0, 0.0],
        "121": [0.0, 0.0, 0.0, 0.0],
        "122": [0.0, 0.0, 0.0, 0.0],
        "123": [0.0, 0.0, 0.0, 0.0],
        "124": [0.0, 0.0, 0.0, 0.0],
        "125": [0.0, 0.0, 0.0, 0.0],
        "126": [0.0, 0.0, 0.0, 0.0],
        "127": [0.0, 0.0, 0.0, 0.0],
        "128": [0.0, 0.0, 0.0, 0.0],
        "129": [0.0, 0.0, 0.0, 0.0],
        "130": [0.0, 0.0, 0.0, 0.0],
        "131": [0.0, 0.0, 0.0, 0.0],
    }

    return convert_dict[dest]


def set_msg(msg, dest, method):
    """
    dest를 좌표로 변환해서 msg에 넣어주는 함수
    x, y, z, w는 float

    return: msg
    """
    coordinate = convert_dest_to_coord(dest)

    msg.stamp = rospy.Time.now()

    msg.fin_x = coordinate[0]
    msg.fin_y = coordinate[1]
    msg.fin_z = coordinate[2]
    msg.fin_w = coordinate[3]

    return msg


def talker():
    if os.name != "nt":
        settings = termios.tcgetattr(sys.stdin)
    count = 0
    msg = web_rasp()

    msg.state = 1
    msg.mid_x = 22.443568993207002  # 112호 x좌표
    msg.mid_y = 11.193750460054984  # 112호 y좌표
    msg.mid_z = 0.09728127496148936  # 112호 z값
    msg.mid_w = 0.689173570437249  # 112호 w값

    dest = get_dest()  # e.g. 113
    method = get_method()  # e.g. 0

    rospy.init_node("pub_dest")
    pub = rospy.Publisher("dest_val", web_rasp, queue_size=10)
    rate = rospy.Rate(5)  # 10hz

    while not rospy.is_shutdown():
        if count == 10:
            break

        msg = set_msg(msg, dest, method)
        pub.publish(msg)

        rate.sleep()
        count += 1
    if os.name != "nt":
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)

    return None


if __name__ == "__main__":
    try:
        talker()

    except rospy.ROSInterruptException:
        pass
