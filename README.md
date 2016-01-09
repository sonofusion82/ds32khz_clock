Simple PICmicro-based digital clock with DS32KHZ TCXO
-----------------------------------------------------

When most normal people wants a table clock, they just buy one.
A simple clock from a "pasar malam" stall will cost about RM10.

But for some crazy people, they would rather spend RM50 and many hours over several weekends to build one!

As you may know, most digital clocks seems to drift up to 20 minutes per year.
Therefore, instead of using standard 32KHz "watch crystal", I've decided put a [DS32KHZ](https://www.maximintegrated.com/en/products/digital/clock-generation-distribution/silicon-crystal-oscillators/DS32KHZ.html) TCXO (temperature compensated crystal oscillator).

I've tried measuring the accuracy with an NTP synchronized Raspberry PI measuring a PPS signal from the PIC. 
It seems to be accurate to less than 1 second per week.
So, if the datasheet is correct, the it should be accurate with within 1 minute per year!

Here's the source code and the schematics open-sourced with MIT license.

It was created with MPLABX IDE and it can be compiled with both XC8 and SDCC compilers.
It has been tested with both PIC16F72 and PIC16F628A, other 28-pin PIC micros might work with some tweaking.

Some pictures:
![Final](img/IMG_20160109_142033.jpg?raw=true "Final working clock")

![Before Assembling](img/IMG_20160109_141655.jpg?raw=true "Open, before assembling")

and schematic:

![Schematics](schematics/DS32KHz_Clock_stripboard_schem.png?raw=true "Open, before assembling")
