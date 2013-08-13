#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=XYZ

# enable position reached callback
tinkerforge call servo-brick $uid enable-position-reached-callback --expect-response

# set velocity to 100°/s. This has to be smaller or equal to
# maximum velocity of the servo, otherwise cb_reached will be
# called to early.
tinkerforge call servo-brick $uid set-velocity --expect-response 0 10000
tinkerforge call servo-brick $uid set-position --expect-response 0 9000
tinkerforge call servo-brick $uid enable --expect-response 0

echo 222
# use position reached callback to swing back and forth
tinkerforge dispatch servo-brick $uid position-reached\
 --execute "if   [ {position} -eq  9000 ];
            then echo 'Position: 90°, going to -90°' && tinkerforge call servo-brick $uid set-position 0 -9000;
            elif [ {position} -eq -9000 ];
            then echo 'Position: -90°, going to 90°' && tinkerforge call servo-brick $uid set-position 0 9000;
            else echo error; fi"
