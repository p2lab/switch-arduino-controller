Pokémon Brilliant Diamond/Shining Pearl automation
===============================

This module automates some tasks in Pokémon Brilliant Diamond and Shining Pearl.

Requirements
------------

You will need **two** Arduino UNO R3 and an external Arduino programmer. From now on, I will refer to first Arduino as U0 and the second one as U1.

U0 will be flashed with usb-iface.hex and bdsp.hex, while U1 will be controlled from a Python script (using Firmata). U0 will be connected to the Nintendo Switch, while U1 will be connected to the PC.

U0's pin 8 must be connected with U1's pin 8.

You can additionally install a buzzer between pins 2 and GND.

See [the main README](../../README.md#required-hardware) for details.

Installation
------------

Use `make` to build the `usb-iface.hex` and `bdsp.hex` files. Flash
`usb-iface.hex` to the USB interface microcontroller (ATmega16U2), and
`bdsp.hex` to the main microcontroller (ATmega328P) on U0.

See the main README for the
[required software](../../README.md#required-software), the
[build procedure](../../README.md#building), and the
[programming procedure](../../README.md#programming).

Usage
-----

Working on description...

### Soft-reset sequence [Feature 1]

**Pre-requisites:** None

Working on description...
