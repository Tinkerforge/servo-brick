function octave_example_callback()
    more off;
    
    HOST = "localhost";
    PORT = 4223;
    UID = "5VF5vG"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    servo = java_new("com.tinkerforge.BrickServo", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register "position reached callback" to cb_reached
    % cb_reached will be called every time a position set with
    % set_position is reached
    servo.addPositionReachedCallback(@cb_reached);
    servo.enablePositionReachedCallback();

    % Set velocity to 100°/s. This has to be smaller or equal to 
    % maximum velocity of the servo, otherwise cb_reached will be
    % called too early
    servo.setVelocity(0, 10000); 
    servo.setPosition(0, 9000);
    servo.enable(0);

    input("Press any key to exit...\n", "s");
    ipcon.disconnect();
end

% Use position reached callback to swing back and forth
function cb_reached(e)
    servo = e.getSource();
    if str2double(e.position.toString()) == 9000
        fprintf("Position: 90°, going to -90°\n");
        servo.setPosition(e.servoNum, -9000);
    elseif str2double(e.position.toString()) == -9000
        fprintf("Position: -90°, going to 90°\n");
        servo.setPosition(e.servoNum, 9000);
    else
        fprintf("Error\n"); % Can only happen if another program sets position
    end
end
