#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XXYYZZ # Change to your UID

# Configure two servos with voltage 5.5V
# Servo 1: Connected to port 0, period of 19.5ms, pulse width of 1 to 2ms
#          and operating angle -100 to 100°
#
# Servo 2: Connected to port 5, period of 20ms, pulse width of 0.95
#          to 1.95ms and operating angle -90 to 90°
tinkerforge call servo-brick $uid set-output-voltage 5500

tinkerforge call servo-brick $uid set-degree 0 -10000 10000
tinkerforge call servo-brick $uid set-pulse-width 0 1000 2000
tinkerforge call servo-brick $uid set-period 0 19500
tinkerforge call servo-brick $uid set-acceleration 0 1000 # Slow acceleration
tinkerforge call servo-brick $uid set-velocity 0 65535 # Full speed

tinkerforge call servo-brick $uid set-degree 5 -9000 9000
tinkerforge call servo-brick $uid set-pulse-width 5 950 1950
tinkerforge call servo-brick $uid set-period 5 20000
tinkerforge call servo-brick $uid set-acceleration 5 65535 # Full acceleration
tinkerforge call servo-brick $uid set-velocity 5 65535 # Full speed

tinkerforge call servo-brick $uid set-position 0 10000 # Set to most right position
tinkerforge call servo-brick $uid enable 0

tinkerforge call servo-brick $uid set-position 5 -9000 # Set to most left position
tinkerforge call servo-brick $uid enable 5

echo "Press key to exit"; read dummy

tinkerforge call servo-brick $uid disable 0
tinkerforge call servo-brick $uid disable 5
