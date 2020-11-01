# Aegis
  
 The Aegis is a keyboard that uses the same layout as the crkbd by foostan : https://github.com/foostan/crkbd
 
 I wanted certain features like the solenoid so I made a quick PCB that's similar in layout to a crkbd but with only one pro-micro, you can make this PCB if you want a single PCB with underglow and a solenoid, or you can take the crkbd version of the case and slap both halves into this bad boy !
 
 ### PCB
 The PCB uses SK6812mini-E for easier soldering, but the footprints are inverted compared to most keyboards :
 here the underglow LEDs are soldered from under the PCB (facing you when you solder them), instead of being soldered from the top. 
 TODO : add a picture.
 
 I did this because on my previous board some of the LEDs failed after that I had soldered all of the switches, meaning that to change them I had to desolder the switches.
 
 The center LED is soldered like a switch backlight led (from under the PCB, shining towards the top, through the PCB) because it's here to shine on the plate which have a logo cutout (a version without the logo is also available, in which case you'll probably want to just jump the trace for the led from IN to OUT).
 TODO : add a picture.
 
 For the solenoid you'll need 1 TIP120, 1 1N4001 diode, 1 1.1KOhms resistor and 1 5V solenoid.
 TODO: add a picture.
 
 The footprints for the diodes are either THT or SMD.

### CASE

If you're going for a metal 1,5mm switchplate (which you should, better sound yay !), you'll need to cut :
- One of every : Aegis_top1, Aegis_top2, Aegis_top3, Aegis_bottom in 3mm acrylic.
- Three times the Aegis_middle in 3mm acrylic
- One Aegis_switch_plate in 1,5mm metal of your choosing.

If you want to make everything in acrylic : just do as above minus one Aegis_middle.

You'll need 13 x M3 hex standoffs, >9mm if you have 3 "middle" part, >6 if you have only 2.
I've noticed that nylon standoffs are way larger than brass standoffs, so the dxf are designed for brass standoff but can be modified.
You'll also need 13 x M3x6mm and 13 x M3x12mm screws.
The screws heads are hidden underneath the topmost plate, so you'll need something to hold it in place, probably some slim double-sided tape (will update once I've tested).

TBC

