#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/brick_servo'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change to your UID

ipcon = IPConnection.new # Create IP connection
s = BrickServo.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Configure two servos with voltage 5.5V
# Servo 1: Connected to port 0, period of 19.5ms, pulse width of 1 to 2ms
#          and operating angle -100 to 100°
#
# Servo 2: Connected to port 5, period of 20ms, pulse width of 0.95 
#          to 1.95ms and operating angle -90 to 90°
s.set_output_voltage 5500

s.set_degree 0, -10000, 10000
s.set_pulse_width 0, 1000, 2000
s.set_period 0, 19500
s.set_acceleration 0, 1000 # Slow acceleration
s.set_velocity 0, 0xFFFF # Full speed

s.set_degree 5, -9000, 9000
s.set_pulse_width 5, 950, 1950
s.set_period 5, 20000
s.set_acceleration 5, 0xFFFF # Full acceleration
s.set_velocity 5, 0xFFFF # Full speed

s.set_position 0, 10000 # Set to most right position
s.enable 0

s.set_position 5, -9000 # Set to most left position
s.enable 5

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
