#!/usr/bin/env python

"""
node = "sub_sound"
topic = "sound_val"
topic -> "True" or "False"

mp3 파일을 재생하는 listener 노드
playsound 모듈을 사용

따라서 사용 전에 설치해야함
pip3 install playsound
"""


import rospy
from std_msgs.msg import String
import os
import sys
import playsound


if os.name == "nt":
    import msvcrt
else:
    import tty, termios


CURRENT_DIR = os.path.dirname(os.path.abspath(__file__))
UPPER_DIR = os.path.dirname(CURRENT_DIR)
MEDIA_DIR = os.path.join(UPPER_DIR, "media")
music_file = os.path.join(MEDIA_DIR, "music_1.mp3")

massage = ""
state = 0


def play_sound(music_file):
    playsound.playsound(music_file)
    return None


def callback(data):
    global massage
    massage = data.data

    return None


def listener():
    rospy.init_node("sub_sound")

    while not rospy.is_shutdown():
        rospy.Subscriber("sound_val", String, callback)

        if massage == "True" and state == 0:
            play_sound(music_file)
            state = 1
            continue

        if massage == "False":
            break

    return None


if __name__ == "__main__":
    try:
        listener()

    except rospy.ROSInterruptException:
        pass
