/**
 * ServoLibTiny - The ServoLibTiny Project library.
 * @author Neven Boyanov
 * This is part of the Tinusaur/ServoLibTiny project.
 * ----------------------------------------------------------------------------
 *  Copyright (c) 2021 Tinusaur (https://tinusaur.com). All rights reserved.
 *  Distributed as open source under the MIT License (see the LICENSE.txt file)
 *  Please, retain in your work a link to the Tinusaur project website.
 * ----------------------------------------------------------------------------
 * Source code available at: https://gitlab.com/tinusaur/servolibtiny
 */

// ============================================================================

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#include "servolibtiny/servolibtiny.h"

// ----------------------------------------------------------------------------

// SG90 Datasheet timing: pulse 1000uS (val=250) ... 2000uS (val=500), middle 1500uS (val=375)
// Testing for servo model SG90, pulse: min=130(560uS) max=750(3000uS) mid=415 safe=150...680
// Testing for servo model MG90S, pulse: min=150(600uS) max=700(2800uS) mid=425 safe=160...710
// Testing for servo model MG996R, pulse: min=150(600uS) max=650() mid= safe=150...640

// TODO: Add global variable for the pulse_count value and initialize it in the _init() function.

static uint8_t servolibtiny_servo_port;
static uint8_t servolibtiny_pulse_count;

// ----------------------------------------------------------------------------

// Select the active servo port, inti the port, set pulse count.
void servolibtiny_sel(uint8_t servo_port, uint8_t pulse_count) {
	servolibtiny_servo_port = servo_port;
	DDRB |= (1 << servo_port); // Set the port as output.
	PORTB &= ~(1 << servo_port); // Set port to LOW
	servolibtiny_pulse_count = pulse_count;
}

#define SERVOLIBTINY_SIGNAL_PERIOD 4980 // Should be 4980(5010) for 20 mS pulse period.
#define SERVOLIBTINY_PULSE_MIN 248      // This is the delay value for 1000uS pulse width.
#define SERVOLIBTINY_PULSE_MID 375      // This is the delay value for 1000uS pulse width.
#define SERVOLIBTINY_PULSE_MAX 500      // This is the delay value for 2000uS pulse width.

// servo_pos - value should be between 0 and 250 to comply with the servo datasheet.
// Note: servo_pos values less than 0 and more that 250 are possible to achieve wider range.
// - at servo_pos=0 the pulse should be 1+19=20 mS
// - at servo_pos=125 the pulse should be 1.5+18.5=20 mS
// - at servo_pos=250 the pulse should be 2+18=20 mS
void servolibtiny_set(uint8_t servo_port, int16_t servo_pos) {
	int16_t pulse_length = SERVOLIBTINY_PULSE_MIN + servo_pos;
	for (uint8_t pulse_count = servolibtiny_pulse_count; pulse_count > 0; pulse_count--) {
		// Loop to repeat (pulse_count times) the pulse - to reach the position.
		PORTB |= (1 << servo_port);
		_delay_loop_2(pulse_length); // Signal - Pulse
		PORTB &= ~(1 << servo_port);
		_delay_loop_2(SERVOLIBTINY_SIGNAL_PERIOD - pulse_length); // Signal - Pulse
	}
}

// Set servo position specifying only the servo_pos, and
// using servo_port & pulse_count set by the servolibtiny_sel().
void servolibtiny_pos(int16_t servo_pos) {
	servolibtiny_set(servolibtiny_servo_port, servo_pos);
}

// ----------------------------------------------------------------------------
// The following functions allow using:
// - multiple servos
// - keeping servo position position
// FOOTPRINT: Code 106 Bytes, Data 11 Bytes. (based on experiments)

static uint8_t servolibtiny_servo_index;
static int16_t servolibtiny_servo_poss[4];

void servolibtiny_resel(uint8_t servo_index, uint8_t servo_port, uint8_t pulse_count) {
	servolibtiny_servo_index = servo_index;
	servolibtiny_sel(servo_port, pulse_count);
}

int16_t servolibtiny_getpos(void) {
	return servolibtiny_servo_poss[servolibtiny_servo_index];
}

// Reposition the servo using series of pulses until it reaches the position.
void servolibtiny_repos(int16_t servo_pos) {
	int16_t pos = servolibtiny_servo_poss[servolibtiny_servo_index];
	if (servo_pos == pos) return; // No change in the position
	for (; servo_pos != pos;) {
		if (servo_pos > pos) {
			pos++;
		} else {
			pos--;
		}
		servolibtiny_pos(pos);
	}
	// TODO: array index bound check.
	servolibtiny_servo_poss[servolibtiny_servo_index] = servo_pos;
}
// NOTE: An earlier implementation of this was capable of using
// a STEP different than 1, but it appeared that there was no much
// use of this capability.

// ============================================================================
