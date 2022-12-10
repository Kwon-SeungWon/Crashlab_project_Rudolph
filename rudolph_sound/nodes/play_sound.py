#!/usr/bin/env python3

"""
rospy가 끝날때 까지 sound 재생하는 노드

사용 모듈:
playsound
mutagen

따라서 사용 전에 설치해야함
pip install playsound
pip install mutagen
"""


import rospy
import os
import sys
import playsound
import time
from mutagen.mp3 import MP3


if os.name == "nt":
    import msvcrt
else:
    import tty, termios


CURRENT_DIR = os.path.dirname(os.path.abspath(__file__))
UPPER_DIR = os.path.dirname(CURRENT_DIR)
MEDIA_DIR = os.path.join(UPPER_DIR, "media")
music_file_list = []

massage = ""
state = 0


def get_music_file():
    """
    media 폴더에 있는 mp3 파일을 리스트로 반환하는 함수
    """
    music_list = []
    for file in os.listdir(MEDIA_DIR):
        if file.endswith(".mp3"):
            music_list.append(file)

    return music_list


def get_music_file_path(music_file):
    """
    media 폴더에 있는 mp3 파일의 경로를 반환하는 함수
    """
    music_file_path = os.path.join(MEDIA_DIR, music_file)
    return music_file_path


def add_music_file_path():
    """
    music_file_list에 mp3 파일의 전체 경로를 추가하는 함수
    """
    music_list = get_music_file()

    for music in music_list:
        music_file_path = get_music_file_path(music)
        music_file_list.append(music_file_path)

    return None


def get_mp3_duration(music_file):
    """
    mp3 파일의 길이를 반환하는 함수
    """
    audio = MP3(music_file)
    duration = int(audio.info.length)
    return duration


def main():
    add_music_file_path()
    count = 0

    while rospy.is_shutdown() == False:
        music_file = music_file_list[count]
        duration = get_mp3_duration(music_file)

        playsound.playsound(music_file, False)
        time.sleep(duration + 2)
        count += 1

        if count == len(music_file_list):
            count = 0


if __name__ == "__main__":
    try:
        main()
    
    except rospy.ROSInterruptException:
        pass