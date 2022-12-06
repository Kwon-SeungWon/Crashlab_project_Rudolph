#!/usr/bin/env python3

"""
rospy가 끝날때 까지 sound 재생하는 노드

playsound 모듈을 사용

따라서 사용 전에 설치해야함
pip install playsound
"""


import rospy
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


def main():

    while not rospy.is_shutdown():
        playsound.playsound(music_file)

    return None


if __name__ == "__main__":
    try:
        main()

    except rospy.ROSInterruptException:
        pass
