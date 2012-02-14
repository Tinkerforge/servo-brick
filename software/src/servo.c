/* servo-brick
 * Copyright (C) 2011 Olaf Lüke <olaf@tinkerforge.com>
 *
 * servo.c: Servo specific functions implementation
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

#include "servo.h"

#include "config.h"
#include "mcp3008.h"

#include "bricklib/com/com.h"
#include "bricklib/com/com_common.h"
#include "bricklib/logging/logging.h"
#include "bricklib/bricklet/bricklet_init.h"
#include "bricklib/drivers/dacc/dacc.h"
#include "bricklib/drivers/adc/adc.h"
#include "bricklib/drivers/pwmc/pwmc.h"
#include "bricklib/drivers/tc/tc.h"
#include "bricklib/drivers/pio/pio.h"
#include "bricklib/drivers/usart/usart.h"
#include "bricklib/utility/util_definitions.h"
#include "bricklib/utility/led.h"
#include "bricklib/utility/init.h"

#include <stdio.h>

Pin servos_off[] = {SERVO_OFF_PINS};
Pin servos_on[] = {SERVO_ON_PINS};
uint32_t servo_state = 0;

// true if servo is pwm pin, otherwise it is tc
bool servo_is_pwm[SERVO_NUM] = {true, true, false, true, true, false, false};

RwReg *servo_tc_counter[SERVO_NUM]  = {NULL,
                                       NULL,
                                       &SERVO_COUNTER_1B,
                                       NULL,
                                       NULL,
                                       &SERVO_COUNTER_2A,
                                       &SERVO_COUNTER_0A
};

RwReg *servo_tc_counterp[SERVO_NUM]  = {NULL,
                                        NULL,
                                        &SERVO_COUNTER_1C,
                                        NULL,
                                        NULL,
                                        &SERVO_COUNTER_2C,
                                        &SERVO_COUNTER_0C
};

TcChannel *servo_tc_channel[SERVO_NUM] = {NULL,
                                          NULL,
                                          &SERVO_TC_CHANNEL_1,
                                          NULL,
                                          NULL,
                                          &SERVO_TC_CHANNEL_2,
                                          &SERVO_TC_CHANNEL_0
};


uint8_t servo_pwm_channel[SERVO_NUM] = {0, 3, 0xFF, 1, 2, 0xFF, 0xFF};


uint8_t servo_pwmtc_mult[SERVO_NUM] = {SERVO_TIMER_MULT_PWM_32,
									   SERVO_TIMER_MULT_PWM_32,
									   SERVO_TIMER_MULT_TC_32,
									   SERVO_TIMER_MULT_PWM_32,
									   SERVO_TIMER_MULT_PWM_32,
									   SERVO_TIMER_MULT_TC_32,
									   SERVO_TIMER_MULT_TC_32};



int16_t servo_position_orig[SERVO_NUM] = {SERVO_POSITION_ORIG,
                                          SERVO_POSITION_ORIG,
                                          SERVO_POSITION_ORIG,
                                          SERVO_POSITION_ORIG,
                                          SERVO_POSITION_ORIG,
                                          SERVO_POSITION_ORIG,
                                          SERVO_POSITION_ORIG
};

uint16_t servo_velocity_orig[SERVO_NUM] = {SERVO_VELOCITY_ORIG,
                                           SERVO_VELOCITY_ORIG,
                                           SERVO_VELOCITY_ORIG,
                                           SERVO_VELOCITY_ORIG,
                                           SERVO_VELOCITY_ORIG,
                                           SERVO_VELOCITY_ORIG,
                                           SERVO_VELOCITY_ORIG
};

uint16_t servo_acceleration_orig[SERVO_NUM] = {SERVO_ACCELERATION_ORIG,
                                               SERVO_ACCELERATION_ORIG,
                                               SERVO_ACCELERATION_ORIG,
                                               SERVO_ACCELERATION_ORIG,
                                               SERVO_ACCELERATION_ORIG,
                                               SERVO_ACCELERATION_ORIG,
                                               SERVO_ACCELERATION_ORIG
};

uint32_t servo_period_length[SERVO_NUM] = {SERVO_STARTUP_PERIOD_LENGTH,
                                           SERVO_STARTUP_PERIOD_LENGTH,
                                           SERVO_STARTUP_PERIOD_LENGTH,
                                           SERVO_STARTUP_PERIOD_LENGTH,
                                           SERVO_STARTUP_PERIOD_LENGTH,
                                           SERVO_STARTUP_PERIOD_LENGTH,
                                           SERVO_STARTUP_PERIOD_LENGTH
}; // in ns

uint32_t servo_period[SERVO_NUM] = {SERVO_STARTUP_PERIOD,
									SERVO_STARTUP_PERIOD,
									SERVO_STARTUP_PERIOD,
									SERVO_STARTUP_PERIOD,
									SERVO_STARTUP_PERIOD,
									SERVO_STARTUP_PERIOD,
									SERVO_STARTUP_PERIOD
}; // in period/s



uint32_t servo_position[SERVO_NUM] = {SERVO_STARTUP_POSITION,
                                      SERVO_STARTUP_POSITION,
                                      SERVO_STARTUP_POSITION,
                                      SERVO_STARTUP_POSITION,
                                      SERVO_STARTUP_POSITION,
                                      SERVO_STARTUP_POSITION,
                                      SERVO_STARTUP_POSITION
}; // in ns

uint32_t servo_position_goal[SERVO_NUM] = {SERVO_STARTUP_POSITION,
                                           SERVO_STARTUP_POSITION,
                                           SERVO_STARTUP_POSITION,
                                           SERVO_STARTUP_POSITION,
                                           SERVO_STARTUP_POSITION,
                                           SERVO_STARTUP_POSITION,
                                           SERVO_STARTUP_POSITION
}; // in ns

uint32_t servo_velocity[SERVO_NUM] = {0,
                                      0,
                                      0,
                                      0,
                                      0,
                                      0,
                                      0
}; // in ns/periode

uint32_t servo_velocity_goal[SERVO_NUM] = {SERVO_STARTUP_MAX_VELOCITY,
                                           SERVO_STARTUP_MAX_VELOCITY,
                                           SERVO_STARTUP_MAX_VELOCITY,
                                           SERVO_STARTUP_MAX_VELOCITY,
                                           SERVO_STARTUP_MAX_VELOCITY,
                                           SERVO_STARTUP_MAX_VELOCITY,
                                           SERVO_STARTUP_MAX_VELOCITY
}; // in ns/periode


uint32_t servo_velocity_max[SERVO_NUM] = {SERVO_STARTUP_MAX_VELOCITY,
                                          SERVO_STARTUP_MAX_VELOCITY,
                                          SERVO_STARTUP_MAX_VELOCITY,
                                          SERVO_STARTUP_MAX_VELOCITY,
                                          SERVO_STARTUP_MAX_VELOCITY,
                                          SERVO_STARTUP_MAX_VELOCITY,
                                          SERVO_STARTUP_MAX_VELOCITY
}; // in ns/periode

uint32_t servo_acceleration[SERVO_NUM] = {SERVO_STARTUP_MAX_ACCELERATION,
                                          SERVO_STARTUP_MAX_ACCELERATION,
                                          SERVO_STARTUP_MAX_ACCELERATION,
                                          SERVO_STARTUP_MAX_ACCELERATION,
                                          SERVO_STARTUP_MAX_ACCELERATION,
                                          SERVO_STARTUP_MAX_ACCELERATION,
                                          SERVO_STARTUP_MAX_ACCELERATION
}; // in ns/periode^2

uint32_t servo_acceleration_max[SERVO_NUM] = {SERVO_STARTUP_MAX_ACCELERATION,
                                              SERVO_STARTUP_MAX_ACCELERATION,
                                              SERVO_STARTUP_MAX_ACCELERATION,
                                              SERVO_STARTUP_MAX_ACCELERATION,
                                              SERVO_STARTUP_MAX_ACCELERATION,
                                              SERVO_STARTUP_MAX_ACCELERATION,
                                              SERVO_STARTUP_MAX_ACCELERATION
}; // in ns/periode^2

uint32_t servo_max_pulse_width[SERVO_NUM] = {SERVO_STARTUP_MAX_PULSE_WIDTH,
											 SERVO_STARTUP_MAX_PULSE_WIDTH,
											 SERVO_STARTUP_MAX_PULSE_WIDTH,
											 SERVO_STARTUP_MAX_PULSE_WIDTH,
											 SERVO_STARTUP_MAX_PULSE_WIDTH,
											 SERVO_STARTUP_MAX_PULSE_WIDTH,
											 SERVO_STARTUP_MAX_PULSE_WIDTH
}; // in ns


uint32_t servo_min_pulse_width[SERVO_NUM] = {SERVO_STARTUP_MIN_PULSE_WIDTH,
										 	 SERVO_STARTUP_MIN_PULSE_WIDTH,
											 SERVO_STARTUP_MIN_PULSE_WIDTH,
											 SERVO_STARTUP_MIN_PULSE_WIDTH,
											 SERVO_STARTUP_MIN_PULSE_WIDTH,
											 SERVO_STARTUP_MIN_PULSE_WIDTH,
											 SERVO_STARTUP_MIN_PULSE_WIDTH
}; // in ns

int16_t servo_max_degree[SERVO_NUM] = {SERVO_STARTUP_MAX_DEGREE,
									   SERVO_STARTUP_MAX_DEGREE,
									   SERVO_STARTUP_MAX_DEGREE,
									   SERVO_STARTUP_MAX_DEGREE,
									   SERVO_STARTUP_MAX_DEGREE,
									   SERVO_STARTUP_MAX_DEGREE,
									   SERVO_STARTUP_MAX_DEGREE
}; // in degree/100

int16_t servo_min_degree[SERVO_NUM] = {SERVO_STARTUP_MIN_DEGREE,
									   SERVO_STARTUP_MIN_DEGREE,
									   SERVO_STARTUP_MIN_DEGREE,
									   SERVO_STARTUP_MIN_DEGREE,
									   SERVO_STARTUP_MIN_DEGREE,
									   SERVO_STARTUP_MIN_DEGREE,
									   SERVO_STARTUP_MIN_DEGREE
}; // in degree/100

bool servo_enabled[SERVO_NUM] = {false,
                                 false,
                                 false,
                                 false,
                                 false,
                                 false,
                                 false
};

bool servo_position_reached[SERVO_NUM] = {false,
                                          false,
                                          false,
                                          false,
                                          false,
                                          false,
                                          false
};

bool servo_velocity_reached[SERVO_NUM] = {false,
                                          false,
                                          false,
                                          false,
                                          false,
                                          false,
                                          false
};

extern uint32_t servo_current_counter;
extern uint32_t servo_current_sum[SERVO_NUM];
extern ComType com_current;
extern uint8_t com_stack_id;

uint16_t servo_current[SERVO_NUM] = {0};
uint16_t servo_output_voltage = 0;
uint16_t servo_minimum_voltage = SERVO_MIN_VOLTAGE;

uint32_t tick = 0;
uint32_t tick_message = 0;

Pin pin_voltage_switch = VOLTAGE_STACK_SWITCH_PIN;

int32_t servo_ns_to_pwm(uint8_t servo, int32_t position) {
	return (position/((1000/servo_pwmtc_mult[servo])*2));
}

void new_connection(void) {
}

void tick_task(uint8_t tick_type) {
	if(tick_type == TICK_TASK_TYPE_CALCULATION) {
		tick++;
		if(tick % 50 == 0) {
			update_servo_current();
		}

		uint32_t pwm_mask = PWM->PWM_ISR1;

		// Switch Output Voltage between extern and stack
		if(servo_get_external_voltage() < SERVO_VOLTAGE_EPSILON) {
			PIO_Set(&pin_voltage_switch);
		} else {
			PIO_Clear(&pin_voltage_switch);
		}


		for(uint8_t i = 0; i < SERVO_NUM; i++) {
			if(!servo_enabled[i] || servo_position_goal[i] == servo_position[i]) {
				continue;
			}

			// Check if this is a new period, we only update once per period
			if(servo_is_pwm[i]) {
				if(!(pwm_mask & (1 << servo_pwm_channel[i]))) {
					continue;
				}
			} else if(!(servo_tc_channel[i]->TC_SR & TC_SR_CPCS)) {
				continue;
			}

			// Update position
			if(servo_velocity[i] >= servo_velocity_max[i] &&
			   servo_acceleration[i] >= servo_acceleration_max[i]) {
				servo_position[i] = servo_position_goal[i];
			} else if(servo_position_goal[i] > servo_position[i]) {
				int32_t new_vel = servo_position[i] +
								  servo_acceleration[i]/2 +
								  servo_velocity[i];

				if(new_vel > servo_position_goal[i]) {
					servo_position[i] = servo_position_goal[i];
				} else {
					servo_position[i] = new_vel;
				}
			} else if(servo_position_goal[i] < servo_position[i]) {
				int32_t new_vel = servo_position[i] -
								  servo_acceleration[i]/2 -
								  servo_velocity[i];

				if(new_vel < servo_position_goal[i]) {
					servo_position[i] = servo_position_goal[i];
				} else {
					servo_position[i] = new_vel;
				}
			}

			// Update velocity
			if(servo_velocity[i] != servo_velocity_goal[i]) {
				if(servo_acceleration[i] >= servo_acceleration_max[i]) {
					servo_velocity[i] = servo_velocity_goal[i];
				} else if(servo_velocity_goal[i] > servo_velocity[i]) {
					int32_t new_vel = servo_velocity[i] + servo_acceleration[i];
					if(new_vel > servo_velocity_goal[i]) {
						servo_velocity[i] = servo_velocity_goal[i];
					} else {
						servo_velocity[i] = new_vel;
					}
				} else if(servo_velocity_goal[i] < servo_velocity[i]) {
					int32_t new_vel = servo_velocity[i] - servo_acceleration[i];
					if(new_vel < servo_velocity_goal[i]) {
						servo_velocity[i] = servo_velocity_goal[i];
					} else {
						servo_velocity[i] = new_vel;
					}
				}

				if(servo_velocity[i] == servo_velocity_goal[i]) {
					servo_velocity_reached[i] = true;
				}
			}

			servo_update_position(i);

			if(servo_position[i] == servo_position_goal[i]) {
				servo_velocity[i] = 0;
				servo_position_reached[i] = true;
			}
		}
	} else if(tick_type == TICK_TASK_TYPE_MESSAGE) {
		tick_message++;

		for(uint8_t i = 0; i < SERVO_NUM; i++) {
			if(servo_position_reached[i]) {
				servo_position_reached[i] = false;
				servo_position_reached_signal(i);
			}

			if(servo_velocity_reached[i]) {
				servo_velocity_reached[i] = false;
				servo_velocity_reached_signal(i);
			}
		}

		servo_check_error_signals();
	}
}

void servo_check_error_signals(void) {
	if(tick_message % 1000 != 0) {
		return;
	}

	const uint16_t external_voltage = servo_get_external_voltage();
	const uint16_t stack_voltage    = servo_get_stack_voltage();

	// Under Voltage if external voltage is below minimum voltage (regardless
	// of stack voltage), or if external voltage is zero and stack velotage is
	// below minimum voltage
	if((external_voltage > SERVO_VOLTAGE_EPSILON &&
	    external_voltage < servo_minimum_voltage) ||
	   (external_voltage < SERVO_VOLTAGE_EPSILON &&
	    stack_voltage > SERVO_VOLTAGE_EPSILON &&
	    stack_voltage < servo_minimum_voltage)) {
		UnderVoltageSignal uvs = {
			com_stack_id,
			TYPE_UNDER_VOLTAGE,
			sizeof(UnderVoltageSignal),
			external_voltage < SERVO_VOLTAGE_EPSILON ? stack_voltage : external_voltage
		};

		send_blocking_with_timeout(&uvs,
		                           sizeof(UnderVoltageSignal),
		                           com_current);
		led_on(LED_STD_RED);
	} else {
		led_off(LED_STD_RED);
	}
}

void servo_position_reached_signal(uint8_t servo) {
	PositionReachedSignal prs = {
		com_stack_id,
		TYPE_POSITION_REACHED,
		sizeof(PositionReachedSignal),
		servo,
		servo_position_orig[servo]
	};

	send_blocking_with_timeout(&prs,
	                           sizeof(PositionReachedSignal),
	                           com_current);
}

void servo_velocity_reached_signal(uint8_t servo) {
	VelocityReachedSignal vrs = {
		com_stack_id,
		TYPE_VELOCITY_REACHED,
		sizeof(VelocityReachedSignal),
		servo,
		servo_velocity_orig[servo]
	};

	send_blocking_with_timeout(&vrs,
	                           sizeof(VelocityReachedSignal),
	                           com_current);
}

void servo_update_data(uint8_t servo,
                       int32_t period_length_old, int32_t period_length_new,
                       int32_t period_old, int32_t period_new,
                       int32_t min_pulse_width_old, int32_t min_pulse_width_new,
                       int32_t max_pulse_width_old, int32_t max_pulse_width_new,
                       int16_t min_degree_old, int16_t min_degree_new,
                       int16_t max_degree_old, int16_t max_degree_new) {
	int32_t value_pos;
	uint32_t value;

	// Get position
	value_pos = SCALE((int64_t)servo_position[servo],
	                  (int64_t)servo_min_pulse_width[servo],
	                  (int64_t)servo_max_pulse_width[servo],
	                  (int64_t)servo_min_degree[servo],
	                  (int64_t)servo_max_degree[servo]);

	// Update position
	value = SCALE((int64_t)value_pos,
	              (int64_t)min_degree_new,
	              (int64_t)max_degree_new,
	              (int64_t)min_pulse_width_new,
	              (int64_t)max_pulse_width_new);

	logservod("update position: %d -> %d\n\r", servo_position[servo], value);
	servo_position[servo] = value;

	// Update position goal
	value = SCALE((int64_t)servo_position_orig[servo],
	              (int64_t)min_degree_new,
	              (int64_t)max_degree_new,
	              (int64_t)min_pulse_width_new,
	              (int64_t)max_pulse_width_new);

	logservod("update position goal: %d -> %d\n\r", servo_position_goal[servo], value);
	servo_position_goal[servo] = value;

	// Get velocity
	value = SCALE((int64_t)servo_velocity[servo],
		          0,
		          (int64_t)(servo_max_pulse_width[servo] - servo_min_pulse_width[servo])/servo_period[servo],
		          0,
		          (int64_t)(servo_max_degree[servo] - servo_min_degree[servo]));

	// Update velocity
	value = SCALE((int64_t)value,
		          0,
		          (int64_t)(max_degree_new - min_degree_new),
		          0,
		          (int64_t)(max_pulse_width_new - min_pulse_width_new))/period_new;

	logservod("update velocity: %d -> %d\n\r", servo_velocity[servo], value);
	servo_velocity[servo] = value;

	// Update velocity goal
	value = SCALE((int64_t)servo_velocity_orig[servo],
		          0,
		          (int64_t)(max_degree_new - min_degree_new),
		          0,
		          (int64_t)(max_pulse_width_new - min_pulse_width_new))/period_new;

	logservod("update velocity goal: %d -> %d\n\r", servo_velocity_goal[servo], value);
	servo_velocity_goal[servo] = value;


	// Update acceleration
	value = SCALE((int64_t)servo_acceleration_orig[servo],
		          0,
		          (int64_t)(max_degree_new - min_degree_new),
		          0,
		          (int64_t)(max_pulse_width_new - min_pulse_width_new))/(period_new*period_new);

	logservod("update acceleration: %d -> %d\n\r", servo_acceleration[servo], value);
	servo_acceleration[servo] = value;


	// Update maxima
	logservod("old maxima: %d, %d\n\r", servo_acceleration_max[servo], servo_velocity_max[servo]);

	servo_acceleration_max[servo] = SCALE((int64_t)0xffff,
	                                      0,
	                                      (int64_t)(max_degree_new - min_degree_new),
	                                      0,
	                                      (int64_t)(max_pulse_width_new - min_pulse_width_new))/(period_new*period_new);

	servo_velocity_max[servo] = SCALE((int64_t)0xffff,
			                          0,
									  (int64_t)(max_degree_new - min_degree_new),
									  0,
									  (int64_t)(max_pulse_width_new - min_pulse_width_new))/period_new;

	logservod("new maxima: %d, %d\n\r", servo_acceleration_max[servo], servo_velocity_max[servo]);
}

void servo_update_position(uint8_t servo) {
	if(servo_is_pwm[servo]) {
		PWMC_SetDutyCycle(PWM,
		                  servo_pwm_channel[servo],
		                  servo_ns_to_pwm(servo, servo_position[servo]));
	} else {
		*servo_tc_counter[servo] = servo_ns_to_pwm(servo, servo_position[servo]);
	}

}

void update_servo_current(void) {
	for(uint8_t i = 0; i < SERVO_NUM; i++) {
		servo_current[i] = servo_current_sum[i] / servo_current_counter;
		servo_current_sum[i] = 0;
	}
	servo_current_counter = 0;
}

void servo_init(void) {
	Pin servo_power_management_pins[] = {VOLTAGE_STACK_PIN,
	                                     VOLTAGE_EXTERN_PIN,
	                                     SERVO_POWER_ENABLE_PIN,
	                                     VOLTAGE_STACK_SWITCH_PIN,
	                                     SERVO_OUTPUT_VOLTAGE_PIN};
	PIO_Configure(servo_power_management_pins, 5);
	PIO_Configure(servos_off, PIO_LISTSIZE(servos_off));

	// Initialize and enable DACC for to set output voltage
    DACC_Initialize(DACC,
                    ID_DACC,
                    0, // Hardware triggers are disabled
                    0, // External trigger
                    0, // Half-Word Transfer
                    0, // Normal Mode (not sleep mode)
                    BOARD_MCK,
                    1, // refresh period
                    1, // Channel 1 selection
                    0, // Tag Selection Mode disabled
                    16); //  value of the start up time

    DACC_EnableChannel(DACC, SERVO_OUTPUT_VOLTAGE_CHANNEL);

    // Set default output voltage
    servo_set_output_voltage(SERVO_DEFAULT_OUTPUT_VOLTAGE);

	// Configure PWM servo pins
    PMC->PMC_PCER0 = 1 << ID_PWM;

	PWMC_ConfigureChannel(PWM,
	                      0,
	                      PWM_CMR_CPRE_MCK_DIV_32,
	                      0,
	                      PWM_CMR_CPOL);
	PWMC_SetPeriod(PWM,
	               0,
	               servo_ns_to_pwm(6, SERVO_STARTUP_PERIOD_LENGTH));

	PWMC_ConfigureChannel(PWM,
	                      1,
	                      PWM_CMR_CPRE_MCK_DIV_32,
	                      0,
	                      PWM_CMR_CPOL);
	PWMC_SetPeriod(PWM,
	               1,
	               servo_ns_to_pwm(3, SERVO_STARTUP_PERIOD_LENGTH));

	PWMC_ConfigureChannel(PWM,
	                      2,
	                      PWM_CMR_CPRE_MCK_DIV_32,
	                      0,
	                      PWM_CMR_CPOL);
	PWMC_SetPeriod(PWM,
	               2,
	               servo_ns_to_pwm(2, SERVO_STARTUP_PERIOD_LENGTH));

	PWMC_ConfigureChannel(PWM,
	                      3,
	                      PWM_CMR_CPRE_MCK_DIV_32,
	                      0,
	                      PWM_CMR_CPOL);
	PWMC_SetPeriod(PWM,
	               3,
	               servo_ns_to_pwm(1, SERVO_STARTUP_PERIOD_LENGTH));

	// Enable interrupt on period end for every pwm channel
	PWM->PWM_IER1 = PWM_IER1_CHID0 |
	                PWM_IER1_CHID1 |
	                PWM_IER1_CHID2 |
	                PWM_IER1_CHID3;

	// Configure timer counter servo pins
    PMC->PMC_PCER0 = 1 << ID_TC0;
    tc_channel_init(&SERVO_TC_CHANNEL_0,
	                TC_CMR_WAVE |
	                TC_CMR_TCCLKS_TIMER_CLOCK3 |
	                //TC_CMR_EEVT_XC0 |
	                TC_CMR_ACPA_CLEAR |
	                TC_CMR_ACPC_SET |
	                TC_CMR_WAVSEL_UP_RC);

	SERVO_COUNTER_0A = servo_ns_to_pwm(2, SERVO_STARTUP_POSITION);
	SERVO_COUNTER_0C = servo_ns_to_pwm(2, SERVO_STARTUP_PERIOD_LENGTH);
	SERVO_TC_CHANNEL_0.TC_IER = TC_IER_CPCS;

    PMC->PMC_PCER0 = 1 << ID_TC1;
	tc_channel_init(&SERVO_TC_CHANNEL_1,
	                TC_CMR_WAVE |
	                TC_CMR_TCCLKS_TIMER_CLOCK3 |
	                TC_CMR_EEVT_XC0 |
	                TC_CMR_BCPB_CLEAR |
	                TC_CMR_BCPC_SET |
	                TC_CMR_WAVSEL_UP_RC);

	SERVO_COUNTER_1B = servo_ns_to_pwm(2, SERVO_STARTUP_POSITION);
	SERVO_COUNTER_1C = servo_ns_to_pwm(2, SERVO_STARTUP_PERIOD_LENGTH);
	SERVO_TC_CHANNEL_1.TC_IER = TC_IER_CPCS;

    PMC->PMC_PCER0 = 1 << ID_TC2;
	tc_channel_init(&SERVO_TC_CHANNEL_2,
	                TC_CMR_WAVE |
	                TC_CMR_TCCLKS_TIMER_CLOCK3 |
	                //TC_CMR_EEVT_XC0 |
	                TC_CMR_ACPA_CLEAR |
	                TC_CMR_ACPC_SET |
	                TC_CMR_WAVSEL_UP_RC);

	SERVO_COUNTER_2A = servo_ns_to_pwm(2, SERVO_STARTUP_POSITION);
	SERVO_COUNTER_2C = servo_ns_to_pwm(2, SERVO_STARTUP_PERIOD_LENGTH);
	SERVO_TC_CHANNEL_2.TC_IER = TC_IER_CPCS;

    // Enable ADC channels for voltage measurements
	adc_channel_enable(VOLTAGE_EXTERN_CHANNEL);
	adc_channel_enable(VOLTAGE_STACK_CHANNEL);

	// Initializie extern AD converter (for servo current measurement)
	mcp3008_init();
}

void servo_set_period(uint8_t servo, uint16_t period) {
	uint32_t div;

	if(servo_is_pwm[servo]) {
		if(period > 0xFFFF/2) {
			div = PWM_CMR_CPRE_MCK_DIV_64;
			servo_pwmtc_mult[servo] = SERVO_TIMER_MULT_PWM_64;
		} else {
			div = PWM_CMR_CPRE_MCK_DIV_32;
			servo_pwmtc_mult[servo] = SERVO_TIMER_MULT_PWM_32;
		}

		PWMC_ConfigureChannel(PWM,
							  servo_pwm_channel[servo],
					          div,
					          0,
					          PWM_CMR_CPOL);

		PWMC_SetPeriod(PWM,
		               servo_pwm_channel[servo],
		               servo_ns_to_pwm(servo, servo_period_length[servo]));

		if(servo_enabled[servo]) {
			PWMC_EnableChannel(PWM, servo_pwm_channel[servo]);
		}
	} else {
		tc_channel_stop(servo_tc_channel[servo]);

		TC0->TC_WPMR &=  ~(1 << 0);	// clear write protection

		if(period > 0xFFFF/2) {
			servo_pwmtc_mult[servo] = SERVO_TIMER_MULT_TC_128;
			servo_tc_channel[servo]->TC_CMR =
					(servo_tc_channel[servo]->TC_CMR & ~7)
					| TC_CMR_TCCLKS_TIMER_CLOCK4; // 128

		} else {
			servo_pwmtc_mult[servo] = SERVO_TIMER_MULT_TC_32;
			servo_tc_channel[servo]->TC_CMR =
					(servo_tc_channel[servo]->TC_CMR & ~7)
					| TC_CMR_TCCLKS_TIMER_CLOCK3; // 32

		}

		*servo_tc_counterp[servo] = servo_ns_to_pwm(servo,
		                                            servo_period_length[servo]);
		servo_tc_channel[servo]->TC_IER = TC_IER_CPCS;

		tc_channel_start(servo_tc_channel[servo]);
	}
}

uint16_t servo_get_period(uint8_t servo) {
	return servo_period_length[servo]/1000;
}

void servo_set_output_voltage(uint16_t voltage) {
	Pin pin_power = SERVO_POWER_ENABLE_PIN;

	if(voltage < SERVO_MIN_MV) {
		voltage = SERVO_MIN_MV;
	} else if(voltage > SERVO_MAX_MV) {
		voltage = SERVO_MAX_MV;
	}

	PIO_Clear(&pin_power);
	for(uint8_t i = 0; i < 10; i++) {
		__NOP();
	}

	DACC_SetConversionData(DACC,
	                       SERVO_VALUE_2V -
	                       (SERVO_VALUE_2V - SERVO_VALUE_9V)*
	                       (voltage - SERVO_MIN_MV)/
	                       (SERVO_MAX_MV - SERVO_MIN_MV));

	servo_output_voltage = voltage;
	for(uint8_t i = 0; i < 10; i++) {
		__NOP();
	}
	PIO_Set(&pin_power);
}

uint16_t servo_get_output_voltage() {
	return servo_output_voltage;
}

void servo_enable(uint8_t servo) {
	PIO_Configure(&servos_on[servo], 1);
	servo_enabled[servo] = true;
	if(servo_is_pwm[servo]) {
		PWMC_EnableChannel(PWM, servo_pwm_channel[servo]);
		while(!(PWM->PWM_SR & (1 << servo_pwm_channel[servo])));
	} else {
		tc_channel_start(servo_tc_channel[servo]);
	}

	// Update position once
	servo_update_position(servo);
}

void servo_disable(uint8_t servo) {
	if(servo_is_pwm[servo]) {
		PWMC_DisableChannel(PWM, servo_pwm_channel[servo]);
	} else {
		tc_channel_stop(servo_tc_channel[servo]);
	}
	servo_enabled[servo] = false;
	PIO_Configure(&servos_off[servo], 1);
}

uint16_t servo_get_external_voltage(void) {
    return adc_channel_get_data(VOLTAGE_EXTERN_CHANNEL) *
           VOLTAGE_EXTERN_REFERENCE *
           VOLTAGE_EXTERN_MULTIPLIER /
           VOLTAGE_MAX_VALUE;
}

uint16_t servo_get_stack_voltage(void) {
    return adc_channel_get_data(VOLTAGE_STACK_CHANNEL) *
           VOLTAGE_STACK_REFERENCE *
           VOLTAGE_STACK_MULTIPLIER /
           VOLTAGE_MAX_VALUE;
}
