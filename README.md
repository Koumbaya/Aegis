# Aegis
  
 The Aegis is a keyboard that uses the same layout as the crkbd by foostan : https://github.com/foostan/crkbd
 
 ![pic](https://github.com/Koumbaya/Aegis/blob/master/pictures/aegiscollage.jpg?raw=true)
 
 I wanted certain features like the solenoid so I made a quick PCB that's similar in layout to a crkbd but with only one pro-micro, you can make this PCB if you want a single PCB with underglow and a solenoid, or you can take the crkbd version of the case and slap both halves into this bad boy !
With the brass plate, it weight around 1Kg.
 
### CASE

If you're going for a metal 1,5mm switchplate (which you should, better sound yay !), you'll need to cut :
- One of every : Aegis_top1, Aegis_top2, Aegis_top3, Aegis_bottom in 3mm acrylic.
- Three times the Aegis_middle in 3mm acrylic
- One Aegis_switch_plate in 1,5mm metal of your choosing.

If you want to make everything in acrylic : just do as above minus one Aegis_middle.

You'll need 13 x M3 hex standoffs, >9mm if you have 3 "middle" part, >6 if you have only 2.
I've noticed that nylon standoffs are way larger than brass standoffs, so the dxf are designed for nylon standoff (brass ones will turn free) but can be modified.
You'll also need 13 x M3x5mm and 13 x M3x8mm screws.
The screws heads are hidden underneath the topmost plate, so you'll need something to hold it in place, probably some slim double-sided tape (will update once I've tested).
Note : be careful with the top1 and top2 cutouts, I broke mine when peeling the protective plastic sheet. (shoudn't have this problem on the crkbd version I think

 ### PCB
 
 The footprints for the diodes are either THT or SMD.
 
 The PCB uses SK6812mini-E for easier soldering, but the footprints are inverted compared to most keyboards :
 here the underglow LEDs are soldered from under the PCB (facing you when you solder them), instead of being soldered from the top. 
 
![top](https://github.com/Koumbaya/Aegis/blob/master/pictures/top.jpg?raw=true)

(soldered from under the PCB, led facing you. beware of the different orientations : the cut tab goes with the dot on the PCB)
 
 I did this because on my previous board some of the LEDs failed after that I had soldered all of the switches, meaning that to change them I had to desolder the switches.
 
 The center LED is soldered like a switch backlight led (from under the PCB, shining towards the top, through the PCB) because it's here to shine on the plate which have a logo cutout (a version without the logo is also available, in which case you'll probably want to just jump the trace for the led from IN to OUT).
 
![inverted](https://github.com/Koumbaya/Aegis/blob/master/pictures/inverted.jpg?raw=true)

(the cut tab goes on the top/right orientation, led facing back at you)
 
 
 For the solenoid you'll need 1 TIP120, 1 1N4001 diode, 1 1.1KOhms resistor and 1 5V solenoid.
Should look like this ![solenoid](https://github.com/Koumbaya/Aegis/blob/master/pictures/solenoid.jpg?raw=true)
Note : in the v1.1, I've added a hole for the TIP120 because it's too big (by 0.3mm) to fit in the case. In mine I had to sand it down.

Note 2 : I couldn't get the solenoid to work :( with a pro micro I got a reboot, with the elite-c I discovered that the RAW port doesn't exist on it, so I took the VCC, with the same result. I've checked the schematics with some people and it should be good, so I'm putting in on the PCB anyway if someone want to have a crack at it(I've added 2 jumpers to get either VCC or RAW to the solenoid, if you have a pro micro, solder RAW, elite-c : solder VCC. Never both). If you find a solution let me know.
 


