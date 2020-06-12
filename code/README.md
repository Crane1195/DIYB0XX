DIY B0XX v1.202 code by Crane.

This code utilizes Nicohood's Nintendo library.

This is code designed with 16 mhz Arduinos in mind such as the Arduino Mega 2560, Arduino Micro, Arduino Nano, etc. A version of this code is available with native USB joystick support and nunchuk support for controllers using the 32u4 chip such as my Arduino Micro based GCCPCB.

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

You can change which is loaded with no button press at line 59 (and its SOCD at line 60), and which are loaded with button presses starting at line 113. You can change the button required by changing whats inside the parenthesis of `if (digitalRead(**) == LOW)` as well as the game / SOCD like before.

More profiles can be added easily. Just add another game in the enum game declaration at line 23, add another block for picking a mode via a button press like lines 113-117, and everywhere you see a if(currentGame == XXXXX), you will need to add a code block like it for the new game mode. From there you can edit the coords for that mode.

## DPAD Toggle Button / Switch
Normally the DPAD is enabled by holding Mod1 and Mod2 and pressing C-Up/down/left/right. If instead you would rather have a switch or a button do this, follow these steps.
* Uncomment line 84, and change XX to whatever pin you have your switch / button plugged into.
* Uncomment line 109, this sets that pin to the correct mode.
* Uncomment line 148, this sets a boolean to true if the button is pressed or the switch is closed.
* Comment out line 523, this is the normal way DPAD is enabled.
* Uncomment line 524, this enables the DPAD code when the button is pressed or switch is closed.

## Contact info

Let me know if you have any issues with the code, or any suggestions for the Ultimate/PM modes, as they are less concrete.

Discord : @Crane#1195
