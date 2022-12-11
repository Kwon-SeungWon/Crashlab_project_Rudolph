#!/usr/bin/env python3
"""
arduino와 serial 통신하는 코드

ros 없는 버전

모듈:
serial

pip install serial

0, 1, 2, 3

메세지의 형태가 아두이노에서는 파이썬에게 Serial.println 형태로 보내고, 파이썬에서는 아두이노에게 char 형의 문자로 시리얼을 보낸다.
"""


# import rospy
# from rudolph_msgs.msg import rasp_arduino
import serial
import os
import sys
import requests
import time

# import cv2
import datetime

if os.name == "nt":
    import msvcrt
else:
    import tty, termios


ser = serial.Serial("/dev/ttyACM0", 9600)  # 'COM3' 부분에 환경에 맞는 포트 입력
TIME_FORMAT = "%Y-%m-%d_%H:%M:%S"


def main():
    while True:
        if ser.readable():
            val = ser.readline()
            decode_val = val.decode()[: len(val) - 1]  # 넘어온 데이터 중 마지막 개행문자 제외
            print(decode_val)

        time.sleep(0.01)


if __name__ == "__main__":
    try:
        main()

    except:
        pass
