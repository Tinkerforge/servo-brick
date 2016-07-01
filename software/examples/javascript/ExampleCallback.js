var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'XXYYZZ'; // Change XXYYZZ to the UID of your Servo Brick

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var servo = new Tinkerforge.BrickServo(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function (error) {
        console.log('Error: ' + error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function (connectReason) {
        // Enable position reached callback
        servo.enablePositionReachedCallback();

        // Set velocity to 100°/s. This has to be smaller or equal to the
        // maximum velocity of the servo you are using, otherwise the position
        // reached callback will be called too early
        servo.setVelocity(0, 10000);
        servo.setPosition(0, 9000);
        servo.enable(0);
    }
);

// Register position reached callback
servo.on(Tinkerforge.BrickServo.CALLBACK_POSITION_REACHED,
    // Use position reached callback to swing back and forth
    function (servoNum, position) {
        if(position === 9000) {
            console.log('Position: 90°, going to -90°');
            servo.setPosition(servoNum, -9000);
        }
        else if(position === -9000) {
            console.log('Position: -90°, going to 90°');
            servo.setPosition(servoNum, 9000);
        }
        else {
            console.log('Error'); // Can only happen if another program sets position
        }
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        servo.disable(0);
        ipcon.disconnect();
        process.exit(0);
    }
);
