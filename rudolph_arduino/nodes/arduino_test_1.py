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


# import rospy
# from rudolph_msgs.msg import rasp_arduino
import serial
import os
import sys
import requests

# import cv2
import datetime
import time

if os.name == "nt":
    import msvcrt
else:
    import tty, termios

# Rx Tx 포트에서는 '/dev/ttyACM0'을 사용
ser = serial.Serial("/dev/ttyACM0", 9600)
URL = "http://140.238.28.123/fileUpload"  # 이미지 업로드 URL
TIME_FORMAT = "%Y-%m-%d_%H:%M:%S"

CURRENT_DIR = os.path.dirname(os.path.abspath(__file__))
UPPER_DIR = os.path.dirname(CURRENT_DIR)
IMAGE_DIR = UPPER_DIR + "/images"


def sub_arduino(decode_val):
    """
    아두이노에서 python으로 보낸 신호를 받는 함수.
    1: 중간지점 도착
    2: 목적지 도착 -> 이미지 업로드

    pub_msg 형식: rasp_arduino
    e.g. pub_msg.mid_fin = 1

    return: pub_msg
    """
    print("decode_val: ", decode_val)


def main():
    state = 0
    if os.name != "nt":
        settings = termios.tcgetattr(sys.stdin)

    while True:

        if ser.readable():
            """
            아두이노에서 보낸 메세지를 받는 코드
            serial값을 읽은 후, pub_msg에 변환해 저장.
            """
            val = ser.readline()  # 아두이노에서 보낸 메세지를 받는 코드
            decode_val = val.decode()[: len(val) - 1]  # 메세지 디코딩 후, 마지막 개행문자 제거
            sub_arduino(decode_val)  # 아두이노에서 온 메세지에 따라, pub_msg 값 변경

    return None


if __name__ == "__main__":
    main()
