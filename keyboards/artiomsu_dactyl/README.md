# RP 2040 Handwired Dactyl Manuform 5x7 by ArtiomSu

![header1](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/header.jpg)

This is using the raspberry pi pico micro controller on both halves of the keyboard. 

The dactyl keyboard present in the qmk repo is configured with the pro micro in mind, hence I split this out into its own keyboard directory. Also so I can include the build guide. 


# Sections
[Pico Vs Pro Micro](#why-the-raspberry-pi-pico-rp-2040-instead-of-the-usual-pro-micro)

[Wiring Diagram](#wiring-diagram)

[Parts List](#parts-list)

[Build Guide](#build-guide)

[Build Videos](#build-video)

[QMK Tips](#qmk-tips)

[Wrist Wrest and Cover](#wrist-rest-and-bottom-cover)

[Photos](#photos)

# Why the raspberry pi pico (RP 2040) instead of the usual pro micro?

I used the pro micro for my 30 key keyboard and macro pad before. This was before QMK supported the RP 2040. And on both ocassions I had to trim down the firmware/make compromises as I ran out of ram or flash storage.

This won't be a problem with the RP 2040, due to the massive spec gap. Also weirdly enough the RP 2040 can be found for cheaper.

RP 2040 vs pro micro specs
| Controller | CPU Speed | RAM    | FLASH |
| -----------|-----------|--------|-------|
| RP 2040    | 133 MHz   | 264 KB | 2 MB  |
| Pro Micro  | 16 Mhz    | 2.5 KB | 32 KB |

So as you can see the pico is over 100x more powerful in some aspects so running out of ram or flash storage is a thing of the past. As well as having two cpu cores, but I'm not sure if qmk utilises them, I don't think so.

The pico also has two hardware state machines that can be used for the LEDs and serial communication between the two halves, leaving more reasources available for your custom functions.

So overall the pico will be the go to controller for qmk from now on.

# Wiring Diagram
I didn't find any decent wiring diagram for the 5x7 form factor and it took me some time to figure it out. So here is a diagram I created.  

![wiring_diagram](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/wiring.png)

Make sure to take note of the differences on the wiring of the ttrs jack and columns between the two sides.

The numbers and letters in the diagram correspond to the pin labels you see on the physical micro controller. These won't be the same pins used in qmk but it helps with the wiring. 

For the actual pins to use in qmk, they need to be the GPIO equivelent. See the [pinout here](https://learn.adafruit.com/adafruit-kb2040/pinouts)

# Parts List
| Quantity | Item | Price | Shop | Optional |
|----------|------|-------|------|----------|
|2| adafruit KB 2040 (same chip as the official raspberry pi pico but slightly smaller and has USB C) micro controllers | €25 | Pimoroni (€10 shipping) if in EU, Adafruit if in US | No |
|2| JST-SH Cable (Qwicc, STEMMA QT, QW/ST) | €3 | Pimoroni (€10 shipping) if in EU, Adafruit if in US | Yes (you can use any spare pin on the controller for hooking up the led strip) |
|74| 1N4148 diodes | €8 for 500 | Amazon UK | No |
|2| TTRS Jack breakout board | €6 for 10 | Amazon UK | No |
|74| switches (I reused my ZealPc Clickiez from my ergodox)| - | - | No |
|74| keycaps (I reused keycaps from my ergodox again)| - | - | No |
|2| dactyl cases. I 3d printed mine. You will need almost a full 1KG fillament spool for these | €35 | Amazon for fillament | No |
|2| wrist wrests. I 3d printed these too (800 grams of TPU) | €25 | Amazon for fillament | Yes but recommended |
|10| Self Adhessive Rubber feet for wrist rests 6mm | €2 for 50 | Amazon | Yes but recommended |
|1| 10 Pin rainbow ribbon cable | €7 | Amazon | Yes |
|1| WS2812B 144/m led strip (1m) | €12 | Amazon | Yes |
|1| WS2812B 60/m led strip (3m) | €12 | Ebay | Yes |
|100| Wires, (try get the breadboard jumper Arduino kind so we can easily connect it to the controller) | €11 | Amazon | No |
|1| Soldering Iron, Solder Wire | - | - | No |
|1| Hotglue Gun and sticks | - | - | Yes but recommended |

So the build is actually quite affordable, provided that you are reusing the switches and keycaps from a different keyboard. If you don't have a 3d printer, there are 3d printing services that do it for you. It shouldn't cost more than €50 to get the two halves printed and shipped. 

# Build Guide

One important thing to note, if you are going to be using alot of leds like me, you won't have enough power by default. You will need to bypass the fuse as shown in [Step 14](#step-14).

This will also mean that we cant use the STEMMA QT cable from the parts list as we need to power the leds from the RAW pin directly.

You can tell if you are running out of current if the keyboard is constantly rebooting, you will hear the windows usb sound effect non stop etc. Don't worry this doesn't damage anything just annoying.

I used 109 led in each half of the keyboard which is a bit obsurd but by god it looks insane. So if you know you are going to use this many you can save some cash and don't order the QT connector.

#### Step 1
Wire up the diodes. Take note of the direction, make sure it is the same as the diagram.
![step_1](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/step_1.jpg)

#### Step 2
Wire up the columns as per the diagram.
![step_2](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/step_2.jpg)

#### Step 3
Wire up the rows as per the diagram.
![step_3](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/step_3.jpg)

#### Step 4
Extend the connectors so that we can easily plug into the controller.
![step_4](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/step_4.jpg)

#### Step 5
This step assumes you have soldered on the connectors to both the micro controller and the ttrs breakout board.

Now just wire them up as in the diagram.
![step_5](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/step_5.jpg)

#### Step 6
Prepare the first led strip. This will be powered by the Stemma QT port at the bottom of the kb 2040 micro controller. 

Also add connectors for the second led strip.
![step_6](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/step_6.jpg)

#### Step 7
Secure the connections with hotglue
![step_7](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/step_7.jpg)

#### Step 8
Hook up the columns and rows to the controller as per the diagram.
![step_8](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/step_8.jpg)

#### Step 9
The led strip can be left hanging loose for now.

Now you can try flashing the qmk firmware onto the board. And check if all of the buttons and led strip work.

You can compile the test firmware. See the QMK tips section down bellow for testing tips.

![step_9](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/step_9.jpg)
Loosely hook up the led strip for testing

#### Step 10
![step_10](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/step_10.jpg)
Hot glue the first led strip and row wires

#### Step 11
![step_11](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/step_11.jpg)
Using 30 LEDs from the 60/m LED strip. Wire them up around the bottom of the case. 

#### Step 12
![step_12](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/step_12.jpg)
Using 43 LEDs from the 60/m LED strip. Wire up a grid like so.

#### Step 13
![step_13](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/step_13.jpg)
Attach the led grid

#### Step 14
![step_14](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/step_14.jpg)
Solder the bypass as we need more current.

This is that tiny pad right under the usb c connector that says `USB -> RAW`. This will bypass the fuse and let us use all the current available from the USB port.

#### Step 15
![step_15](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/step_15.jpg)
Create these jumpers to split the raw pin

#### Step 16
![step_16](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/step_16.jpg)
Raw pin for leds and ttrs jack is now shared.

So the 5v for the leds and the 5v for the ttrs jack are both taken from the raw pin.

# QMK tips
## Setup
Make sure you clone my fork and switch to my dactyl branch.
```sh
git clone https://github.com/ArtiomSu/qmk_firmware.git

git checkout artiom_dactyl
```

You will also need to have the [qmk cli tool](https://github.com/qmk/qmk_cli) installed. It is required for building the firmware now.

You will need to flash each side independantly
`cd /temp/GIT/qmk_firmware && make clean && qmk flash -kb artiomsu_dactyl -km test`

If you `#define EE_HANDS` in the `config.h` you can save the side in the eeprom storage like so

```
cd /temp/GIT/qmk_firmware && make clean && qmk flash -kb artiomsu_dactyl -km test -bl uf2-split-right

cd /temp/GIT/qmk_firmware && make clean && qmk flash -kb artiomsu_dactyl -km test -bl uf2-split-left
```
Otherwise whichever side is plugged into the pc will think its left of right depending on if you set `#define MASTER_RIGHT` or `#define MASTER_LEFT` 

When updating qmk, builds might fail so you need to 
```sh
git submodule update --init --recursive
make git-submodule
```

## Testing
To build the test firmware you can do.
```sh
make clean && make artiomsu_dactyl:test
```

Then put the controller into bootloader mode and copy the `.uf2` firmware file onto the controller

Inside `config.h` make sure to `#define MASTER_LEFT` or `#define MASTER_RIGHT` depending on which side you built.

Yes you can test the sides independantly before testing them both at the same time.



## Sections you should take a look at after you are done

Make sure to checkout the [rp2040 sections](https://github.com/qmk/qmk_firmware/blob/master/docs/platformdev_rp2040.md) as they are a bit different to the pro micros.

Make sure to checkout the [split keyboard](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_split_keyboard.md) specific information.

If you are using led lighting checkout [this section](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_rgblight.md#lighting-layers)

# Build videos
[Dactyl Manuform RP 2040 Build Part 1 | Soldering Micro Contollers And Jacks](https://www.youtube.com/watch?v=SH30g5IgDSc)

[Dactyl Manuform RP 2040 Build Part 2 | LED strips](https://www.youtube.com/watch?v=pt-6UTvO6-A)

[Dactyl Manuform RP 2040 Build Part 3 | Diodes](https://www.youtube.com/watch?v=Vyib0i9I5N0)

[Dactyl Manuform RP 2040 Build Part 4 | Switches and Diodes](https://www.youtube.com/watch?v=efsJ9erwwJ0)

[Dactyl Manuform RP 2040 Build Part 5 | Rows](https://www.youtube.com/watch?v=QlJTeLKdx9E)

[Dactyl Manuform RP 2040 Build Part 6 | Columns](https://www.youtube.com/watch?v=Ufe2N9i5dcQ)

[Dactyl Manuform RP 2040 Build Part 7 | QMK Flashing and Testing](https://www.youtube.com/watch?v=5NNjv0asuOE)

[Dactyl Manuform RP 2040 Build Part 8 | Final assembly LED strips](https://www.youtube.com/watch?v=q52N-qa9q9w)

# 3D Printing / Design
These should be printable on any printer with a print area of 200x200 mm.

I simply bought the cheapest printer I could find that has a heated bed and auto bed leveling. This turned out to be Creality CR-6 SE for €300. This has a bed size of 235x235 mm. 

### Case
For the case I used this awesome tool called [Dactyl Generator](https://ryanis.cool/dactyl/#manuform). You will have to do a couple of prints to determine what you like.

The version you see in this guide is version 3. It is tweaked to exactly how I like it.

I'll share the exact config I used and you can see some of the stuff I tweaked, you can use this directly but I hightly recommend that you customise it to your own liking/fingers.

[v1](https://ryanis.cool/dactyl/#manuform:Ch4IBxAFGgNzaXgiBGZ1bGwqA2JveDIGbm9ybWllOAASEAjGChCjBRjCAyAEKMYKMFoiF1UAACBBGAAgAF0AAOBAZQAAQEBAAUgA)

[v2](https://ryanis.cool/dactyl/#original:ChIIBhABGAEiA2JveCoDc2l4MAASEgjGChDCAxjGCiDGCiiEBzCPHBoCCAEiDggAEAEYASAHKAEwADgS)

[v3](https://ryanis.cool/dactyl/#manuform:Ch0IBhAFGgNzaXgiBGZ1bGwqA2JveDIFb3V0aWU4ABIQCMYKEKMFGMIDIAQoxgowWhoKCAESBHRycnMYACIXVQAAcEEYACAAXQAA4EBlAABAQEABSAAy+QGVAwAAIECdAwAAgD+AAwCIAwENAAAAABUAAAAAHTMzM0AlAADQwC0AAFDBNQAAwEA9AAAAAEUAAAAATQAAwEBVAABAwF0AAAAAZTMzYcJtMzMtwnUAALzBeOcCgAHNGIgByCSVATMzF8KdATMzXcKlAWZmysGoAZ8LsAGZF7gB/CXFAQAAUMLNAQAA0MHVAQAAQMHYAZwE4AHzF+gBkBz1AQAA6MH9AQAAJMKFAgAAUMGIApsEkALzF5gC4CGlAgAADMKtAgAAcMG1AgAAAMC4AoQHwAKVEMgChAfVAgAAQMHdAgAAgMHlAgAAQEDoAoQH8AKVEPgChAc=)

For the material I use PLA. I used the multicolor transclucent one, thats why its costs a bit more than the regular ones.

Make sure you use some transclucent fillament regardless as it will allow the light to pass through easier for a greater effect.

Each side of this case takes over 3 days to print so make sure you are able to do this.

I used 100% infill to make sure the case is indestructable and heavy.

Each side uses just under 500g with the supports so make sure you have 1KG of fillament.

### Chip holder
For the chip holder I used the pro micro usb c as a base from [here](https://github.com/rianadon/dactyl-configurator/blob/main/src/connectors.md). And modified it in blender to fit the shape of the pico micro contoller.

This was printed with the same PLA as the case at 100% infill. You should have more than enough left from the 1KG roll so don't worry about running out.

This takes about 2 hours to print.


### Wrist rest
Printed using the TPU material as it is flexible and soft. And it actually feels nicer to the touch than the wrist rest that came with my ergodox ez keyboard.

This was printed with 10% infill since we want it to be flexible and takes about 5 hours.

Make sure you crank up the temperature higher than the PLA when printing this.

I created this in blender form scratch by importing the case and roughly following the shape.

What you see here is version 5, so it does take a good number of itterations to get it to how you like it.

![wrist_rest_1](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/wrist_rest_1.jpg)

![wrist_rest_2](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/wrist_rest_2.jpg)
Attach the feet if it is slippery.

![wrist_rest_3](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/wrist_rest_3.jpg)
Here you can see how flexible it is. I'm not using a lot of force to press it down in this photo.

### Bottom Cover
The bottom cover is also printed using TPU because it essentially stretches over the sides of the keyboard kind of like a condom, so we dont need to use screws or anything. It also has sound dampening qualities so its a win win.

I printed two versions of the bottom cover. One with a cutout and one without.

You can reset the pico micro controller using qmk, without needing to press the buttons on the bottom so you can use the full cover no problem. I personally use the full cover.

This was printed with 10% infill too, since it only a few millimeters tall so it doesn't really make a difference.

The bottom cover was basically created by copying the bottom of the model in blender and performing some extrusions.

![bottom_cover_cutout_1](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/bottom_cover_cutout_1.jpg)

![bottom_cover_cutout_2](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/bottom_cover_cutout_2.jpg)

![bottom_cover_full_1](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/bottom_cover_full_1.jpg)

![bottom_cover_full_2](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/bottom_cover_full_2.jpg)


# Photos
![photo1](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/photos_1.jpg)
![photo2](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/photos_2.jpg)
![photo3](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/photos_3.jpg)
![photo4](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/photos_4.jpg)
![photo5](https://github.com/ArtiomSu/qmk_firmware/raw/artiom_dactyl/keyboards/artiomsu_dactyl/public/images/photos_5.jpg)
