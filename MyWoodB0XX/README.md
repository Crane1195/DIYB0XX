## Crane's DIY B0XX

![image](https://i.imgur.com/nWhepdX.jpg)

First, credit where credit is due. The B0XX is a product that will be brought to market soon™ by:

Hax$ (https://twitter.com/ssbmhax)

Streamlord (https://twitter.com/StreamlordSSBM)

SimpleControllers (https://github.com/SimpleControllers)

Their website, where the B0XX is now available to preorder, is http://b0xx.com/


Here you can find the B0XX manifesto explaining how the B0XX attempts to be in line with the gamecube controller for SSBM, as well as the 20XX community Discord where you can keep up to date with the progress of the B0XX development, as well as ask questions to Streamlord or Simple about the B0XX, or myself (Crane) and others any DIY questions.

Here's the Discord invite link https://discord.gg/6wcEaDU

Huge shout out to Simple for his excellent guide detailing how to DIY a Smash Box found here.
https://docs.google.com/document/d/1ndV4E_w2ThAv9LpbjEzRDWwMj0uBWB9YqbvkHV35X5w/edit

His guide is an incredible resource for how the wiring works. I have also added my own wiring schematic to this guide.

Also, a shout out to Snapple and Danny who modified Simples Smash Box Arduino code to be accurate to the B0XX manifesto and work with the B0XX's 2 modifiers. I have modified this code to work with Project M, Smash4, and Smash Ultimate. I have also made 2ip SOCD an option. This code can be found here. Read the README to see my edits, how to select a mode, and an explanation of SOCD.

https://github.com/Crane1195/DIYB0XX/tree/master/code

This utilizes the Nicohood Nintendo library found here https://github.com/NicoHood/Nintendo

Anyway, enough of the intro, lets get into the build.

### Part List
  * Arduino Mega 2560
  * Logic Controller 3.3V - 5V (I used this one https://www.amazon.com/gp/product/B0148BLZGE/ref=oh_aui_search_asin_title?ie=UTF8&psc=1)
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

Here's a link to the template I used. Print the document on 8.5"x11" paper, and cut along the lines to get your 8"x16" template.

https://drive.google.com/file/d/1a7MxgeOgtNVZLJR3XxBTWMSy3c9NhZ1_/view?usp=sharing

Taping the template to my B0XX, I marked the center points with a thumbtack.

![image](https://i.imgur.com/yBqV9HB.jpg)

This is the B0XX after cutting the holes with a 15/16" spade bit.

![image](https://i.imgur.com/M9v4XDy.jpg)

I cut a piece of 2' x 2' piece of plywood to be the bottom. As I write this, the paint is drying on the bottom. I did this last.

![image](https://i.imgur.com/lebgWjP.jpg)

I painted the top and sides using multiple layers of spray paint, and then brushed on 3 layers of minwax polycrylic to make it smoother and a bit more protected.

![image](https://i.imgur.com/nJz8njy.jpg)

Next up was the internals. Here you can see the OBSF-24 Blues and the cables I spliced together to connect the buttons to the Arduino.

Custom wire process:
* Bought a pack of 10 double ended cables with .110" QDC's and cut them in half
* Cut male to male jumper wires in half
* Strip the ends of these wires
* Solder the ends together, and put heat shrink over the joint.

Also pictured is a Gamecube controller cable that I desoldered from a dead GCC I bought from ebay.

![image](https://i.imgur.com/eLWxTKm.jpg)

The wiring is messy since I made the cables much longer than they need to be unfortunately. I used a common ground daisy chain cable with 30 .110" connectors, a 5v to 3.3v converter, and a common ground / 5V panel from another project I did.

![image](https://i.imgur.com/z4oZP2O.jpg)

Here is a wiring diagram I made showing how it all works. For more info on how the wiring works, check out Simple's guide linked above, message me on Discord, or join the 20XX Discord from the link above. @Crane#1195 is my ID.

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

Once again, huge thanks to Simple for his guide, and assistance when I had a couple of roadblocks, as well as Hax, and Streamlord. We are all on the Discord which can be found at http://b0xx.com/ (or above) if you have any questions, or want to keep up with the actual B0XX's development.
