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

#ifndef SERVOLIBTINY_H
#define SERVOLIBTINY_H

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------

void servolibtiny_sel(uint8_t servo_port, uint8_t pulse_count);
void servolibtiny_pos(int16_t servo_pos);

void servolibtiny_resel(uint8_t servo_index, uint8_t servo_port, uint8_t pulse_count);
int16_t servolibtiny_getpos(void);
void servolibtiny_repos(int16_t servo_pos);

// ----------------------------------------------------------------------------

#endif

// ============================================================================
