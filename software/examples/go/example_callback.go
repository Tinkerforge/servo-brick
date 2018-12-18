package main

import (
	"fmt"
	"github.com/tinkerforge/go-api-bindings/ipconnection"
    "github.com/tinkerforge/go-api-bindings/servo_brick"
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

	servo.RegisterPositionReachedCallback(func(servoNum uint8, position int16) {
		if position == 9000 {
            fmt.Println("Position: 90°, going to -90°")
            servo.SetPosition(servoNum, -9000)
        } else if position == -9000 {
            fmt.Println("Position: -90°, going to 90°")
            servo.SetPosition(servoNum, 9000)
        } else {
            // Can only happen if another program sets position
            fmt.Println("Error");
        }
	})

	// Enable position reached callback
	servo.EnablePositionReachedCallback()

	// Set velocity to 100°/s. This has to be smaller or equal to the
	// maximum velocity of the servo you are using, otherwise the position
	// reached callback will be called too early
	servo.SetVelocity(0, 10000)
	servo.SetPosition(0, 9000)
	servo.Enable(0)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

	servo.Disable(0)
	ipcon.Disconnect()
}
