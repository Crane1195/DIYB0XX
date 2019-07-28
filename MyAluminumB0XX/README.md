# Crane's DIY Aluminum B0XX
![image](https://i.imgur.com/u44Nq8T.jpg)

The B0XX is a controller designed for Super Smash Brothers Melee, with ergonomics being the number one priority. It is

    Designed by Aziz “Hax$” Al-Yami
    Produced & Engineered by Stephen “Streamlord” Kasmir
    Programmed & Engineered by Kyle “simple” McDowell
    Logo & Art  by Jacqueline "Jisu" Choe

More information regarding the B0XX and links to preorder it are found here

https://b0xx.com/

While my first DIY B0XX project was functional, it had room for improvement. This time, I have chosen to purchase an aluminum case from Digikey to use as the chassis, and I have drawn a face plate, which was laser cut out of acrylic from Pololu. The prefab aluminum case was chosen to make all three dimensions smaller. It is much more portable now as a result. The laser cut acrylic plate has perfectly spaced holes, and is much smoother than the wood coated in polycrylic.

On top of this, I have done two modifications to the design which increase overall functionality.

![image](https://i.imgur.com/LMoBayj.jpg)

The first of which a detachable RJ45 to Gamecube cable, and the second is an internal Gamecube to USB adapter with the extra three ports available to use outside the case.

If you have any questions regarding this build, feel free to ask me in the 20XX Discord's #diy-discussion channel (https://discord.gg/6wcEaDU) or in direct message @Crane#1195 .

## Components

### Aluminum Case
![image](https://i.imgur.com/7dGkZdS.jpg)

The case used for this build is a 12" x 8" x 2" aluminum prefab that I ordered from Digikey.

https://www.digikey.com/product-detail/en/hammond-manufacturing/1444-22/HM267-ND/247996

This case's edges are pretty sharp, the holes on mine did not match up exactly to its datasheet, and it got pretty scratched up while I was modding it, but it is pretty decent for the price of ~$40 dollars shipped.

A bit of sanding solves the sharp edges.

I highly reccomend measuring the holes on your unit if you are making a panel for the top like I did. I might have been unlucky, but it might be normal.

It comes with an adhesive protective film on all sides if I recall correctly. Leave these on the case while working on it.

They also make a similar case to this one, but in a 16" x 8" x 2" form factor. The larger size comes in both aluminum:

https://www.digikey.com/product-detail/en/hammond-manufacturing/1444-26/HM269-ND/247998

and steel:

https://www.digikey.com/product-detail/en/hammond-manufacturing/1441-26BK3/HM1493-ND/460097

I have not used the steel variant, but I would imagine it would be more scratch resistant and probably stronger.

### Laser Cut Acrylic Button Panel
![image](https://i.imgur.com/0ZhgDX8.jpg)

I designed this button panel based on the layout of the MiniB0XX made by Simple. You can find drawing/PDF files of this layout here:

https://github.com/Crane1195/DIYB0XX/tree/master/MyAluminumB0XX/AcrylicPlate

I sent drawing file (.dwg) to Pololu, who have an affordable acrylic laser cutting service that you can find here:

https://www.pololu.com/product/749

![image](https://i.imgur.com/Cc4ZUtd.png)

They have tons of options, and I chose this one. It is a slightly translucent matte finish white panel (the bottom side is glossy, but it is inside the case).

I highly recommend them. I have ordered two panels from them so far, and both turned out perfect. Do note though, this panel is below their minimum cost of $25, so if you have anything else you would like laser cut, they can add that to the order to be cost efficient.

The screw holes in the drawing file I linked is based on the 12" x 8" case's datasheet's screw placements, and as previously mentioned, these did not work perfectly for my case. I had to use different screws and angle them for the top two. Measuring your own case and editing the drawing file would be ideal, and if you do not know how to use a CAD software, or do not have one, I can edit the drawing for you given your measurements. Alternatively you could just roll the dice and hope your case is good enough, or angle screws like I did.

Personally, I use just one 3mm acrylic panel for the top. If you push in the middle of it, there is a bit of flex, but it is not enough to bother me. If this would bother you, or you want to easily use art under the buttons, you can get a second panel, but with 28mm holes to put under the top 24mm holes panel. This way, the buttons snap into the top panel, and just pass through the second. For art, you could get a clear top, and whatever color bottom, and put the art inbetween. Once again, if anyone who can not use a drawing editor wants me to make this into a file, let me know.

### Detachable RJ45 to GCC Cable
![image](https://camo.githubusercontent.com/8c6c392c081724a795778e1a34ffaf427c57ec16/68747470733a2f2f692e696d6775722e636f6d2f4745306f537a532e6a7067)
This is a massive upgrade over the attached cable used previously. Besides the fact that the cable I used was in bad shape and from a beat up OEM controller I found on eBay, an attached cable does not really have anywhere to go outside of a box controller. Wrapping it around damages the cable, and it makes the controller much more of a hassle to travel with. To see how this cable is made, check out this guide I wrote on the topic: https://github.com/Crane1195/DIYB0XX/tree/master/Detachable%20Cable

### Internal GCC to USB adapter
![image](https://i.imgur.com/PZbbE8u.jpg)
This is an interesting addition that could be quite useful for some people, but I am not really one of them. Basically, you take the Nintendo GCC to USB adapter out of its case, solder wires to the pads of a GC port on a Gamecube to USB adapter, and route those to the same lines of your normal GCC cable. What this means is that you can use the controller like a normal Gamecube controller with the RJ45 to GCC cable, or you can plug the GC adapters USB cable into a Switch/WiiU/PC to avoid using an external controller adapter.

To do this, I wanted to remove the gray usb cable to save space in the case, and solder wires to the back of the adapters PCB to access 5v, GND, 3v, and data.

![image](https://i.imgur.com/1AMAWl0.jpg)
Here is a spreadsheet detailing what each pin of the connector / header on board does.

![image](https://i.imgur.com/3algLk9.png)
Basically you want to remove / cut wires 1, 2, and 5, and split the cable in half as seen below.

![image](https://i.imgur.com/XXBmsEZ.jpg)
Here is the finished modified GCC adapter. I forgot to get a labeled pinout of the pads on the back of the adapter as to which is 5v, GND, 3V, and data, so if you want to do something like this, you'll need to use a multimeter continuity test to figure out which is which.

### The Internals
![image](https://i.imgur.com/hmlrhyG.jpg)
Initially, I had used the same Mega2560 and logic converter as before, and soldered each of the GCC adapters lines (5v, GND, 3v, Data) to the RJ45 lines.

### Wiring Schematic
![image](https://i.imgur.com/HH7MXpK.png)
The wiring schematic is the same as my first DIY, but now has the GCC adapters lines attached as well.

### Completed interior
![image](https://i.imgur.com/42vVEyB.jpg)
Not the cleanest thing ever, but here was the completed interior. The left Neutrik is for the Dween, the middle is for the RJ45 Gamecube port, and the right is for the GCC to USB adapter.

### Updated interior
![image](https://i.imgur.com/Yc3b0H8.jpg)
I made a PCB to make building Gamecube controllers a lot easier and to have more features. I call it the GCCPCB. A brief synopsis of the benefits are:

* The entire circuit is all done by the board.
* Buttons don't need to be spliced to jumper cables and can just be plugged into screw terminals.
* It's very compact.
* A port for a detachable cable is built in (either RJ45 or USBC).
* A 10x2 pin connector is on board to passthrough button signals to a Brook board.
* Native PC controller support. No need for a GCC to USB adapter for PC.
* Nunchuk port to use an analog stick instead of the digital stick / modifiers.

If you are interested in finding out more about the GCCPCB, join this discord server and check out #info

discord.gg/P2BxMVY

![image](https://i.imgur.com/yPC4dIC.jpg)
Here is the final interior. I put a four pin header on the board to allow access to the 5V, GND, 3V, and Data lines so I could hook up my GCC to USB adapter. I plugged the GCC adapter into the GCCPCB USB port, which means that it is accessible using a RJ45 to USB cable. The Arduino is plugged into a USB Neutrik, which I use for Native PC control and updating the firmware.

### Conclusion / Contact

Overall, this controller has been a really solid test bench for various projects I've been working on. First the internal USB to GCC adapter, then my mechanical switch boards that I used to replace the Sanwa SW68s (maybe more info on these coming soon, they aren't perfect yet), and now to work on my GCCPCB.

If you have any questions about this build, the GCCPCB, or anything else, feel free to message me on Discord @Crane#1195, or to join my Discord server, discord.gg/P2BxMVY, where I'll be posting updates about the various projects I am working on.
