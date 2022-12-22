#!/usr/bin/env python3
"""
Publish robot parameters for various reasons:
    They might be needed by more than one package.
    It might be nice to be able to modify them at runtime.
    It is an obvious place to find them.
See doc at http://wiki.ros.org/rospy/Overview/Parameter%20Server
"""
import rospy

# Robot parameter values
ROBOT_TICKS_PER_REV = 228.0  # 24:1 worm, 26:10 spur, 11 pole encoder magnet
ROBOT_WHEEL_CIRCUMFERENCE = 0.361  # meters
ROBOT_TICKS_PER_METER = int(ROBOT_TICKS_PER_REV / ROBOT_WHEEL_CIRCUMFERENCE)
ROBOT_TRACK_WIDTH = 0.41  # Wheel Separation Distance (meters)
ROBOT_MIN_PWM_VAL = 0  # Minimum PWM value motors will turn reliably
ROBOT_MAX_PWM_VAL = 220  # Maximum allowable PWM value
ROBOT_MIN_X_VEL = 0.01  # Minimum x velocity robot can manage (m/s)
ROBOT_MAX_X_VEL = 5.0  # Maximum x velocity robot can manage (m/s)
ROBOT_MIN_Z_VEL = 0.01  # Minimum theta-z velocity robot can manage (rad/s)
ROBOT_MAX_Z_VEL = 5.0  # Maximum theta-z velocity robot can manage (rad/s)
ROBOT_MTR_KP = 0.5  # Proportional coeff  최적 0.1
ROBOT_MTR_KD = 0.1  # Derivative coeff 최적 0.02
ROBOT_MTR_MAX_PID_TRIM = 20 # Max allowable value for PID trim term

# end points of segments of piecewise linear curve in descending order
# where curve relates tick rate (tr) to motor speed (s)
ROBOT_TRS_CURVE = ((8.92, 0.63), #892 240  ->8.92,4  -> 8.92,0.5
                   (5.78, 0.33), #578 140  ->5.78,2 ->5.78,0.25
                   (3.60, 0.188), #360 100  ->3.60,1->3.60,0.128
                   (1.42, 0.143))  #142 80->1.42,0.5->1.42,0.083

param_dict = {
    'ROBOT_TICKS_PER_REV': ROBOT_TICKS_PER_REV,
    'ROBOT_WHEEL_CIRCUMFERENCE': ROBOT_WHEEL_CIRCUMFERENCE,
    'ROBOT_TICKS_PER_METER': ROBOT_TICKS_PER_METER,
    'ROBOT_TRACK_WIDTH': ROBOT_TRACK_WIDTH,
    'ROBOT_MIN_PWM_VAL': ROBOT_MIN_PWM_VAL,
    'ROBOT_MAX_PWM_VAL': ROBOT_MAX_PWM_VAL,
    'ROBOT_MIN_X_VEL': ROBOT_MIN_X_VEL,
    'ROBOT_MAX_X_VEL': ROBOT_MAX_X_VEL,
    'ROBOT_MIN_Z_VEL': ROBOT_MIN_Z_VEL,
    'ROBOT_MAX_Z_VEL': ROBOT_MAX_Z_VEL,
    'ROBOT_TRS_CURVE': ROBOT_TRS_CURVE,
    'ROBOT_MTR_KP': ROBOT_MTR_KP,
    'ROBOT_MTR_KD': ROBOT_MTR_KD,
    'ROBOT_MTR_MAX_PID_TRIM': ROBOT_MTR_MAX_PID_TRIM
    }
    
for key, val in param_dict.items():
    rospy.set_param(key, val)
