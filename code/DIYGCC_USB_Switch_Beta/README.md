## Switch USB Beta Branch

This firmware is a beta version of my code which works on the Switch over USB courtesy of Jas2o's fork of MHeironimus' Arduino Joystick Library.

You can find this library here: https://github.com/Jas2o/Leonardo-Switch-Controller

It is being redistrubed in this repository following the GNU LGPL v3.0 license. See the LICENSE file in this folder for what that entails.

GameCube functionality is not present on this patch, and the Switch support breaks PC support at the moment. It may be possible to have both working on the same firmware in the future though.

## Installation Instructions

Download the latest release of this code from here:
https://github.com/Crane1195/diyb0xx/releases

Copy the `boards.txt` file found in the release to this file path in your Arduino installation.

![image](https://cdn.discordapp.com/attachments/718166387691880548/827945105796628520/unknown-14.png)

Open `DIYGCC_USB_Switch_Beta.ino` in the Arduino IDE, and select Leonardo Pokken from the boards menu.

![image](https://cdn.discordapp.com/attachments/718166387691880548/827945403898396722/unknown-26.png)

Plug in the Arduino. Close and reopen this menu and you should see a new com port, this is your Arduino. Select that port.

![image](https://cdn.discordapp.com/attachments/718166387691880548/827945492335951922/unknown-21.png)

Modify the pinout section of the code to match your pinout.

![image](https://cdn.discordapp.com/attachments/718166387691880548/827945614377091122/unknown-30.png)

Press upload.

![image](https://cdn.discordapp.com/attachments/718166387691880548/827945729250820106/unknown-28.png)

If you encounter any errors when installing this firmware, feel free to contact me in my [Discord Server](https://www.craneslab.xyz/discord).

## Support my work

Do note, all Amazon links are affiliated, meaning I get a kickback when you buy anything using these links, and you pay the normal price of the thing. I figure it's a good way for people who want to support me to be able to without any additional cost.

I set up a donation link for people who appreciate my work and wish to donate. Donations are greatly appreciated, but are far from necessary:

https://www.paypal.com/donate/?hosted_button_id=NFDEML5FKR8N8
