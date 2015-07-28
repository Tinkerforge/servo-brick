import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickServo;

public class ExampleConfiguration {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;
	private static final String UID = "XYZ"; // Change to your UID

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions you
	//       might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickServo s = new BrickServo(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Configure two servos with voltage 5.5V
		// Servo 1: Connected to port 0, period of 19.5ms, pulse width of 1 to 2ms
		//          and operating angle -100 to 100°
		//
		// Servo 2: Connected to port 5, period of 20ms, pulse width of 0.95 
		//          to 1.95ms and operating angle -90 to 90°
		s.setOutputVoltage(5500);

		s.setDegree((short)0, (short)-10000, (short)10000);
		s.setPulseWidth((short)0, 1000, 2000);
		s.setPeriod((short)0, 19500);
		s.setAcceleration((short)0, 1000); // Slow acceleration
		s.setVelocity((short)0, 0xFFFF); // Full speed

		s.setDegree((short)5, (short)-9000, (short)9000);
		s.setPulseWidth((short)5, 950, 1950);
		s.setPeriod((short)5, 20000);
		s.setAcceleration((short)5, 0xFFFF); // Full acceleration
		s.setVelocity((short)5, 0xFFFF); // Full speed

		s.setPosition((short)0, (short)10000); // Set to most right position
		s.enable((short)0);

		s.setPosition((short)5, (short)-9000); // Set to most left position
		s.enable((short)5);

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
