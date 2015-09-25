import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickServo;
import com.tinkerforge.TinkerforgeException;

public class ExampleCallback {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;
	private static final String UID = "XXYYZZ"; // Change to your UID

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		// Note: Declare servo as final, so the listener can access it
		final BrickServo servo = new BrickServo(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Use position reached callback to swing back and forth
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

		// Enable position reached callback
		servo.enablePositionReachedCallback();

		// Set velocity to 100°/s. This has to be smaller or equal to the
		// maximum velocity of the servo you are using, otherwise the position
		// reached callback will be called too early
		servo.setVelocity((short)0, 10000);
		servo.setPosition((short)0, (short)9000);
		servo.enable((short)0);

		System.out.println("Press key to exit"); System.in.read();
		servo.disable((short)0);
		ipcon.disconnect();
	}
}
