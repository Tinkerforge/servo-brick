use std::{error::Error, io, thread};
use tinkerforge::{ip_connection::IpConnection, servo_brick::*};

const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XXYYZZ"; // Change XXYYZZ to the UID of your Servo Brick.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let servo = ServoBrick::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
                                          // Don't use device before ipcon is connected.

    let position_reached_receiver = servo.get_position_reached_callback_receiver();

    // Spawn thread to handle received callback messages.
    // This thread ends when the `servo` object
    // is dropped, so there is no need for manual cleanup.
    let servo_copy = servo.clone(); //Device objects don't implement Sync, so they can't be shared between threads (by reference). So clone the device and move the copy.
    thread::spawn(move || {
        for position_reached in position_reached_receiver {
            if position_reached.position == 9000 {
                println!("Position: 90°, going to -90°");
                servo_copy.set_position(position_reached.servo_num, -9000);
            } else if position_reached.position == -9000 {
                println!("Position: -90°, going to 90°");
                servo_copy.set_position(position_reached.servo_num, 9000);
            } else {
                // Can only happen if another program sets position
                println!("Error");
            }
        }
    });

    // Enable position reached callback
    servo.enable_position_reached_callback();

    // Set velocity to 100°/s. This has to be smaller or equal to the
    // maximum velocity of the servo you are using, otherwise the position
    // reached callback will be called too early
    servo.set_velocity(0, 10000);
    servo.set_position(0, 9000);
    servo.enable(0);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;

    servo.disable(0);

    ipcon.disconnect();
    Ok(())
}
