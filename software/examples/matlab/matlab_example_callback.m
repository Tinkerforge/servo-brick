function matlab_example_callback()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickServo;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XXYYZZ'; % Change to your UID

    ipcon = IPConnection(); % Create IP connection
    servo = handle(BrickServo(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register position reached callback to function cb_position_reached
    set(servo, 'PositionReachedCallback', @(h, e) cb_position_reached(e));

    % Enable position reached callback
    servo.enablePositionReachedCallback();

    % Set velocity to 100°/s. This has to be smaller or equal to the
    % maximum velocity of the servo you are using, otherwise the position
    % reached callback will be called too early
    servo.setVelocity(0, 10000);
    servo.setPosition(0, 9000);
    servo.enable(0);

    input('Press key to exit\n', 's');
    servo.disable(0);
    ipcon.disconnect();
end

% Use position reached callback to swing back and forth
function cb_position_reached(e)
    servo = e.getSource();

    if e.position == 9000
        fprintf('Position: 90°, going to -90°\n');
        servo.setPosition(e.servoNum, -9000);
    elseif e.position == -9000
        fprintf('Position: -90°, going to 90°\n');
        servo.setPosition(e.servoNum, 9000);
    else
        fprintf('Error\n'); % Can only happen if another program sets position
    end
end
