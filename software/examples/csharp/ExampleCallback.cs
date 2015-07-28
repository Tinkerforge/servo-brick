using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change to your UID

	// Use position reached callback to swing back and forth
	static void ReachedCB(BrickServo sender, byte servoNum, short position)
	{
		if(position == 9000)
		{
			System.Console.WriteLine("Position: 90°, going to -90°");
			sender.SetPosition(servoNum, -9000);
		}
		else if(position == -9000)
		{
			System.Console.WriteLine("Position: -90°, going to 90°");
			sender.SetPosition(servoNum, 9000);
		}
		else
		{
			// Can only happen if another program sets position
			System.Console.WriteLine("Error");
		}
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickServo servo = new BrickServo(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Register "position reached callback" to ReachedCB
		// ReachedCB will be called every time a position set with
		// SetPosition is reached
		servo.PositionReached += ReachedCB;
		servo.EnablePositionReachedCallback();

		// Set velocity to 100°/s. This has to be smaller or equal to 
		// maximum velocity of the servo, otherwise ReachedCB will be
		// called too early
		servo.SetVelocity(0, 10000);
		servo.SetPosition(0, 9000);
		servo.Enable(0);

		System.Console.WriteLine("Press enter to exit");
		System.Console.ReadLine();
		ipcon.Disconnect();
	}
}
