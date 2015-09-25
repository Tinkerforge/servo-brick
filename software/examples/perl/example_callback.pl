#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickServo;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XXYYZZ'; # Change to your UID

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
our $servo = Tinkerforge::BrickServo->new(&UID, $ipcon); # Create device object

# Use position reached callback to swing back and forth
sub cb_position_reached
{
    my ($servo_num, $position) = @_;

    if ($position == 9000)
    {
        print "Position: 90°, going to -90°\n";
        $servo->set_position($servo_num, -9000);
    }
    elsif ($position == -9000)
    {
        print "Position: -90°, going to 90°\n";
        $servo->set_position($servo_num, 9000);
    }
    else
    {
        print "Error\n"; # Can only happen if another program sets position
    }
}

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Register position reached callback to subroutine cb_position_reached
$servo->register_callback($servo->CALLBACK_POSITION_REACHED, 'cb_position_reached');

# Enable position reached callback
$servo->enable_position_reached_callback();

# Set velocity to 100°/s. This has to be smaller or equal to the
# maximum velocity of the servo you are using, otherwise the position
# reached callback will be called too early
$servo->set_velocity(0, 10000);
$servo->set_position(0, 9000);
$servo->enable(0);

print "Press key to exit\n";
<STDIN>;
$servo->disable(0);
$ipcon->disconnect();
