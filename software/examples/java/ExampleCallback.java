import com.tinkerforge.BrickServo;
import com.tinkerforge.IPConnection;

public class ExampleCallback {
	private static final String host = "localhost";
	private static final int port = 4223;
	private static final String UID = "a4LCMm3K2bS"; // Change to your UID

	// Declare servo static, so the listener can use it. In a real program you probably
	// want to make a real listener class (not the anonym inner class) and pass the servo
	// reference to it. But we want to keep the examples as short es possible.
	static BrickServo servo;

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions you
	//       might normally want to catch are described in the commnents below
	public static void main(String args[]) throws Exception {
		// Create connection to brickd
		IPConnection ipcon = new IPConnection(host, port); // Can throw IOException

		servo = new BrickServo(UID); // Create device object

		// Add device to IP connection
		ipcon.addDevice(servo); // Can throw IPConnection.TimeoutException
		// Don't use device before it is added to a connection

		// Add and implement position reached listener 
		// (called if velocity set by setVelocity is reached)
		servo.addListener(new BrickServo.PositionReachedListener() {
			public void positionReached(short servoNum, short position) {
				if(position == 9000) {
					System.out.println("Position: 90°, going to -90°");
					ExampleCallback.servo.setPosition(servoNum, (short)-9000);
				} else if(position == -9000) {
					System.out.println("Position: -90°, going to 90°");
					ExampleCallback.servo.setPosition(servoNum, (short)9000);
				} else {
					// Can only happen if another program sets velocity
					System.out.println("Error"); 
				}
			}
		});

		// Set velocity to 100°/s. This has to be smaller or equal to the
		// maximum velocity of the servo you are using, otherwise the 
		// velocity reached listener will be called too early
		servo.setVelocity((short)0, 10000); 
		servo.setPosition((short)0, (short)9000);
		servo.enable((short)0);

		System.out.println("Press ctrl+c to exit");
		ipcon.joinThread();
	}
}
