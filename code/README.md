# DIYGCC v1.209 code by Crane.

# Deprecated

This firmware has been succeeded by [CL-FW](https://github.com/Crane1195/CL-FW). Consult the CL-FW README for more information and a new installation guide.

---

This is code designed with 16 mhz Arduinos in mind such as the Arduino Mega 2560, Arduino Micro, Arduino Nano, etc.

Release Page: https://github.com/Crane1195/DIYB0XX/releases

## Variants

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

## Installation
The firmware currently utilizes Nicohood's Nintendo library found here :

https://github.com/NicoHood/Nintendo

and MHeironimus' Arduino Joystick Library found here :

https://github.com/MHeironimus/ArduinoJoystickLibrary

If this is the first time you have used these libraries, press Clone or download, and press Download ZIP on these repos.

Download YourVariant.zip from the latest release here https://github.com/Crane1195/DIYB0XX/releases. Copy the YourVariant folder out from this .zip to a convenient location. You can place the ArduinoJoystickLibrary-master.zip file and the Nintendo-master.zip file here too.

![image](https://i.imgur.com/2sbIDBU.png)

Your folder should look something like this.

Another thing you will need is the Arduino IDE, which is found here :

https://www.arduino.cc/en/Main/Software

![image](https://i.imgur.com/CHpg0XW.png)

After installing the Arduino IDE, open YourVariant.ino within it, and add the libraries using this menu option.

![image](https://i.imgur.com/naC2TpM.png)

Navigate to where you have the YourVariant folder, and double click one, then repeat the process for the other. You will only need to install these libraries and the Arduino IDE once. For future updates, you will just have to download the new code, and upload it using the method below.

![image](https://i.imgur.com/SV0kNzA.png)

In this menu, change the board to be whichever board you are using. If you are using a Pro Micro you can just use the Micro option. 

![image](https://i.imgur.com/9tYGmu7.png)

Before plugging in the Arduino, look and see what Ports are there. On this machine, there is COM1, but on my other machine, I had none.

![image](https://i.imgur.com/IvchWFZ.png)

Plug in the board via USB, and check this menu again, you should see another COM port show up. For both of my computers, it will also say "Arduino Micro" next to the port, but it is possible it will not. What should always happen though, is a port should show up when you plug in the board, and should disappear when you unplug the board (make sure you close the menu and reopen it to refresh the list). This port is the port for your Arduino, so select it.

![image](https://i.imgur.com/SLpPgmo.png)

If you are using GC firmware, you will need to change the value here to match which pin you connected your data line to.

![image](https://i.imgur.com/yFiT9X9.png)

On any of these firmwares, you will need to change this pinout section to match which pins you connected your buttons to.

![image](https://i.imgur.com/dayg2lX.png)

Click this button to upload the firmware to the Arduino.

![image](https://i.imgur.com/CY3OeIv.png)

This section of the IDE will say Compiling Sketch, then Uploading, then Done Uploading. When it says Done Uploading, the board is ready to use, and can be unplugged.

## Contact info
Let me know if you have any issues with the code in my Discord Server:
https://craneslab.xyz/discord

## Support my work

Do note, all Amazon links are affiliated, meaning I get a kickback when you buy anything using these links, and you pay the normal price of the thing. I figure it's a good way for people who want to support me to be able to without any additional cost.

I set up a donation link for people who appreciate my work and wish to donate. Donations are greatly appreciated, but are far from necessary:

https://www.paypal.com/donate/?hosted_button_id=NFDEML5FKR8N8
