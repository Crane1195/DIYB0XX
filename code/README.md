DIY B0XX v1.0 code by Crane.
This code utilizes Nicohood's Nintendo library.

As of July 4th 2019 : I rewrote the entire program from scratch to increase efficiency, increase readability, to make adding new profiles easier, to improve the Smash Ultimate mode

This is code designed with 16 mhz Arduinos in mind such as the Arduino Mega 2560, Arduino Micro, Arduino Nano, etc. A version of this code is available with native USB joystick support and nunchuk support for controllers using the 32u4 chip such as my Arduino Micro based GCCPCB. You can probably use it on a Micro/Leonardo/Pro Micro DIY, but do so at your own risk.

Heres a link to it : https://github.com/Crane1195/GCCPCB/tree/master/code

## SOCD Options
You can choose between 2ip, 2ip with no reactivation, and neutral to resolve simultaneous opposite cardinal direction (SOCD) inputs. This applies to both the control and c stick.

#### 2ip works like this:
* Press left. Character moves left.
* While still pressing left, press right. Character moves right.
* While still pressing left, stop pressing right. Character moves left again.

#### 2ip with no reactivation (The method the B0XX uses) works like this:
* Press left. Character moves left.
* While still pressing left, press right. Character moves right.
* While still pressing left, stop pressing right. Character will not move.

#### Neutral works like this:
* Press left. Character moves left.
* While still pressing left, press right. Character stops moving.
* While still pressing left, stop pressing right. Character moves left again.

## Game profiles
Currently there are 3 game profiles. Melee, Ultimate, and PM.
* One of these modes loads when the controller is plugged in while holding no buttons, by default this is Melee.
* Another mode loads when the controller is plugged in while holding B, by default this is Ultimate.
* The third mode loads when the controller is plugged in while holding X, by default this is PM.

You can choose the SOCD method for each profile separately.

You can change which is loaded with no button press at line 59 (and its SOCD at line 60), and which are loaded with button presses starting at line 110. You can change the button required by changing whats inside the parenthesis of `if (digitalRead(**) == LOW)` as well as the game / SOCD like before.

More profiles can be added easily. Just add another game in the enum game declaration at line 23, add another block for picking a mode via a button press like lines 110-114, and everywhere you see a if(currentGame == XXXXX), you will need to add a code block like it for the new game mode. From there you can edit the coords for that mode.

Let me know if you have any issues with the code, or any suggestions for the Ultimate/PM modes, as they are less concrete.
