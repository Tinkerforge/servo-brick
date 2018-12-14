package main

import (
	"fmt"
	"tinkerforge/ipconnection"
	"tinkerforge/servo_brick"
)

const ADDR string = "localhost:4223"
const UID string = "XXYYZZ" // Change XXYYZZ to the UID of your Servo Brick.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	servo, _ := servo_brick.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	// Configure two servos with voltage 5.5V
	// Servo 1: Connected to port 0, period of 19.5ms, pulse width of 1 to 2ms
	//          and operating angle -100 to 100°
	//
	// Servo 2: Connected to port 5, period of 20ms, pulse width of 0.95
	//          to 1.95ms and operating angle -90 to 90°
	servo.SetOutputVoltage(5500)

	servo.SetDegree(0, -10000, 10000)
	servo.SetPulseWidth(0, 1000, 2000)
	servo.SetPeriod(0, 19500)
	servo.SetAcceleration(0, 1000) // Slow acceleration
	servo.SetVelocity(0, 65535)    // Full speed

	servo.SetDegree(5, -9000, 9000)
	servo.SetPulseWidth(5, 950, 1950)
	servo.SetPeriod(5, 20000)
	servo.SetAcceleration(5, 65535) // Full acceleration
	servo.SetVelocity(5, 65535)     // Full speed

	servo.SetPosition(0, 10000) // Set to most right position
	servo.Enable(0)

	servo.SetPosition(5, -9000) // Set to most left position
	servo.Enable(5)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

	servo.Disable(0)
	servo.Disable(5)
}
