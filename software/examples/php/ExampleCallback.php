<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickServo.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickServo;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XXYYZZ'; // Change to your UID

// Use position reached callback to swing back and forth
function cb_positionReached($servo_num, $position, $user_data)
{
    $servo = $user_data;

    if ($position == 9000) {
        echo "Position: 90°, going to -90°\n";
        $servo->setPosition($servo_num, -9000);
    } elseif ($position == -9000) {
        echo "Position: -90°, going to 90°\n";
        $servo->setPosition($servo_num, 9000);
    } else {
        echo "Error\n"; // Can only happen if another program sets position
    }
}

$ipcon = new IPConnection(); // Create IP connection
$servo = new BrickServo(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Register position reached callback to function cb_positionReached
$servo->registerCallback(BrickServo::CALLBACK_POSITION_REACHED, 'cb_positionReached', $servo);

// Enable position reached callback
$servo->enablePositionReachedCallback();

// Set velocity to 100°/s. This has to be smaller or equal to the
// maximum velocity of the servo you are using, otherwise the position
// reached callback will be called too early
$servo->setVelocity(0, 10000);
$servo->setPosition(0, 9000);
$servo->enable(0);

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
