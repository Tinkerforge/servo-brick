#!/usr/bin/perl  

use Tinkerforge::IPConnection;
use Tinkerforge::BrickServo;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => '5VF5vG'; # Change to your UID

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $servo = Tinkerforge::BrickServo->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Configure two servos with voltage 5.5V
# Servo 1: Connected to port 0, period of 19.5ms, pulse width of 1 to 2ms
#          and operating angle -100 to 100°
#
# Servo 2: Connected to port 5, period of 20ms, pulse width of 0.95 
#          to 1.95ms and operating angle -90 to 90°
$servo->set_output_voltage(5500);

$servo->set_degree(0, -10000, 10000);
$servo->set_pulse_width(0, 1000, 2000);
$servo->set_period(0, 19500);
$servo->set_acceleration(0, 1000); # Slow acceleration
$servo->set_velocity(0, 0xFFFF); # Full speed

$servo->set_degree(5, -9000, 9000);
$servo->set_pulse_width(5, 950, 1950);
$servo->set_period(5, 20000);
$servo->set_acceleration(5, 0xFFFF); # Full acceleration
$servo->set_velocity(5, 0xFFFF); # Full speed

$servo->set_position(0, 10000); # Set to most right position
$servo->enable(0);

$servo->set_position(5, -9000); # Set to most left position
$servo->enable(5);

print "\nPress any key to exit...\n";
<STDIN>;
$ipcon->disconnect();

