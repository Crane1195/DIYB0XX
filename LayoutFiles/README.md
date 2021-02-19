# Layout Files

I've made a lot of layout files over time and figured it would make sense to compile some of the useful ones here. Let me know if you interested in any other layout files, I might have made them already and I can add them here.

The PDF folder is for people who want to print the layout to use as a template.

The DXF folder is for people who want to modify the layouts, or get them laser cut.

## USA Laser Cutting Recommendations

https://www.pololu.com/product/749 for laser cutting acrylic and wood, they are very fairly priced and quite quick.

https://sendcutsend.com/ for laser cutting metals, they have incredible prices for laser cut metals, are super fast, and offer free shipping.

## Top Panel Laser Cutting Advice

### MX Form Factor Keyboard Switches

If you are using MX like keyboard switches, I recommend using a 1.5mm steel switch plate from SendCutSend. 1.5mm is what you need for the switches to snap in properly, and steel is super rigid and not too expensive. Acrylic and wood would be far too flimsy, aluminum would probably be fine but a bit less rigid than steel, and brass/carbon fiber would work well but be far more expensive.

### Snap In Buttons

If you are using 24mm snap in buttons (like Sanwa OBSX-24) and an acrylic or wood top panel from Pololu:

Sanwas will only clip into panels that are <= 3mm thick with 24mm holes. Just a 3mm thick top acrylic panel though will flex in the middle. To solve this, I add another 3mm panel beneath the top panel. This one has 26mm holes, which allows the buttons to still clip in.

```
Top Top panel    - 3mm thick - 24mm holes
Bottom Top Panel - 3mm thick - 26mm holes
```

If you are using 24mm snap in buttons (like Sanwa OBSX-24) with an aluminum or ACM top panel from SendCutSend, ~3mm is enough to not flex at all.

### Screw in Buttons

If you are using Crowns screw in buttons you could use just one 6mm acrylic or wood panel with 24mm holes rather than two 3mm ones. (Unless you want art, then you'd want a clear 3mm panel and some color 3mm panel)

And like with snap in buttons, just a 3mm aluminum or ACM panel is fine too.
