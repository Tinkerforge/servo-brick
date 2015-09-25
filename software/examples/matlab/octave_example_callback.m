function octave_example_callback()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XXYYZZ"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    servo = java_new("com.tinkerforge.BrickServo", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register position reached callback to function cb_position_reached
    servo.addPositionReachedCallback(@cb_position_reached);

    % Enable position reached callback
    servo.enablePositionReachedCallback();

    % Set velocity to 100°/s. This has to be smaller or equal to the
    % maximum velocity of the servo you are using, otherwise the position
    % reached callback will be called too early
    servo.setVelocity(0, 10000);
    servo.setPosition(0, 9000);
    servo.enable(0);

    input("Press key to exit\n", "s");
    servo.disable(0);
    ipcon.disconnect();
end

% Use position reached callback to swing back and forth
function cb_position_reached(e)
    servo = e.getSource();
    position = java2int(e.position);

    if position == 9000
        fprintf("Position: 90°, going to -90°\n");
        servo.setPosition(java2int(e.servoNum), -9000);
    elseif position == -9000
        fprintf("Position: -90°, going to 90°\n");
        servo.setPosition(java2int(e.servoNum), 9000);
    else
        fprintf("Error\n"); % Can only happen if another program sets position
    end
end

function int = java2int(value)
    if compare_versions(version(), "3.8", "<=")
        int = value.intValue();
    else
        int = value;
    end
end
