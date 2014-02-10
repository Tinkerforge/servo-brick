#!/usr/bin/perl  

use Tinkerforge::IPConnection;
use Tinkerforge::BrickServo;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => '5VF5vG'; # Change to your UID

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
our $servo = Tinkerforge::BrickServo->new(&UID, $ipcon); # Create device object

# Use position reached callback to swing back and forth
sub cb_reached
{
    my ($servo_num, $position) = @_;

    if ($position == 9000)
    {
        print "\nPosition: 90°, going to -90°\n";
        $servo->set_position($servo_num, -9000);
    }
    elsif ($position == -9000)
    {
        print "\nPosition: -90°, going to 90°\n";
        $servo->set_position($servo_num, 9000);
    }
    else
    {
        print "\nError\n"; # Can only happen if another program sets position
    }
}

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Register "position reached callback" to cb_reached
# cb_reached will be called every time a position set with
# set_position is reached
$servo->register_callback($servo->CALLBACK_POSITION_REACHED, 'cb_reached');
$servo->enable_position_reached_callback();

# Set velocity to 100°/s. This has to be smaller or equal to 
# maximum velocity of the servo, otherwise cb_reached will be
# called too early
$servo->set_velocity(0, 10000) ;
$servo->set_position(0, 9000);
$servo->enable(0);

print "\nPress any key to exit...\n";
<STDIN>;
$ipcon->disconnect();

