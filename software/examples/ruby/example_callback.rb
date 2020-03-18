#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/brick_servo'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XXYYZZ' # Change XXYYZZ to the UID of your Servo Brick

ipcon = IPConnection.new # Create IP connection
servo = BrickServo.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Use position reached callback to swing back and forth
servo.register_callback(BrickServo::CALLBACK_POSITION_REACHED) do |servo_num, position|
  if position == 9000
    puts 'Position: 90°, going to -90°'
    servo.set_position servo_num, -9000
  elsif position == -9000
    puts 'Position: -90°, going to 90°'
    servo.set_position servo_num, 9000
  else
    puts 'Error' # Can only happen if another program sets position
  end
end

# Enable position reached callback
servo.enable_position_reached_callback

# Set velocity to 100°/s. This has to be smaller or equal to the
# maximum velocity of the servo you are using, otherwise the position
# reached callback will be called too early
servo.set_velocity 0, 10000
servo.set_position 0, 9000
servo.enable 0

puts 'Press key to exit'
$stdin.gets

servo.disable 0

ipcon.disconnect
