using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "a4LCMm3K2bS"; // Change to your UID

	private static BrickServo servo;

	// Callback function for distance callback (parameter has unit mm)
	static void ReachedCB(byte servoNum, short position)
	{
		if(position == 9000)
		{
			System.Console.WriteLine("Position: 90°, going to -90°");
			servo.SetPosition(servoNum, -9000);
		}
		else if(position == -9000)
		{
			System.Console.WriteLine("Position: -90°, going to 90°");
			servo.SetPosition(servoNum, 9000);
		}
		else
		{
			// Can only happen if another program sets position
			System.Console.WriteLine("Error");
		}
	}

	static void Main() 
	{
		IPConnection ipcon = new IPConnection(HOST, PORT); // Create connection to brickd
		servo = new BrickServo(UID); // Create device object
		ipcon.AddDevice(servo); // Add device to ip connection
		// Don't use device before it is added to a connection


		// Register "position reached callback" to ReachedCB
		// ReachedCB will be called every time a position set with
		// SetPosition is reached
		servo.RegisterCallback(new BrickServo.PositionReached(ReachedCB));

		// Set velocity to 100°/s. This has to be smaller or equal to 
		// maximum velocity of the servo, otherwise ReachedCB will be
		// called too early
		servo.SetVelocity(0, 10000);
		servo.SetPosition(0, 9000);
		servo.Enable(0);

		System.Console.WriteLine("Press ctrl+c to exit");
		ipcon.JoinThread();
    }
}
