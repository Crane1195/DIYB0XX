# DIYGCC v1.209 code by Crane.

This is code designed with 16 mhz Arduinos in mind such as the Arduino Mega 2560, Arduino Micro, Arduino Nano, etc.

Release Page: https://github.com/Crane1195/DIYB0XX/releases

## Versions

- `DIYGCC_GC`
  - __**Using:**__
    - Mega2560, Nano, Uno
    - [GameCube circuit](https://cdn.discordapp.com/attachments/557665530677559307/680513973694627847/micro_diyb0xx_schematic.png)
  - __**Supports:**__
    - GameCube/Wii/GCC to USB adapter

- `DIYGCC_GC_And_USB`
  - __**Using:**__
    - Micro, Leonardo, Pro Micro
    - [GameCube circuit](https://cdn.discordapp.com/attachments/557665530677559307/680513973694627847/micro_diyb0xx_schematic.png)
  - __**Supports:**__
    - GameCube/Wii/GCC to USB adapter
    - PC via a USB cable

- `DIYGCC_USB`
  - __**Using:**__
    - Micro, Leonardo
  - __**Supports:**__
    - PC via a USB cable

- `DIYGCC_USB_ProMicro`
  - __**Using:**__
    - Pro Micro
  - __**Supports:**__
    - PC via a USB cable

- `DIYGCC_USB_Switch` - [Read this README for instructions](https://github.com/Crane1195/DIYB0XX/blob/master/code/DIYGCC_USB_Switch_Beta/README.md)
  - __**Using:**__
    - Micro, Leonardo, Pro Micro
  - __**Supports:**__
    - Switch via a USB cable

- `Smashbox`
  - __**Using:**__
    - Hitbox Smashbox
  - __**Supports:**__
    - GameCube/Wii/GCC to USB adapter
  - Here is a tutorial for how to flash it to a Smashbox. Use the code from the most recent release on this repo, as it is the most up to date.
https://github.com/zandm7/DIY-SmashB0XX/blob/master/code/README.md

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
Currently there are 4 game profiles. Melee, Ultimate, PM, and RoA. While plugging in the controller:
* Hold no buttons for Melee.
* Hold B for Ultimate.
* Hold X for PM.
* Hold Z for RoA (only on PC over USB)

## USB Mode
If you are using the firmware with both GC and PC support, hold C-Down while plugging in to enter PC mode.

If you are using any PC supporting firmware, hold ModY on plugin to enter keyboard mode.

## DPAD Toggle
DPAD is enabled by holding ModX and ModY and pressing C-Up/down/left/right.

## Contact info
Let me know if you have any issues with the code in my Discord Server:
https://craneslab.xyz/discord

### Support my work

Do note, all Amazon links are affiliated, meaning I get a kickback when you buy anything using these links, and you pay the normal price of the thing. I figure it's a good way for people who want to support me to be able to without any additional cost.

I set up a donation link for people who appreciate my work and wish to donate. Donations are greatly appreciated, but are far from necessary:

https://www.paypal.com/donate/?hosted_button_id=NFDEML5FKR8N8
