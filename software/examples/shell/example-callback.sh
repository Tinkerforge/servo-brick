#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XXYYZZ # Change to your UID

# Use position reached callback to swing back and forth
tinkerforge dispatch servo-brick $uid position-reached\
 --execute "if   [ {position} -eq  9000 ];
            then echo 'Position: 90°, going to -90°' && tinkerforge call servo-brick $uid set-position 0 -9000;
            elif [ {position} -eq -9000 ];
            then echo 'Position: -90°, going to 90°' && tinkerforge call servo-brick $uid set-position 0 9000;
            else echo error; fi" &

# Enable position reached callback
tinkerforge call servo-brick $uid enable-position-reached-callback

# Set velocity to 100°/s. This has to be smaller or equal to the
# maximum velocity of the servo you are using, otherwise the position
# reached callback will be called too early
tinkerforge call servo-brick $uid set-velocity 0 10000
tinkerforge call servo-brick $uid set-position 0 9000
tinkerforge call servo-brick $uid enable 0

echo "Press key to exit"; read dummy

tinkerforge call servo-brick $uid disable 0

kill -- -$$ # Stop callback dispatch in background
