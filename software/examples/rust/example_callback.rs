use std::{error::Error, io, thread};
use tinkerforge::{ipconnection::IpConnection, servo_brick::*};

const HOST: &str = "127.0.0.1";
const PORT: u16 = 4223;
const UID: &str = "XXYYZZ"; // Change XXYYZZ to the UID of your Servo Brick

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection
    let servo_brick = ServoBrick::new(UID, &ipcon); // Create device object

    ipcon.connect(HOST, PORT).recv()??; // Connect to brickd
                                        // Don't use device before ipcon is connected

    //Create listener for position reached events.
    let position_reached_listener = servo_brick.get_position_reached_receiver();
    // Spawn thread to handle received events. This thread ends when the servo_brick
    // is dropped, so there is no need for manual cleanup.
    let servo_brick_copy = servo_brick.clone(); //Device objects don't implement Sync, so they can't be shared between threads (by reference). So clone the device and move the copy.
    thread::spawn(move || {
        for event in position_reached_listener {
            if event.position == 9000 {
                println!("Position: 90°, going to -90°");
                servo_brick_copy.set_position(event.servo_num, -9000);
            } else if event.position == -9000 {
                println!("Position: -90°, going to 90°");
                servo_brick_copy.set_position(event.servo_num, 9000);
            } else {
                // Can only happen if another program sets position
                println!("Error");
            }
        }
    });

    // Enable position reached callback
    servo_brick.enable_position_reached_callback();

    // Set velocity to 100°/s. This has to be smaller or equal to the
    // maximum velocity of the servo you are using, otherwise the position
    // reached callback will be called too early
    servo_brick.set_velocity(0, 10000);
    servo_brick.set_position(0, 9000);
    servo_brick.enable(0);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    servo_brick.disable(0);
    ipcon.disconnect();
    Ok(())
}
