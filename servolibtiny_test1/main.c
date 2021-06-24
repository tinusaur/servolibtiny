/**
 * ServoLibTiny - Testing scripts
 * @author Neven Boyanov
 * This is part of the Tinusaur/ServoLibTiny project.
 * ----------------------------------------------------------------------------
 *  Copyright (c) 2021 Tinusaur (https://tinusaur.com). All rights reserved.
 *  Distributed as open source under the MIT License (see the LICENSE.txt file)
 *  Please, retain in your work a link to the Tinusaur project website.
 * ----------------------------------------------------------------------------
 * Source code available at: https://gitlab.com/tinusaur/servolibtiny
 */

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#include "servolibtiny/servolibtiny.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~ Shield-XXXXX ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//               Shield XXXXX
//               +----------+
//      (RST)--> + PB5  Vcc +---(+)--VCC--
// --[OWOWOD]--> + PB3  PB2 +-------------
// --------------+ PB4  PB1 +---SERVO-----
// --------(-)---+ GND  PB0 +-------------
//               +----------+
//                 Tinusaur
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    SG90 - Tower Pro, Micro Servo, 9g
//          +---+              +------+
//    PWM --+ o +----Orange----+      |
//    Vcc --+ o +----Red-------+      |
//    Gnd --+ o +----Brown-----+      |
//          +---+              +------+
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Define the I/O port to be used for the SERVO.
#define SERVO_PORT PB1
#define SERVO_PULSE_COUNT 50

// ----------------------------------------------------------------------------

int main(void) {

	// ---- Initialization ----
	servolibtiny_sel(SERVO_PORT);	// Select servo and init port.

	// ---- Main Loop ----
	for (;;) { // The infinite main loop
		servolibtiny_pos(0, SERVO_PULSE_COUNT);	// Set servo in "0" position
		_delay_ms(200);
		servolibtiny_pos(250, SERVO_PULSE_COUNT);	// Set servo in "90" position
		_delay_ms(200);
	}

	return 0; // Return the mandatory for the "main" function int value - "0" for success.
}

// ============================================================================
