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


def main():
    state = 0
    if os.name != "nt":
        settings = termios.tcgetattr(sys.stdin)

    while True:

        if ser.readable():
            var = input("input b or c")  # input b, c
            var = var.encode("utf-8")
            ser.write(var)

    return None


if __name__ == "__main__":
    main()
