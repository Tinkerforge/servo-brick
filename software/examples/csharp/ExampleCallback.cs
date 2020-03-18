using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XXYYZZ"; // Change XXYYZZ to the UID of your Servo Brick

	// Use position reached callback to swing back and forth
	static void PositionReachedCB(BrickServo sender, byte servoNum, short position)
	{
		if(position == 9000)
		{
			Console.WriteLine("Position: 90°, going to -90°");
			sender.SetPosition(servoNum, -9000);
		}
		else if(position == -9000)
		{
			Console.WriteLine("Position: -90°, going to 90°");
			sender.SetPosition(servoNum, 9000);
		}
		else
		{
			// Can only happen if another program sets position
			Console.WriteLine("Error");
		}
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickServo servo = new BrickServo(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Register position reached callback to function PositionReachedCB
		servo.PositionReachedCallback += PositionReachedCB;

		// Enable position reached callback
		servo.EnablePositionReachedCallback();

		// Set velocity to 100°/s. This has to be smaller or equal to the
		// maximum velocity of the servo you are using, otherwise the position
		// reached callback will be called too early
		servo.SetVelocity(0, 10000);
		servo.SetPosition(0, 9000);
		servo.Enable(0);

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();

		servo.Disable(0);

		ipcon.Disconnect();
	}
}
