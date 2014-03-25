function matlab_example_callback
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickServo;

    HOST = 'localhost';
    PORT = 4223;
    UID = '5VF5vG'; % Change to your UID
    
    ipcon = IPConnection(); % Create IP connection
    global servo;
    servo = BrickServo(UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register "position reached callback" to cb_reached
    % cb_reached will be called every time a position set with
    % set_position is reached
    set(servo, 'PositionReachedCallback', @(h, e)cb_reached(e.servoNum, e.position));
    servo.enablePositionReachedCallback();

    % Set velocity to 100°/s. This has to be smaller or equal to 
    % maximum velocity of the servo, otherwise cb_reached will be
    % called too early
    servo.setVelocity(0, 10000); 
    servo.setPosition(0, 9000);
    servo.enable(0);

    input('\nPress any key to exit...\n', 's');
    ipcon.disconnect();
end

% Use position reached callback to swing back and forth
function cb_reached(servo_num, position)
    global servo;
    if position == 9000
        fprintf('Position: 90°, going to -90°\n');
        servo.setPosition(servo_num, -9000);
    elseif position == -9000
        fprintf('Position: -90°, going to 90°\n');
        servo.setPosition(servo_num, 9000);
    else
        fprintf('Error\n'); % Can only happen if another program sets position
    end
end
