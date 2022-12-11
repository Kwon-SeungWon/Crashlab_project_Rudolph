#!/usr/bin/env python3
"""
arduino와 serial 통신하는 코드
목적지에 도착하면, 이미지를 업로드하고, arduino에게 목적지 도착 신호를 보낸다.

모듈:
serial
cv2

pip install serial
pip install opencv-python

Topic: /arduino_val

msg: rasp_arduino

"""


#import rospy
from rudolph_msgs.msg import rasp_arduino
#import serial
import os
import sys
import requests
import cv2
import datetime

if os.name == "nt":
    import msvcrt
else:
    import tty, termios


#ser = serial.Serial("ttyARDUINO", 9600)  # 'ttyARDUINO' 부분에 환경에 맞는 포트 입력
URL = "http://140.238.28.123/fileUpload"  # 이미지 업로드 URL
TIME_FORMAT = "%Y-%m-%d_%H:%M:%S"

CURRENT_DIR = os.path.dirname(os.path.abspath(__file__))
UPPER_DIR = os.path.dirname(CURRENT_DIR)
IMAGE_DIR = UPPER_DIR + "/images"


def check_dir():
    """
    이미지 파일 다루기 전, 상위 폴더 안에 images 폴더가 있는지 확인. 없으면 images 폴더 생성
    """
    if not os.path.isdir(UPPER_DIR + "/images"):
        os.mkdir(UPPER_DIR + "/images")

    return None


def save_image():
    """
    웹캠 화면을 저장하는 코드.
    return: 저장된 이미지 파일 이름(현재 시간), 저장된 이미지 파일 경로
    """

    now_time = datetime.datetime.now().strftime(TIME_FORMAT)

    check_dir()
    cam = cv2.VideoCapture(2)
    ret, frame = cam.read()

    img_name = IMAGE_DIR + "/" + now_time + ".jpg"
    cv2.imwrite(img_name, frame)

    cam.release()
    cv2.destroyAllWindows()

    file_name = now_time + ".jpg"
    file_path = IMAGE_DIR + "/" + now_time + ".jpg"

    return file_name, file_path


def upload_image(file_name, file_path):
    """
    URL로 이미지파일을 업로드하는 함수
    """
    filename = file_name
    filepath = file_path

    image_file = {
        "file": (filename, open(filepath, "rb")),
        "Content-Type": "image/jpg",
        # "Content-Length": l,
    }
    requests.post(URL, files=image_file)

    return None


def post_image():
    """
    종합적인 이미지 업로드 코드
    """
    file_name, file_path = save_image()
    upload_image(file_name, file_path)

    return None

"""
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
"""

if __name__ == "__main__":
    check_dir()
    save_image()