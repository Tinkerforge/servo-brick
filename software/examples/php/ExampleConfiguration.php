<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickServo.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickServo;

const HOST = 'localhost';
const PORT = 4223;
const UID = '94ANb9AZAwo'; // Change to your UID

$ipcon = new IPConnection(); // Create IP connection
$servo = new BrickServo(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Configure two servos with voltage 5.5V
// Servo 1: Connected to port 0, period of 19.5ms, pulse width of 1 to 2ms
//          and operating angle -100 to 100°
//
// Servo 2: Connected to port 5, period of 20ms, pulse width of 0.95 
//          to 1.95ms and operating angle -90 to 90°
$servo->setOutputVoltage(5500);

$servo->setDegree(0, -10000, 10000);
$servo->setPulseWidth(0, 1000, 2000);
$servo->setPeriod(0, 19500);
$servo->setAcceleration(0, 1000); // Slow acceleration
$servo->setVelocity(0, 0xFFFF); // Full speed

$servo->setDegree(5, -9000, 9000);
$servo->setPulseWidth(5, 950, 1950);
$servo->setPeriod(5, 20000);
$servo->setAcceleration(5, 0xFFFF); // Full acceleration
$servo->setVelocity(5, 0xFFFF); // Full speed

$servo->setPosition(0, 10000); // Set to most right position
$servo->enable(0);

$servo->setPosition(5, -9000); // Set to most left position
$servo->enable(5);

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->disconnect();

?>
