#!/usr/bin/env python3
"""
arduino와 serial 통신하는 코드

ros 없는 버전

모듈:
serial

pip install serial

0, 1, 2, 3
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


ser = serial.Serial("COM3", 9600)  # 'COM3' 부분에 환경에 맞는 포트 입력
TIME_FORMAT = "%Y-%m-%d_%H:%M:%S"


def main():
    while True:
        if ser.readable():
            var = input()

            if var == "0":
                var = var.encode("utf-8")
                ser.write(var)
                print(f"send {var}")
                time.sleep(0.5)

            if var == "1":
                var = var.encode("utf-8")
                ser.write(var)
                print(f"send {var}")
                time.sleep(0.5)

            if var == "2":
                var = var.encode("utf-8")
                ser.write(var)
                print(f"send {var}")
                time.sleep(0.5)

            if var == "3":
                var = var.encode("utf-8")
                ser.write(var)
                print(f"send {var}")
                time.sleep(0.5)

        # val = ser.readline()
        # decode_val = val.decode()[: len(val) - 1]  # 넘어온 데이터 중 마지막 개행문자 제외

        time.sleep(0.01)


if __name__ == "__main__":
    try:
        main()

    except:
        pass
