import com.tinkerforge.BrickServo;
import com.tinkerforge.IPConnection;

public class ExampleConfiguration {
	private static final String host = "localhost";
	private static final int port = 4223;
	private static final String UID = "a4LCMm3K2bS"; // Change to your UID
	
	// Note: To make the example code cleaner we do not handle exceptions. Exceptions you
	//       might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickServo servo = new BrickServo(UID, ipcon); // Create device object

		ipcon.connect(host, port); // Connect to brickd
		// Don't use device before ipcon is connected

		// Configure two servos with voltage 5.5V
		// Servo 1: Connected to port 0, period of 19.5ms, pulse width of 1 to 2ms
		//          and operating angle -100 to 100°
		//
		// Servo 2: Connected to port 5, period of 20ms, pulse width of 0.95 
		//          to 1.95ms and operating angle -90 to 90°
		servo.setOutputVoltage(5500);

		servo.setDegree((short)0, (short)-10000, (short)10000);
		servo.setPulseWidth((short)0, 1000, 2000);
		servo.setPeriod((short)0, 19500);
		servo.setAcceleration((short)0, 1000); // Slow acceleration
		servo.setVelocity((short)0, 0xFFFF); // Full speed

		servo.setDegree((short)5, (short)-9000, (short)9000);
		servo.setPulseWidth((short)5, 950, 1950);
		servo.setPeriod((short)5, 20000);
		servo.setAcceleration((short)5, 0xFFFF); // Full acceleration
		servo.setVelocity((short)5, 0xFFFF); // Full speed

		servo.setPosition((short)0, (short)10000); // Set to most right position
		servo.enable((short)0);

		servo.setPosition((short)5, (short)-9000); // Set to most left position
		servo.enable((short)5);

		System.console().readLine("Press key to exit\n");
		ipcon.disconnect();
	}
}
