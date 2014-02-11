var IPConnection = require('Tinkerforge/IPConnection');
var BrickServo = require('Tinkerforge/BrickServo');

var HOST = 'localhost';
var PORT = 4223;
var UID = '6qCdfo';// Change to your UID

var ipcon = new IPConnection();// Create IP connection
var servo = new BrickServo(UID, ipcon);// Create device object

ipcon.connect(HOST, PORT,
    function(error) {
        console.log('Error: '+error);        
    }
);// Connect to brickd

// Don't use device before ipcon is connected
ipcon.on(IPConnection.CALLBACK_CONNECTED,
    function(connectReason) {
        servo.enablePositionReachedCallback();
        // Set velocity to 100°/s. This has to be smaller or equal to 
        // maximum velocity of the servo, otherwise cb_reached will be
        // called too early
        servo.setVelocity(0, 10000); 
        servo.setPosition(0, 9000);
        servo.enable(0);  
    }
);

// Register "position reached callback"
// Callback "position reached callback" will be called every time a position set with
// set_position is reached
servo.on(BrickServo.CALLBACK_POSITION_REACHED,
    function(servoNum, position) {
        if(position === 9000) {
            console.log('Position: 90°, going to -90°');
            servo.setPosition(servoNum, -9000);
        }
        else if(position === -9000) {
            console.log('Position: -90°, going to 90°');
            servo.setPosition(servoNum, 9000);
        }
        else {
            console.log('Error');// Can only happen if another program sets position
        }
    }
);

console.log("Press any key to exit ...");
process.stdin.on('data',
    function(data) {
        ipcon.disconnect();
        process.exit(0);
    }
);

