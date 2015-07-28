using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change to your UID

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickServo s = new BrickServo(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Configure two servos with voltage 5.5V
		// Servo 1: Connected to port 0, period of 19.5ms, pulse width of 1 to 2ms
		//          and operating angle -100 to 100°
		//
		// Servo 2: Connected to port 5, period of 20ms, pulse width of 0.95 
		//          to 1.95ms and operating angle -90 to 90°
		s.SetOutputVoltage(5500);

		s.SetDegree(0, -10000, 10000);
		s.SetPulseWidth(0, 1000, 2000);
		s.SetPeriod(0, 19500);
		s.SetAcceleration(0, 1000); // Slow acceleration
		s.SetVelocity(0, 0xFFFF); // Full speed

		s.SetDegree(5, -9000, 9000);
		s.SetPulseWidth(5, 950, 1950);
		s.SetPeriod(5, 20000);
		s.SetAcceleration(5, 0xFFFF); // Full acceleration
		s.SetVelocity(5, 0xFFFF); // Full speed

		s.SetPosition(0, 10000); // Set to most right position
		s.Enable(0);

		s.SetPosition(5, -9000); // Set to most left position
		s.Enable(5);

		System.Console.WriteLine("Press enter to exit");
		System.Console.ReadLine();
		ipcon.Disconnect();
	}
}
