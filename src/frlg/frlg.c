/*
 * Pokémon FireRed/LeafGreen automation
 */

#include <util/delay.h>

#include "automation-utils.h"
#include "user-io.h"

#define HOLD_A_MS 3000

/* Static functions */
static void temporary_control(void);
static void do_rng_manip(void);

int main(void)
{
	init_automation();
	init_led_button();

	/* Initial beep to confirm that the buzzer works */
	beep();

	/* Wait for the user to press the button (should be on the Switch main menu) */
	count_button_presses(100, 100);

	/* Set the virtual controller as controller 1 */
	switch_controller(REAL_TO_VIRT);

	for (;;) {
		/* Set the LEDs, and make sure automation is paused while in the
		   menu */
		set_leds(BOTH_LEDS);
		pause_automation();

		/* Feature selection menu */
		uint8_t count = count_button_presses(100, 900);

		for (uint8_t i = 0 ; i < count ; i += 1) {
			beep();
			_delay_ms(100);
		}

		switch (count) {
			case 1:
				temporary_control();
			break;

			case 2:
				do_rng_manip();
			break;

			default:
				/* Wrong selection */
				delay(100, 200, 1500);
			break;
		}
	}
}


/*
 * Temporary gives back control to the user by performing controller switch.
 */
void temporary_control(void)
{
	set_leds(NO_LEDS);
	set_leds(TX_LED);
	switch_ledr(0);
	switch_ledg(0);
	switch_ledy(0);

	/* Allow the user to connect their controller back as controller 1 */
	switch_controller(VIRT_TO_REAL);

	/* Wait for the user to press the button (should be on the Switch main menu) */
	count_button_presses(100, 100);

	/* Set the virtual controller as controller 1 */
	switch_controller(REAL_TO_VIRT);
}


/*
 * Go through the RNG manip process: press Home after launching, then do the 3 timers.
 */
static void do_rng_manip(void)
{
	set_leds(NO_LEDS);
	set_leds(RX_LED);
	switch_ledr(0);
	switch_ledg(0);
	switch_ledy(0);

	// This assumes the user is hovering over the game icon but not launched it yet

	// Launch game
	send_update(BT_A, DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);
	send_update(BT_NONE, DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);

	_delay_ms(200);

	// Press Home to stabilize emulator
	send_update(BT_H, DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);
	send_update(BT_NONE, DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);

	_delay_ms(6000);

	// Press A to launch the game again
	send_update(BT_A, DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);
	send_update(BT_NONE, DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);
	
	_delay_ms(32279); // first timer
	switch_ledr(1);
	SEND_BUTTON_SEQUENCE(
		{ BT_A,			DP_NEUTRAL,	SEQ_HOLD,	74 },	/* Hold till we see continue screen */
		{ BT_NONE,		DP_NEUTRAL,	SEQ_HOLD,	1  },	/* Wait for the main menu */
	);

	_delay_ms(24946-HOLD_A_MS); // second timer
	send_update(BT_A, DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);
	send_update(BT_NONE, DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);
	switch_ledg(1);

	// now we have to press several buttons so third timer,
	// which is 600 adv or 100046 ms, will be done in segments
	_delay_ms(2000);
	send_update(BT_B, DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);
	send_update(BT_NONE, DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);

	_delay_ms(2500);
	send_update(BT_A, DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);
	send_update(BT_NONE, DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);

	_delay_ms(2000);
	send_update(BT_A, DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);
	send_update(BT_NONE, DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);

	_delay_ms(2000);
	send_update(BT_A, DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);
	send_update(BT_NONE, DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);


	_delay_ms(1546); // remaining time for third timer
	send_update(BT_A, DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);
	send_update(BT_NONE, DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);

	switch_ledy(1);

	_delay_ms(200);
}
