import com.tinkerforge.BrickServo;
import com.tinkerforge.IPConnection;
import com.tinkerforge.TinkerforgeException;

public class ExampleCallback {
	private static final String host = "localhost";
	private static final int port = 4223;
	private static final String UID = "a4LCMm3K2bS"; // Change to your UID

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions you
	//       might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		// Note: Declare servo final, so the listener can access it
		final BrickServo servo = new BrickServo(UID, ipcon); // Create device object

		ipcon.connect(host, port); // Connect to brickd
		// Don't use device before ipcon is connected

		// Add and implement position reached listener 
		// (called if velocity set by setVelocity is reached)
		servo.addPositionReachedListener(new BrickServo.PositionReachedListener() {
			public void positionReached(short servoNum, short position) {
				if(position == 9000) {
					System.out.println("Position: 90°, going to -90°");
					try {
						servo.setPosition(servoNum, (short)-9000);
					} catch(TinkerforgeException e) {
					}
				} else if(position == -9000) {
					System.out.println("Position: -90°, going to 90°");
					try {
						servo.setPosition(servoNum, (short)9000);
					} catch(TinkerforgeException e) {
					}
				} else {
					// Can only happen if another program sets velocity
					System.out.println("Error"); 
				}
			}
		});

		servo.enablePositionReachedCallback();

		// Set velocity to 100°/s. This has to be smaller or equal to the
		// maximum velocity of the servo you are using, otherwise the 
		// velocity reached listener will be called too early
		servo.setVelocity((short)0, 10000); 
		servo.setPosition((short)0, (short)9000);
		servo.enable((short)0);

		System.console().readLine("Press key to exit\n");
		ipcon.disconnect();
	}
}
