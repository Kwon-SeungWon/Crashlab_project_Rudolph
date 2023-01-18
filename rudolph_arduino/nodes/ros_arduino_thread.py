#!/usr/bin/env python3
"""
arduino와 serial 통신하는 코드.

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
import serial
import os
import sys
import requests
import cv2
import datetime
import time
import threading

if os.name == "nt":
    import msvcrt
else:
    import tty, termios

# Rx Tx 포트에서는 '/dev/ttyACM0'을 사용
ser = serial.Serial("/dev/ttyACM0", 9600)
URL = "http://xxx.xxx.xxx.xxx/fileUpload"  # 이미지 업로드 URL
TIME_FORMAT = "%Y-%m-%d_%H:%M:%S"

CURRENT_DIR = os.path.dirname(os.path.abspath(__file__))
UPPER_DIR = os.path.dirname(CURRENT_DIR)
IMAGE_DIR = UPPER_DIR + "/images"

lock = threading.Lock()
rospy.init_node("ros_arduino")
rate = rospy.Rate(5)  # 10hz


def get_serial():
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
        for _ in range(20):
            cam = cv2.VideoCapture(0)
            time.sleep(0.1)  # 카메라 준비 시간

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

    count = 0
    pub_msg = rasp_arduino()
    pub = rospy.Publisher("slave_val", rasp_arduino, queue_size=10)

    pub_msg.mid_arrive = 0
    pub_msg.mid_fin = 0
    pub_msg.fin_arrive = 0
    pub_msg.fin_return = 0

    for _ in range(3):
        pub.publish(pub_msg)
        rospy.loginfo(pub_msg)
        rate.sleep()

    while not rospy.is_shutdown():
        if ser.readable():
            """
            아두이노에서 보낸 메세지를 받는 코드
            serial값을 읽은 후, pub_msg에 변환해 저장.
            """
            val = ser.readline()  # 아두이노에서 보낸 메세지를 받는 코드
            decode_val = val.decode()[: len(val) - 1]  # 메세지 디코딩
            decode_val = decode_val.strip("\r")  # 개행문자 제거
            rospy.loginfo(f"arduino -> rasp_sub: {decode_val}")

            if decode_val == "1":  # 경유지 동작 수행 종료
                pub_msg.mid_arrive = 0
                pub_msg.mid_fin = 1
                pub_msg.fin_arrive = 0
                pub_msg.fin_return = 0

                for _ in range(3):
                    pub.publish(pub_msg)
                    rospy.loginfo(pub_msg)
                    rate.sleep()

            if decode_val == "2":  # 배송지 동작 수행 종료(대면 수령)
                pub_msg.mid_arrive = 0
                pub_msg.mid_fin = 0
                pub_msg.fin_arrive = 0
                pub_msg.fin_return = 1

                for _ in range(3):
                    pub.publish(pub_msg)
                    rospy.loginfo(pub_msg)
                    rate.sleep()

            if decode_val == "3":  # 배송지 동작 수행 종료(비대면 수령)
                pub_msg.mid_arrive = 0
                pub_msg.mid_fin = 0
                pub_msg.fin_arrive = 0
                pub_msg.fin_return = 1

                for _ in range(3):
                    pub.publish(pub_msg)
                    rospy.loginfo(pub_msg)
                    rate.sleep()

                if count == 0:
                    time.sleep(3)
                    post_image()  # 인증사진 전송
                    count = 1

        rate.sleep()
    return None


def act_callback(msg):
    """
    master_val 토픽을 구독하는 콜백 함수
    master_val 토픽에서 받은 메세지를 인코딩 한 후, 아두이노로 즉시 보낸다.

    아두이노에게 보내는 메세지: 'b' or 'c' or 'd' (char형식에 유의)
    """

    def send_msg(msg):
        msg = str(msg)
        msg = msg.encode("utf-16")
        ser.write(msg)

        return None

    if msg.mid_arrive == 1:
        for _ in range(3):
            send_msg("b")
        rospy.loginfo("master val: mid_arrive == 1")
        return None

    if msg.fin_arrive == 1:
        for _ in range(3):
            send_msg("c")
        rospy.loginfo("master val: fin_arrive == 1")
        return None

    if msg.fin_arrive == 1:
        for _ in range(3):
            send_msg("d")
        rospy.loginfo("master val: fin_arrive == 1")
        return None


def main():
    if os.name != "nt":
        settings = termios.tcgetattr(sys.stdin)

    # act_callback을 통해 arduino로 메세지 즉시 전송
    sub = rospy.Subscriber("master_val", rasp_arduino, act_callback)

    if os.name != "nt":
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)

    while not rospy.is_shutdown():
        rate.sleep()
        continue

    return None


if __name__ == "__main__":
    try:
        t = threading.Thread(target=get_serial)
        t.start()
        main()

    except rospy.ROSInterruptException:
        pass
