import com.tinkerforge.BrickServo;
import com.tinkerforge.IPConnection;

public class PWMGenerator {

		private static final String HOST = "localhost";
    private static final int PORT = 4223;

		// Change XXYYZZ to the UID of your Servo Brick
    private static final String UID = "XXYYZZ";

    private static int PWM_FREQUENCY = 175000; // in Hz [15Hz to 1MHz]
    private static int PWM_DUTY_CYCLE = 100; // in % [0% to 100%]

    private static short SERVO_NUMBER = 0; // [0 to 6]

		// Note: To make the example code cleaner we do not handle exceptions. Exceptions
		//       you might normally want to catch are described in the documentation
    public static void main(String args[]) throws Exception {
        IPConnection ipcon = new IPConnection(); // Create IP connection
        BrickServo servo = new BrickServo(UID, ipcon); // Create device object

        ipcon.connect(HOST, PORT); // Connect to brickd
				// Don't use device before ipcon is connected

        // Set degree range to 0-100, this will allow to set the PWM duty cycle in 1% steps
        servo.setDegree(SERVO_NUMBER, (short) 0, (short) 100);

        // Set PWM frequency (1-65535µs == 1MHz-15Hz)
        int period = 1000000 / PWM_FREQUENCY;
        if (period < 1) {
            period = 1; // 1MHz
        } else if (period > 65535) {
            period = 65535; // ~15Hz
        }
        servo.setPulseWidth(SERVO_NUMBER, 0, period);
        servo.setPeriod(SERVO_NUMBER, period);

        // Fast acceleration and full speed
        servo.setAcceleration(SERVO_NUMBER, 65535);
        servo.setVelocity(SERVO_NUMBER, 65535);

        // Set PWM duty cycle (0-100 %)
        int position = PWM_DUTY_CYCLE;
        if (position < 0) {
            position = 0;
        } else if (position > 100) {
            position = 100;
        }
        servo.setPosition(SERVO_NUMBER, (short) position);

        // Enable PWM signal
        servo.enable(SERVO_NUMBER);

        System.out.println("Press key to exit"); System.in.read();
        servo.disable((short)0);
        ipcon.disconnect();
    }
}
