# Crane's Laser Cut DIY B0XX

![image](https://i.imgur.com/3eXRQtJ.jpg)

The B0XX is a controller designed for Super Smash Brothers Melee, with ergonomics being the number one priority. It is

    Designed by Aziz “Hax$” Al-Yami
    Produced & Engineered by Stephen “Streamlord” Kasmir
    Programmed & Engineered by Kyle “simple” McDowell
    Logo & Art  by Jacqueline "Jisu" Choe

More information regarding the B0XX and links to preorder it are found here

https://b0xx.com/

Up until now, I haven't actually made a "perfect" DIY B0XX, which I define as thin, a spread out layout, and high build quality. I've accomplished these three this time, as well as doing art and using my USB-C GCCPCB for the first time.

## The Laser Cut Case
![image](https://i.imgur.com/MUbdEpq.jpg)
The case is comprised of 5 laser cut layers, all cut by [Pololu](https://www.pololu.com/product/749).

- Bottom Layer      : 1/4" Wood

- Wall Layer 1      : 1/2" Wood

- Wall Layer 2      : 1/2" Wood

- Top support layer : 1/8" Wood. 26mm holes cut for buttons to pass through.

- Top button panel  : 1/8" Transparent cast acrylic. 24mm holes cut for buttons to snap into.

![image](https://i.imgur.com/KVPtz1G.jpg)
Here's a picture of all five layers and the hardware to secure it all.

![image](https://i.imgur.com/sHFcH9h.jpg)
The bottom wall panel has hexagons cut to hold hex nuts within the walls of the case to hold the screws in place. Since the hex nuts are thinner than the wall, I 3d printed hexagon shaped spacers to put underneath the nuts (shoutout to simple for this idea).

![image](https://i.imgur.com/Y9r0cWf.jpg)
The nuts now sit flush with the top of the wall. The second wall is glued on top of this wall, encasing the nuts within the walls.

![image](https://i.imgur.com/riOVcad.jpg)
Here's how it looked after the bottom and the two walls were glued together. The top two panels get screwed into the bottom 3.

![image](https://i.imgur.com/seCmGHT.jpg)
I didn't have a way to perfectly align the layers as they were being glued together, so the layers were about 0.3mm off at various points around the case. If anyone plans on doing a case like this, I reccomend figuring out a way to make sure they are perfectly aligned while gluing to prevent this. If I end up doing this again, I will put the same size hole as in the walls in the bottom panel and put a rod through all the panels holes to try and hold it in place. I'd probably then wood fill in the holes in the bottom panel.

![image](https://i.imgur.com/8W1GNR2.jpg)
I decided to sand the entire thing so that they would be even. This took a long time considering I only have a sanding block.

![image](https://i.imgur.com/iDjXLk8.jpg)
I then put the acrylic panel on it, and went at it again. I got a lot more of the laser burn off this time as well.

![image](https://i.imgur.com/idLWYNo.jpg)
After sanding was done, I used Minwax prestain conditioner, then 2 layers of dark walnut stain, then 3 layers of liquid clear satin polyurethane, then one layer of aerosol polyurethane. Finally I used wood finishing paste wax on top of all that. After all the sanding, polyurethane, and wax, it's about as smooth as my satin hardwood floors.

## Art
![image](https://i.imgur.com/MxC2GOw.jpg)
Next was art. I printed it on 17"x11" paper, used scissors to cut the rounded edges, put it inbetween the two panels, and used an exacto knife to cut out the button holes. I then used the white spacer in the OBSC-24 button to give me a guide for how small the button art had to be. I used a very small pair of scissors to cut the 24mm art cutouts down to the size they needed to be to fit in the buttons. [Here's a rough guide on that if you are interested.](https://support.focusattack.com/hc/en-us/articles/115002742306-Adding-art-to-buttons-101)

## Ports
![image](https://i.imgur.com/dgtR2th.jpg)
I left two gaps in the walls. One for a [USB C feedthrough](https://www.amazon.com/gp/product/B07DFCH4V3/ref=ppx_yo_dt_b_asin_title_o08_s00?ie=UTF8&psc=1), and the other for a [Nunchuk extension cable](https://www.amazon.com/gp/product/B01MYVK56T/ref=ppx_yo_dt_b_asin_title_o07_s00?ie=UTF8&psc=1). The company who makes the USB C feedthrough also makes one with only one port which you can find [here](https://www.amazon.com/USB-Adaptor-Type-Receptacle-FT/dp/B07695JD1Q/ref=sr_1_64?qid=1564507879&s=gateway&sr=8-64&srs=8040557011).

![image](https://i.imgur.com/Ers2BYs.jpg)
I used [this](https://www.amazon.com/Loctite-Fun-Tak-Mounting-2-Ounce-1087306/dp/B001F57ZPW) to secure the USB C feedthrough in place, and the Nunchuk extension is friction fit into place. Both are very secure, and I will eventually get some black PLA and make a spacer above the Nunchuk extension to close that hole.

## Internals
![image](https://i.imgur.com/5R3F9Hd.jpg)
Here you can see the internals. This board is the GCCPCB, made my me. If you are interested in learning more or have any questions about this board and its firmware, feel free to message me about it on Discord @Crane#1195, or to [join my Discord server](discord.gg/P2BxMVY) where I post updates about hardware I am working on or firmware updates.
Here's a brief synopsis of its benefits over my previous method of making DIY Gamecube Controllers.
* The entire circuit is all done by the board.
* Buttons don't need to be spliced to jumper cables and can just be plugged into screw terminals like on a Brook board.
* It's very compact, which is crucial in this build considering how small the interior of the case is (15" x 7" x ~0.9")
* A port for a detachable cable is built in (either RJ45 or USBC). I chose USB C for this build.
* A 10x2 pin connector is on board to passthrough button signals to a Brook board (I won't be doing it for this build)
* Native PC controller support. No need for a GCC to USB adapter for PC.
* Nunchuk port to use an analog stick instead of the digital stick / modifiers.

![image](https://i.imgur.com/3LmkPNO.jpg)
Due to how thin the case interior is, the board and all the patch cables all needed to be in a position that was not directly underneath a button. It took quite a while to actually find a location where this was true, and the spot I picked might be the only spot.

![image](https://i.imgur.com/dGIz1oK.jpg)
Unintentionally, the LED on the board ended up being almost directly under the start button giving it this neat faint glow that only shows up in a dark room.

![image](https://i.imgur.com/DDajy5T.jpg)

![image](https://i.imgur.com/al1c5pm.jpg)

![image](https://i.imgur.com/kn0kdpJ.jpg)
A few more angles.

### Conclusion / Contact
Overall I'm super happy with how this turned out. It isn't perfect, but it is about the best I could have done given my inexperience with fightstick art and laser cutting cases. I learned a lot and would it would definitely be easier the next time I do one like this.

If you have any questions about this build, the GCCPCB, or anything else, feel free to message me on Discord @Crane#1195, or to join my Discord server, discord.gg/P2BxMVY, where I'll be posting updates about the various projects I am working on.
