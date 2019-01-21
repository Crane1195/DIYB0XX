# Crane's Detachable Gamecube Cable Guide
![image](https://i.imgur.com/GE0oSzS.jpg)

Here you will find all the information needed to make a detachable cable for a custom Gamecube controller/fightstick.

If you have any questions regarding the process, feel free to message me on Discord @Crane#1195, or join the 20XX Discord here https://discord.gg/6wcEaDU and ask in the DIY #discussion channel.

GCC stands for GameCube Controller. I will use this acryonym a lot.

## Required Parts / Tools
![image](https://i.imgur.com/d0LrhKp.jpg)

- OEM GCC Cable OR GCC extension cable
    - If you have a broken GCC for parts, you can harvest its cable and use that. Otherwise, a GCC extension cable will work. If you have neither, a broken GCC costs much more, but its cable is guaranteed to be high quality, as it is OEM. An extension cable is much cheaper (talking ~$15 dollars compared to ~$3), but some of them are not high quality.
    - I made two custom cables from Kitsch-Bent extension cables and they work perfectly. Here is a link to them, select NGC from the drop down menu. They only cost $2.50, and shipping is ~$5.00, so I got multiple.
    - http://store.kitsch-bent.com/product/extension-cables

- Wire stripper. This is used to remove the protective outer shell of the GCC cable.
    - I used the 8/10 gauge cutter on mine.

- RJ45 Crimp Kit
    - Here's the kit I used. This comes with both the crimping tool, and the connectors.
    - https://www.amazon.com/gp/product/B008UY5WL0/ref=oh_aui_detailpage_o08_s02?ie=UTF8&psc=1

- Neutrik NE8FDP
    - This is the female connector that gets installed in the case of the fightstick; comes in black and silver. Here's a link to the black one I use.
    - https://www.amazon.com/gp/product/B002BEWOYI/ref=oh_aui_detailpage_o08_s01?ie=UTF8&psc=1

- Neutrik NE8MC
    - This is the male connector, that is installed around the custom cable. The cable works without this, but this makes it much more durable and secure; also comes in black and silver. Here's a link to the black one I use.
    - https://www.amazon.com/gp/product/B002BEWKR4/ref=oh_aui_detailpage_o08_s00?ie=UTF8&psc=1

- Multimeter
    - If you are not using an OEM GCC cable, to be safe, you will need to check which wire is which signal. I will post what my wires are below. If you use a Kitsch-Bent extension, they will likely be the same, but not necessarily. It is possible that they have changed their supplier which would change the wiring.

## Making the Cable

![image](https://i.imgur.com/LQqzNMS.png)

1. Cut the female end off of the extension cable, or take apart a GCC and cut the cable as close to its connector as possible.

![image](https://i.imgur.com/5HPw1Qv.png)

2. Strip off about 1 cm of the outer shell. The wires here are too long, so I trimmed them down as seen below, using a wire cutter.

![image](https://i.imgur.com/wFUA6A8.jpg)

3. Flatten all the wires in a way that makes them the least strained. In the cable, they are in a hexagonal prism formation, so try and keep the left wires close to the left, right to right, and middle to middle.

![image](https://i.imgur.com/Pqwgi6K.jpg)

4. Insert the cables into a connector like so, with each wire going into its own channel.

![image](https://i.imgur.com/J3xk5w4.png)

5. This is the wiring setup I am using. As shown in the graphic on the right, the 8 channels of an RJ45 jack are numbered from left to right when the connector is pointing away from you, and the tab is pointing down.

There are different standards of RJ45, but the T-568B RJ45 cables are what you will probably find when getting an "ethernet" cable, and it is what I have on hand.

Row 2 shows which channels the wires from my GCC extension cable are in, Row 3 shows the T-568B wires, and row 4 shows what    function each wire serves for this cable. I will show how I derived this further down.

![image](https://i.imgur.com/se9NOxf.png)

6. Push the connector into the side of the crimping tool that it fits into (it only fits one way) while keeping the cable pushed all the way into connector. I clamp it down 3 times with full force. The cable should now be clamped down by the plastic connector.

![image](https://i.imgur.com/hin4jyK.jpg)
7. To find which cable does what, I then cut a ethernet cable in half, cut open its out shell, and strip the ends of the wires. I used a 26 gauge wire stripper for this.

![image](https://i.imgur.com/3NI6gs5.jpg)
8. I then plugged the GCC to RJ45 cable and the cut ethernet cable into the Neutrik ethernet passthrough

![image](https://i.imgur.com/6bA8qXR.jpg)
9. Using a multimeter on continuity mode, attach one lead to one of the exposed ethernet wires, and then stick the other lead into the GCC male connector, and find which pin corresponds to which wire.

![image](https://i.imgur.com/xyE5hu6.jpg)
10. To double check this, you can check the wires voltages as well. Using the same setup as before, with GCC to RJ45 to Neutrik to RJ45 to breakout. Make sure the exposed wires stay fanned out like in the picture to prevent a short circuit. Hook up the GCC plug to a GC/Wii/Adapter, and read the difference in voltage between the wires you think are 5V/3.3V/Data and ground. The 5V one will read ~4.7V, the 3.3V one will read ~3.1V, and the data one changes, but is less than ~3.3V and greater than ~0.1V.

Using both of these methods, I derived the chart you see above for my cable. If you use a different extension cable, or a different standard of RJ45 ethernet cable, or different wire order, our charts will not be the same. If you use a Kitsch-Bent extension cable, and line up its wires just like I did, it'll probably be the same, but you should check anyway just to be safe.

![image](https://i.imgur.com/bK22Elt.jpg)
11. Follow the instructions here to install the NE8MC around your new cables RJ45 plug

https://www.neutrik.com/media/8070/download/ethercon-cable-connector-ne8mc.pdf?v=1

## Installation Into a Fightstick

![image](https://i.imgur.com/IVrTkXu.jpg)
12. I used a unibit to drill a ~24mm hole in this aluminum case, inserted the NE8FDP faceplate into the hole, marked where the screw holes should be, and drilled 1/8" holes for them.

![image](https://i.imgur.com/GIs4zBX.jpg)
13. Inside the case, I cut that ethernet breakout cable down very short, trimmed the wires to be just long enough, and then soldered them into place. For more information about this wiring schematic, check out the README here https://github.com/Crane1195/DIYB0XX/edit/master/MiniAluminum/README.md

## Results
![image](https://i.imgur.com/GE0oSzS.jpg)
I ended up making a second one as I wasn't taking pictures as I went for the first one. As previously mentioned, it works without the NE8MC, but I'd still recommend it for a more secure connection.

Once again, let me know on Discord in the 20XX Discord or direct message @Crane#1195 if you have any questions.
