use std::{error::Error, io};

use tinkerforge::{ip_connection::IpConnection, servo_brick::*};

const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XXYYZZ"; // Change XXYYZZ to the UID of your Servo Brick.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let servo = ServoBrick::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
                                          // Don't use device before ipcon is connected.

    // Configure two servos with voltage 5.5V
    // Servo 1: Connected to port 0, period of 19.5ms, pulse width of 1 to 2ms
    //          and operating angle -100 to 100°
    //
    // Servo 2: Connected to port 5, period of 20ms, pulse width of 0.95
    //          to 1.95ms and operating angle -90 to 90°
    servo.set_output_voltage(5500).recv()?;

    servo.set_degree(0, -10000, 10000).recv()?;
    servo.set_pulse_width(0, 1000, 2000).recv()?;
    servo.set_period(0, 19500).recv()?;
    servo.set_acceleration(0, 1000).recv()?; // Slow acceleration
    servo.set_velocity(0, 65535).recv()?; // Full speed

    servo.set_degree(5, -9000, 9000).recv()?;
    servo.set_pulse_width(5, 950, 1950).recv()?;
    servo.set_period(5, 20000).recv()?;
    servo.set_acceleration(5, 65535).recv()?; // Full acceleration
    servo.set_velocity(5, 65535).recv()?; // Full speed

    servo.set_position(0, 10000).recv()?; // Set to most right position
    servo.enable(0).recv()?;

    servo.set_position(5, -9000).recv()?; // Set to most left position
    servo.enable(5).recv()?;

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;

    servo.disable(0).recv()?;
    servo.disable(5).recv()?;

    ipcon.disconnect();
    Ok(())
}
