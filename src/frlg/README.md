Pokémon FireRed/LeafGreen automation
====================================

This module automates some tasks in FireRed and LeafGreen.

Requirements
------------

You will need an Arduino UNO R3, an external Arduino programmer, and a
pushbutton inserted in the Arduino board, between pins 13 and GND (on the top
row).

You can additionally install three LEDs (with a series resistor)
between pins 3, 4, 5 and GND.

See [the main README](../../README.md#required-hardware) for details.

Installation
------------

Use `make` to build the `usb-iface.hex` and `frlg.hex` files. Flash
`usb-iface.hex` to the USB interface microcontroller (ATmega16U2), and
`frlg.hex` to the main microcontroller (ATmega328P).

See the main README for the
[required software](../../README.md#required-software), the
[build procedure](../../README.md#building), and the
[programming procedure](../../README.md#programming).

Usage
-----

Plug the Arduino to the Switch; the L LED on the Arduino board should start
blinking rapidly, and the TX/RX LEDs should be off.

To start the automation process, start Pokémon Sword/Shield (if it is not
already), and put the game in the required state (which depends on the task to
be automated; see below for details).

Press Home to get to the Switch main menu (the selection should be on
the game icon) and close the game. Then press the pushbutton on the Arduino board. 
The emulated controller will get auto-registered as controller 2, and then will access the
controller settings to register as controller 1. It will then get back to the
game, ready to control it.

Once it’s done, the Arduino L LED will blink once per second, and both the
RX and TX LEDs will be lit up. You are in the “main menu”, which allows you
to select which automation feature to perform. Press the pushbutton on the
board once to activate feature 1; twice to activate feature 2; etc.

The different automation features are described below.

### Temporary control [Feature 1 — one button press]

**Pre-requisites:** None

Pokémon FireRed/LeafGreen only allows one controller to be enabled while the game
is running; this features allows you to regain control of the game with your
controller.

When the feature is activated, the virtual controller will get back to the
main menu and open the controller management menu, allowing you to press A on
your controller to reconnect it. Once that’s done, you can close the menu
and get back to the game. The Arduino L LED will blink rapidly.

Once you’re ready to give back control to the virtual controller, press Home
to get back to the main menu Switch main menu (the selection should be on
the game icon) and press the pushbutton again. You will be back to the
game, ready to activate another feature.

### Repeat press A [Feature 2 - Starter RNG manip]

**Pre-requisites:** Save right in front the starter you want to pick

When this feature is activated, WIP