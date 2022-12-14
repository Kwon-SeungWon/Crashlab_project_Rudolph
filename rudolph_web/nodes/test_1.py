#!/usr/bin/env python3
"""
서버에서 목적지와 방법을 받아서 pub_dest 노드로 보내는 코드
pub: dest_val
e.g. 113, 0
"""

import requests
import json
import os
import sys
import datetime
import time

if os.name == "nt":
    import msvcrt
else:
    import tty, termios

TIME_FORMAT = "%Y-%m-%d %H:%M:%S"


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


def talker():
    while True:
        dest_dict = get_dest_dict()
        dest = dest_dict["dest"]  # e.g. 113
        method = dest_dict["method"]  # e.g. 0
        web_time = dest_dict["time"]  # e.g. 2021-06-01 00:00:00

        now_time = datetime.datetime.now().strftime(TIME_FORMAT)
        time_diff = datetime.datetime.strptime(
            now_time, TIME_FORMAT
        ) - datetime.datetime.strptime(web_time, TIME_FORMAT)

        if time_diff.seconds < 60:
            print("Server is connected")
            break

        print(web_time, now_time, time_diff.seconds)
        time.sleep(1)

    print(dest, method)

    return None


if __name__ == "__main__":
    talker()
