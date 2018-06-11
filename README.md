# Colorsair

This project provides user-space driver, controller and easy to use API for Corsair RGB fans through Corsair Node.

WARNING: This project is prototype as it is now, but I am going to make it fully featured driver/controller.
It has no interface whatsoever or way to control it outside of programming API yet.

## Features
- effects (Breathing, Linear color change, Static)
- any number of fans connected to Node's socket #1
- handles different framerates

## Supported systems
It is developed specifically for Linux systems, but it should work just fine on
OS X, BSD and Windows (basically if libusb 1.0 supports it then it will work).

## Dependencies
C++14 compiler and just libusb 1.0.

## Protocol
I am reverse engineering noob, so I basically copied what I saw in communication and replaced
color codes. I would love to describe this protocol fully, but I know as much as there is in
code. If you want to help grab Wireshark and USBPcap!

Generally speaking device accepts packages of 64bytes (padded with zeroes) as interrupts.
First of all, it expects commands with information which socket you want to control (not sure 
about this, I didn't bother to work with 2 sockets yet).
```
{0x33, 0xFF},
{0x38, 0x01, 0x02},
{0x34, 0x01},
{0x33, 0xFF},
{0x38, 0x00, 0x02}
```
That's what I send first (each line is beginning of 64B package).
I think 0x38 followed by 0x01 or 0x00 tells it which port you want to control.

After telling it which port you want to control it expects color commands. These have following format:
```
0x32, 0x00, 0x00, LEDS_COUNT, COLOR_CHANNEL, CHANNEL_VAL...
```
Each fan has 4 LEDs so LEDS_COUNT is fans count times 4. 
Then we tell which color channel it is (0x00 = Red, 0x01 = Green, 0x02 = Blue).
Finally we send given channel values for LEDs across ALL devices. I am not good with words so in case you don't understand here's example for 2 fans, one red, the other blue:
```
0x32, 0x00, 0x00, 0x08, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
0x32, 0x00, 0x00, 0x08, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
0x32, 0x00, 0x00, 0x08, 0x02, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
```
Just loop everything described here and that's it.

## Licensing
GNU GPL v2

See LICENSE.GPL2
