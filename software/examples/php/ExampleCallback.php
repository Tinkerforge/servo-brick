<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickServo.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickServo;

$host = 'localhost';
$port = 4223;
$uid = '94ANb9AZAwo'; // Change to your UID

// Use position reached callback to swing back and forth
function cb_reached($servoNum, $position)
{
    global $servo;
    
    if ($position == 9000) {
        echo "Position: 90°, going to -90°\n";
        $servo->setPosition($servoNum, -9000);
    } elseif ($position == -9000) {
        echo "Position: -90°, going to 90°\n";
        $servo->setPosition($servoNum, 9000);
    } else {
        echo "Error\n"; // Can only happen if another program sets position
    }
}

$ipcon = new IPConnection($host, $port); // Create IP connection to brickd
$servo = new BrickServo($uid); // Create device object

$ipcon->addDevice($servo); // Add device to IP connection
// Don't use device before it is added to a connection

// Register "position reached callback" to cb_reached
// cb_reached will be called every time a position set with
// set_position is reached
$servo->registerCallback(BrickServo::CALLBACK_POSITION_REACHED, 'cb_reached');

// Set velocity to 100°/s. This has to be smaller or equal to 
// maximum velocity of the servo, otherwise cb_reached will be
// called too early
$servo->setVelocity(0, 10000);
$servo->setPosition(0, 9000);
$servo->enable(0);

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
