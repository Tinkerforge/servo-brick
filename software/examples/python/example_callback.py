#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change to your UID

from tinkerforge.ip_connection import IPConnection
from tinkerforge.brick_servo import BrickServo

# Use position reached callback to swing back and forth
def cb_position_reached(servo_num, position, servo):
    if position == 9000:
        print('Position: 90°, going to -90°')
        servo.set_position(servo_num, -9000)
    elif position == -9000:
        print('Position: -90°, going to 90°')
        servo.set_position(servo_num, 9000)
    else:
        print('Error') # Can only happen if another program sets position

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    servo = BrickServo(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Register "position reached callback" to cb_reached
    # cb_reached will be called every time a position set with
    # set_position is reached
    servo.register_callback(servo.CALLBACK_POSITION_REACHED,
                            lambda x, y: cb_position_reached(x, y, servo))
    servo.enable_position_reached_callback()

    # Set velocity to 100°/s. This has to be smaller or equal to
    # maximum velocity of the servo, otherwise cb_reached will be
    # called too early
    servo.set_velocity(0, 10000)
    servo.set_position(0, 9000)
    servo.enable(0)

    raw_input('Press key to exit\n') # Use input() in Python 3
    ipcon.disconnect()
