## Crane's DIY B0XX

![image](https://i.imgur.com/nWhepdX.jpg)

First, credit where credit is due. The B0XX is a product made by:

Hax$ (https://twitter.com/ssbmhax)

Streamlord (https://twitter.com/StreamlordSSBM)

SimpleControllers (https://github.com/SimpleControllers)

Their website, where the B0XX is now available to preorder, is http://b0xx.com/

Here you can find the B0XX manifesto explaining how the B0XX attempts to be in line with the gamecube controller for SSBM, among other references.

Huge shout out to Simple for his guide detailing how to DIY a Smash Box found here. This is how I learned how to wire up the controller. Since then I have made a cleaner and more updated wiring schematic so be sure to follow mine instead. Scroll down to see it.
https://docs.google.com/document/d/1ndV4E_w2ThAv9LpbjEzRDWwMj0uBWB9YqbvkHV35X5w/edit

I've made code for DIYB0XXes that you can find here. It has Melee, PM, and Ultimate modes, and acts very similar to the official B0XX.

https://github.com/Crane1195/DIYB0XX/tree/master/code

This utilizes the Nicohood Nintendo library found here https://github.com/NicoHood/Nintendo

Anyway, enough of the intro, lets get into the build.

### Part List
  * Arduino ~~Mega 2560~~ Micro (Third party ones are cheaper, and work just as well. I have used this one https://amzn.to/3wioVTG)
  * Logic Controller 3.3V - 5V (I used this one https://amzn.to/3m78dSC)
  * 18 Sanwa OBSF-24 buttons
  * GameCube controller cable. This can be either the cable from an OEM controller as shown in this build, a 3rd party controller cable, or a 3rd party extension cable. You can make this cable detachable by following the guide here https://github.com/Crane1195/DIYB0XX/tree/master/Detachable%20Cable
  * The wooden case
  * 15/16" spade bit
  * 18 .110" QDC button wires
  * .110" daisy chain ground wire
  * Male to male jumper wires
  * Heat shrink kit

![image](https://i.imgur.com/A4ihq5s.jpg)

For a joke, I made the greatest piece of tech that the world has ever seen with the shoeb0xx.

Pictured is the wood used to create a more sturdy B0XX. For a thinner, more slim B0XX, you could use metal, plastic, plexi, or plywood for the top. I wanted a sturdy platform so I used 0.75 inch thick wood, as I don't have the tools to work with metal, plastic, etc. The actual size of the B0XX is 16" x 8" x 1.4", however I could not find a piece of wood exactly 8 inches deep, with the closest I found being 9.75". I don't have a saw that can make the cut, so I stuck with the 9.75" depth. I don't mind it, as I can use the extra depth to rest my wrists.

![image](https://i.imgur.com/RY6jwJm.jpg)

I cut the wood to about the correct size using a compound miter saw.

![image](https://i.imgur.com/PBBv8ep.jpg)

Using wood glue and clamps, I joined the sides together.

![image](https://i.imgur.com/MEVnEXd.jpg)

I tested the fit of the top with the curing walls.

![image](https://i.imgur.com/8UplXpV.jpg)

I wood glued the top to the walls, and applied tons of pressure using clamps and some textbooks to join the wood.

![image](https://i.imgur.com/8v1nStO.jpg)

This is the only picture I could find of the finished pure wooden B0XX, with the Arduino that just showed up.

![image](https://i.imgur.com/mLYnbQ7.jpg)

Here's a link to a 17" x 11" PDF of the layout https://drive.google.com/drive/folders/1cv-wkTo0xmuKJOSA2eP_3mJmC4tP5-0d?usp=sharing

I'll be making a folder on this repo soon with CAD files / more detailed instructions for making faceplates.

Taping the template to my B0XX, I marked the center points with a thumbtack.

![image](https://i.imgur.com/yBqV9HB.jpg)

This is the B0XX after cutting the holes with a 15/16" spade bit.

![image](https://i.imgur.com/M9v4XDy.jpg)

I cut a piece of 2' x 2' piece of plywood to be the bottom. As I write this, the paint is drying on the bottom. I did this last.

![image](https://i.imgur.com/lebgWjP.jpg)

I painted the top and sides using multiple layers of spray paint, and then brushed on 3 layers of minwax polycrylic to make it smoother and a bit more protected.

![image](https://i.imgur.com/nJz8njy.jpg)

Next up was the internals. Here you can see the OBSF-24 Blues and the cables I spliced together to connect the buttons to the Arduino.

Edit : Do note, I used to use the Arduino Mega 2560 seen here, and solder spliced wires for the buttons. I recommend not doing this though, and instead using an Arduino Micro like the one linked in the part list. The wiring schematic below has been updated to reflect this.
The reason to pick the Micro instead is that it can work as a controller on PC without a Gamecube Controller to USB adapter. The Mega2560 cannot. Also, just soldering the button wires to the board is a lot easier IMO then solder splicing wires.

Message me if you have any questions about the Arduino Micro.

Custom wire process:
* Bought a pack of 10 double ended cables with .110" QDC's and cut them in half
* Cut male to male jumper wires in half
* Strip the ends of these wires
* Solder the ends together, and put heat shrink over the joint.

Also pictured is a Gamecube controller cable that I desoldered from a dead GCC I bought from ebay.

![image](https://i.imgur.com/eLWxTKm.jpg)

The wiring is messy since I made the cables much longer than they need to be unfortunately. I used a common ground daisy chain cable with 30 .110" connectors, a 5v to 3.3v converter, and a common ground / 5V panel from another project I did.

![image](https://i.imgur.com/9wG8kuw.jpg)

Here is a wiring diagram I made showing how it all works. I previously used a Mega2560, but now I use an Arduino Micro. I've updated the schematic to show this. For more info on how the wiring works, feel free to ask in my [Discord Server](https://www.craneslab.xyz/discord)

![image](https://i.imgur.com/0YlfuPZ.jpg)

First time testing it with my GC! Works flawlessly.

![image](https://i.imgur.com/xnwA6Bq.jpg)

The color scheme was done to match my mechanical keyboard.

![image](https://i.imgur.com/C6hWFK3.jpg)

Another angle

![image](https://i.imgur.com/bWkMDLI.jpg)

Immediately after drilling a 3/8 inch hole for the Arduino's USB port, I remembered that I have a jigsaw. Used a knife to square it out a bit so the usb could fit, but it isn't as clean as a jigsaw would've been.

![image](https://i.imgur.com/UNmyYfB.png)

Here is an extensive part list I made to track how much I spent but I thought I'd share.

![image](https://i.imgur.com/0mqm5v5.jpg)

Once again, huge thanks to Simple for his guide, and assistance when I had a couple of roadblocks, as well as Hax, and Streamlord.

## Support my work

Do note, all Amazon links are affiliated, meaning I get a kickback when you buy anything using these links, and you pay the normal price of the thing. I figure it's a good way for people who want to support me to be able to without any additional cost.

I also set up a donation link for people who appreciate my work and wish to donate. Donations are greatly appreciated, but are far from necessary:

https://www.paypal.com/donate/?hosted_button_id=NFDEML5FKR8N8
