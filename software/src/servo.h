/* servo-brick
 * Copyright (C) 2011 Olaf Lüke <olaf@tinkerforge.com>
 *
 * servo.h: Servo specific functions implementation
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef SERVO_H
#define SERVO_H

#include <stdint.h>

#define SERVO_TIMER_MULT_TC_32 4
#define SERVO_TIMER_MULT_TC_128 1
#define SERVO_TIMER_MULT_PWM_32 4
#define SERVO_TIMER_MULT_PWM_64 2

#define SERVO_VALUE_2V 1740
#define SERVO_VALUE_9V 455
#define SERVO_MAX_MV 9000
#define SERVO_MIN_MV 2000

#define SERVO_MIN_VOLTAGE 5000
#define SERVO_MAX_VOLTAGE 27000
#define SERVO_VOLTAGE_EPSILON 200

#define SERVO_MIN_PERIOD 2000 // min period is 2ms = 500Hz

#define STATE_HIGH 0
#define STATE_LOW 1

#define SERVO_NUM 7
#define SERVO_NUM_PWM 4
#define SERVO_NUM_TC 3

#define SERVO_TC_CHANNEL_0 (TC0->TC_CHANNEL[0])
#define SERVO_COUNTER_0C SERVO_TC_CHANNEL_0.TC_RC
#define SERVO_COUNTER_0B SERVO_TC_CHANNEL_0.TC_RB
#define SERVO_COUNTER_0A SERVO_TC_CHANNEL_0.TC_RA

#define SERVO_TC_CHANNEL_1 (TC0->TC_CHANNEL[1])
#define SERVO_COUNTER_1C SERVO_TC_CHANNEL_1.TC_RC
#define SERVO_COUNTER_1B SERVO_TC_CHANNEL_1.TC_RB
#define SERVO_COUNTER_1A SERVO_TC_CHANNEL_1.TC_RA

#define SERVO_TC_CHANNEL_2 (TC0->TC_CHANNEL[2])
#define SERVO_COUNTER_2C SERVO_TC_CHANNEL_2.TC_RC
#define SERVO_COUNTER_2B SERVO_TC_CHANNEL_2.TC_RB
#define SERVO_COUNTER_2A SERVO_TC_CHANNEL_2.TC_RA

#define SERVO_PWM(x) PWM->PWM_CH_NUM[x].PWM_CDTY

#define SERVO_POSITION_ORIG 0
#define SERVO_VELOCITY_ORIG 0xFFFF
#define SERVO_ACCELERATION_ORIG 0xFFFF

#define SERVO_STARTUP_PERIOD_LENGTH 19500000 // in ns
#define SERVO_STARTUP_PERIOD (1000000/(SERVO_STARTUP_PERIOD_LENGTH/1000))
#define SERVO_STARTUP_POSITION      1500000  // in ns
#define SERVO_STARTUP_MAX_PULSE_WIDTH	2000000
#define SERVO_STARTUP_MIN_PULSE_WIDTH	1000000
#define SERVO_STARTUP_MAX_DEGREE	9000
#define SERVO_STARTUP_MIN_DEGREE	-9000
#define SERVO_STARTUP_VELOCITY 0
#define SERVO_STARTUP_MAX_VELOCITY ((SCALE((uint64_t)0xffff, 0, SERVO_STARTUP_MAX_DEGREE - SERVO_STARTUP_MIN_DEGREE, 0, SERVO_STARTUP_MAX_PULSE_WIDTH - SERVO_STARTUP_MIN_PULSE_WIDTH))/SERVO_STARTUP_PERIOD)
#define SERVO_STARTUP_MAX_ACCELERATION ((SCALE((uint64_t)0xffff, 0, SERVO_STARTUP_MAX_DEGREE - SERVO_STARTUP_MIN_DEGREE, 0, SERVO_STARTUP_MAX_PULSE_WIDTH - SERVO_STARTUP_MIN_PULSE_WIDTH))/(SERVO_STARTUP_PERIOD*SERVO_STARTUP_PERIOD))

#define SERVO_BIT_MODE (1 << 7)

void new_connection(void);
void servo_init(void);
void tick_task(void);
void servo_step(void);
void servo_update_position(uint8_t servo);
uint16_t servo_get_period(uint8_t servo);
void servo_set_period(uint8_t servo, uint16_t period);
void servo_set_output_voltage(uint16_t voltage);
void update_servo_current(void);
uint16_t servo_get_output_voltage();
uint16_t servo_get_external_voltage(void);
uint16_t servo_get_stack_voltage(void);

void servo_check_error_signals(void);
void servo_position_reached_signal(uint8_t servo);
void servo_velocity_reached_signal(uint8_t servo);

void servo_enable(uint8_t servo);
void servo_disable(uint8_t servo);

void servo_update_data(uint8_t servo,
                       int32_t period_length_old, int32_t period_length_new,
                       int32_t period_old, int32_t period_new,
                       int32_t min_pulse_width_old, int32_t min_pulse_width_new,
                       int32_t max_pulse_width_old, int32_t max_pulse_width_new,
                       int16_t min_degree_old, int16_t min_degree_new,
                       int16_t max_degree_old, int16_t max_degree_new);


#endif
