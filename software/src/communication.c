/* servo-brick
 * Copyright (C) 2010-2011 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.c: Implementation of Servo-Brick specific messages
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

#include "communication.h"

#include "servo.h"
#include "mcp3008.h"

#include "bricklib/logging/logging.h"
#include "bricklib/com/com_common.h"
#include "bricklib/drivers/adc/adc.h"
#include "bricklib/utility/util_definitions.h"
#include <stdint.h>
#include <stdio.h>

extern bool servo_enabled[];
extern uint32_t servo_period_length[];
extern uint32_t servo_period[];
extern uint32_t servo_position[];
extern uint32_t servo_position_goal[];
extern uint32_t servo_velocity[];
extern uint32_t servo_velocity_goal[];
extern uint32_t servo_velocity_max[];
extern uint32_t servo_acceleration[];
extern uint32_t servo_acceleration_max[];
extern uint32_t servo_max_pulse_width[];
extern uint32_t servo_min_pulse_width[];
extern int16_t servo_max_degree[];
extern int16_t servo_min_degree[];
extern uint16_t servo_current[];
extern uint16_t servo_position_orig[];
extern uint16_t servo_velocity_orig[];
extern uint16_t servo_acceleration_orig[];
extern uint16_t servo_minimum_voltage;

void enable(uint8_t com, const Enable *data) {
	uint8_t servo_start;
	uint8_t servo_end;
	uint8_t servo_bitmask;
	if(data->servo & SERVO_BIT_MODE) {
		servo_start = 0;
		servo_end = SERVO_NUM;
		servo_bitmask = data->servo;
	} else {
		servo_start = data->servo;
		servo_end = data->servo +1;
		servo_bitmask = 1 << data->servo;
	}

	for(uint8_t servo = servo_start; servo < servo_end; servo++) {
		if(servo_bitmask & (1 << servo)) {
			servo_enable(servo);
		}
	}

	logservoi("enable %d\n\r", data->servo);
}

void disable(uint8_t com, const Disable *data) {
	uint8_t servo_start;
	uint8_t servo_end;
	uint8_t servo_bitmask;
	if(data->servo & SERVO_BIT_MODE) {
		servo_start = 0;
		servo_end = SERVO_NUM;
		servo_bitmask = data->servo;
	} else {
		servo_start = data->servo;
		servo_end = data->servo +1;
		servo_bitmask = 1 << data->servo;
	}

	for(uint8_t servo = servo_start; servo < servo_end; servo++) {
		if(servo_bitmask & (1 << servo)) {
			servo_disable(servo);
		}
	}

	logservoi("disable %d\n\r", data->servo);
}

void is_enabled(uint8_t com, const IsEnabled *data) {
	IsEnabledReturn ier;

	ier.stack_id      = data->stack_id;
	ier.type          = data->type;
	ier.length        = sizeof(IsEnabledReturn);
	ier.enabled       = servo_enabled[data->servo];

	send_blocking_with_timeout(&ier, sizeof(IsEnabledReturn), com);
	logservoi("is_enabled %d: %d\n\r", data->servo, ier.enabled);
}

void set_position(uint8_t com, const SetPosition *data) {
	// degree*100
	int16_t position = data->position;

	uint8_t servo_start;
	uint8_t servo_end;
	uint8_t servo_bitmask;
	if(data->servo & SERVO_BIT_MODE) {
		servo_start = 0;
		servo_end = SERVO_NUM;
		servo_bitmask = data->servo;
	} else {
		servo_start = data->servo;
		servo_end = data->servo +1;
		servo_bitmask = 1 << data->servo;
	}

	for(uint8_t servo = servo_start; servo < servo_end; servo++) {
		if(servo_bitmask & (1 << servo)) {
			if(position < servo_min_degree[servo]) {
				position = servo_min_degree[servo];
			}
			else if (position > servo_max_degree[servo]){
				position = servo_max_degree[servo];
			}

			servo_position_orig[servo] = position;

			uint32_t value = SCALE((int64_t)position,
								   (int64_t)servo_min_degree[servo],
								   (int64_t)servo_max_degree[servo],
								   (int64_t)servo_min_pulse_width[servo],
								   (int64_t)servo_max_pulse_width[servo]);

			if((servo_position_goal[servo] < servo_position[servo]) && (value > servo_position[servo])) {
				// we have changed direction -> velocity = 0
				servo_velocity[servo] = 0;
			}

			if((servo_position_goal[servo] > servo_position[servo]) && (value < servo_position[servo])) {
				// we have changed direction -> velocity = 0
				servo_velocity[servo] = 0;
			}

			servo_position_goal[servo] = value;
		}
	}

	logservoi("set_position %d: %d\n\r", data->servo, data->position);
}

void get_position(uint8_t com, const GetPosition *data) {
	uint8_t servo = data->servo;
	GetPositionReturn gpr;

	gpr.stack_id      = data->stack_id;
	gpr.type          = data->type;
	gpr.length        = sizeof(GetPositionReturn);
	gpr.position      = servo_position_orig[servo];

	send_blocking_with_timeout(&gpr, sizeof(GetPositionReturn), com);
	logservoi("get_position %d: %d %d\n\r", servo, servo_position[servo], gpr.position);
}

void get_current_position(uint8_t com, const GetCurrentPosition *data) {
	uint8_t servo = data->servo;
	GetCurrentPositionReturn gcpr;

	gcpr.stack_id      = data->stack_id;
	gcpr.type          = data->type;
	gcpr.length        = sizeof(GetCurrentPositionReturn);
	gcpr.position      = SCALE((int64_t)servo_position[servo],
	                           (int64_t)servo_min_pulse_width[servo],
	                           (int64_t)servo_max_pulse_width[servo],
	                           (int64_t)servo_min_degree[servo],
	                           (int64_t)servo_max_degree[servo]);

	send_blocking_with_timeout(&gcpr, sizeof(GetCurrentPositionReturn), com);
	logservoi("get_current_position %d: %d %d\n\r", servo, servo_position[servo], gcpr.position);
}

void set_velocity(uint8_t com, const SetVelocity *data) {
	// degree/100/period
	uint32_t value;

	uint8_t servo_start;
	uint8_t servo_end;
	uint8_t servo_bitmask;
	if(data->servo & SERVO_BIT_MODE) {
		servo_start = 0;
		servo_end = SERVO_NUM;
		servo_bitmask = data->servo;
	} else {
		servo_start = data->servo;
		servo_end = data->servo +1;
		servo_bitmask = 1 << data->servo;
	}

	for(uint8_t servo = servo_start; servo < servo_end; servo++) {
		if(servo_bitmask & (1 << servo)) {
			servo_velocity_orig[servo] = data->velocity;

			value = SCALE((int64_t)data->velocity,
						  0,
						  (int64_t)(servo_max_degree[servo] - servo_min_degree[servo]),
						  0,
						  (int64_t)(servo_max_pulse_width[servo] - servo_min_pulse_width[servo]))/servo_period[servo];


			servo_velocity_goal[servo] = value;
		}
	}

	logservoi("set_velocity %d: %d\n\r", data->servo, data->velocity);
}

void get_velocity(uint8_t com, const GetVelocity *data) {
	uint8_t servo = data->servo;
	GetVelocityReturn gvr;

	gvr.stack_id      = data->stack_id;
	gvr.type          = data->type;
	gvr.length        = sizeof(GetVelocityReturn);
	gvr.velocity      = servo_velocity_orig[servo];

	send_blocking_with_timeout(&gvr, sizeof(GetVelocityReturn), com);
	logservoi("get_velocity %d: %d %d\n\r", servo, servo_velocity[servo], gvr.velocity);
}

void get_current_velocity(uint8_t com, const GetCurrentVelocity *data) {
	uint8_t servo = data->servo;
	GetCurrentVelocityReturn gcvr;

	gcvr.stack_id      = data->stack_id;
	gcvr.type          = data->type;
	gcvr.length        = sizeof(GetCurrentVelocityReturn);
	gcvr.velocity      = SCALE((int64_t)servo_velocity[servo],
	                           0,
	                           (int64_t)(servo_max_pulse_width[servo] - servo_min_pulse_width[servo])/servo_period[servo],
	                           0,
	                           (int64_t)(servo_max_degree[servo] - servo_min_degree[servo]));

	send_blocking_with_timeout(&gcvr, sizeof(GetCurrentVelocityReturn), com);
	logservoi("get_current_velocity %d: %d %d\n\r", servo, servo_velocity[servo], gcvr.velocity);
}

void set_acceleration(uint8_t com, const SetAcceleration *data) {
	// degree/100/period**2
	int64_t value;

	uint8_t servo_start;
	uint8_t servo_end;
	uint8_t servo_bitmask;
	if(data->servo & SERVO_BIT_MODE) {
		servo_start = 0;
		servo_end = SERVO_NUM;
		servo_bitmask = data->servo;
	} else {
		servo_start = data->servo;
		servo_end = data->servo +1;
		servo_bitmask = 1 << data->servo;
	}

	for(uint8_t servo = servo_start; servo < servo_end; servo++) {
		if(servo_bitmask & (1 << servo)) {
			servo_acceleration_orig[servo] = data->acceleration;

			// Scale value between min/max pulse in ns
			value = SCALE((int64_t)data->acceleration,
						  0,
						  (int64_t)(servo_max_degree[servo]  - servo_min_degree[servo]),
						  0,
						  (int64_t)(servo_max_pulse_width[servo] - servo_min_pulse_width[servo]));


			// Scale acceleration to increment acc fraction in period (e.g. 51) steps
			value = value /(servo_period[servo]*servo_period[servo]);

			if(value < 1 && data->acceleration > 0) {
				value = 1;
			}

			servo_acceleration[servo] = value;
		}
	}

	logservoi("set_acceleration %d: %d\n\r", data->servo, data->acceleration);
}

void get_acceleration(uint8_t com, const GetAcceleration *data) {
	uint8_t servo = data->servo;
	GetAccelerationReturn gar;

	gar.stack_id      = data->stack_id;
	gar.type          = data->type;
	gar.length        = sizeof(GetAccelerationReturn);
	gar.acceleration  = servo_acceleration_orig[servo];

	send_blocking_with_timeout(&gar, sizeof(GetAccelerationReturn), com);
	logservoi("get_acceleration %d: %d %d\n\r", servo, servo_acceleration[servo], gar.acceleration);
}

void set_output_voltage(uint8_t com, const SetOutputVoltage *data) {
	servo_set_output_voltage(data->voltage);
	logservoi("set_output_voltage: %d\n\r", data->voltage);
}

void get_output_voltage(uint8_t com, const GetOutputVoltage *data) {
	GetOutputVoltageReturn govr;

	govr.stack_id      = data->stack_id;
	govr.type          = data->type;
	govr.length        = sizeof(GetOutputVoltageReturn);
	govr.voltage       = servo_get_output_voltage();

	send_blocking_with_timeout(&govr, sizeof(GetOutputVoltageReturn), com);
	logservoi("get_output_voltage: %d\n\r", govr.voltage);
}

void set_pulse_width(uint8_t com, const SetPulseWidth *data) {
	// min/max in ms
	uint32_t min_pulse_width = data->min_pulse_width*1000;
	uint32_t max_pulse_width = data->max_pulse_width*1000;


	if(data->max_pulse_width < data->min_pulse_width) {
		// Wrong data
		return;
	}

	uint8_t servo_start;
	uint8_t servo_end;
	uint8_t servo_bitmask;
	if(data->servo & SERVO_BIT_MODE) {
		servo_start = 0;
		servo_end = SERVO_NUM;
		servo_bitmask = data->servo;
	} else {
		servo_start = data->servo;
		servo_end = data->servo +1;
		servo_bitmask = 1 << data->servo;
	}

	for(uint8_t servo = servo_start; servo < servo_end; servo++) {
		if(servo_bitmask & (1 << servo)) {
			if(max_pulse_width > servo_period_length[servo]) {
				max_pulse_width = servo_period_length[servo];
			}

			servo_update_data(servo,
							  servo_period_length[servo], servo_period_length[servo],
							  servo_period[servo], servo_period[servo],
							  servo_min_pulse_width[servo], min_pulse_width,
							  servo_max_pulse_width[servo], max_pulse_width,
							  servo_min_degree[servo], servo_min_degree[servo],
							  servo_max_degree[servo], servo_max_degree[servo]);

			servo_min_pulse_width[servo] = min_pulse_width;
			servo_max_pulse_width[servo] = max_pulse_width;
		}
	}

	logservoi("set_pulse_width (min/max): %d/%d\n\r", data->min_pulse_width, data->max_pulse_width);
}

void get_pulse_width(uint8_t com, const GetPulseWidth *data) {
	GetPulseWidthReturn gpwr;

	gpwr.stack_id        = data->stack_id;
	gpwr.type            = data->type;
	gpwr.length          = sizeof(GetPulseWidthReturn);
	gpwr.max_pulse_width = servo_max_pulse_width[data->servo]/1000;
	gpwr.min_pulse_width = servo_min_pulse_width[data->servo]/1000;

	send_blocking_with_timeout(&gpwr, sizeof(GetPulseWidthReturn), com);

	logservoi("get_pulse_width (min/max): %d/%d\n\r", gpwr.min_pulse_width, gpwr.max_pulse_width);
}

void set_degree(uint8_t com, const SetDegree *data) {
	if(data->min_degree > data->max_degree) {
		// Wrong data input
		return;
	}

	uint8_t servo_start;
	uint8_t servo_end;
	uint8_t servo_bitmask;
	if(data->servo & SERVO_BIT_MODE) {
		servo_start = 0;
		servo_end = SERVO_NUM;
		servo_bitmask = data->servo;
	} else {
		servo_start = data->servo;
		servo_end = data->servo +1;
		servo_bitmask = 1 << data->servo;
	}

	for(uint8_t servo = servo_start; servo < servo_end; servo++) {
		if(servo_bitmask & (1 << servo)) {
			servo_update_data(servo,
							  servo_period_length[servo], servo_period_length[servo],
							  servo_period[servo], servo_period[servo],
							  servo_min_pulse_width[servo], servo_min_pulse_width[servo],
							  servo_max_pulse_width[servo], servo_max_pulse_width[servo],
							  servo_min_degree[servo], data->min_degree,
							  servo_max_degree[servo], data->max_degree);

			servo_max_degree[servo] = data->max_degree;
			servo_min_degree[servo] = data->min_degree;
		}
	}

	logservoi("set_degree (min/max): %d/%d\n\r", data->min_degree, data->max_degree);
}

void get_degree(uint8_t com, const GetDegree *data) {
	GetDegreeReturn gdr;

	gdr.stack_id      = data->stack_id;
	gdr.type          = data->type;
	gdr.length        = sizeof(GetDegreeReturn);
	gdr.max_degree    = servo_max_degree[data->servo];
	gdr.min_degree    = servo_min_degree[data->servo];

	send_blocking_with_timeout(&gdr, sizeof(GetDegreeReturn), com);

	logservoi("get_degree (min/max): %d/%d\n\r", gdr.min_degree, gdr.max_degree);
}

void set_period(uint8_t com, const SetPeriod *data) {
	int32_t period = data->period;

	if(period < SERVO_MIN_PERIOD) {
		period = SERVO_MIN_PERIOD * 1000;
	}
	else {
		period = period * 1000;			// we compute in ns
	}

	uint8_t servo_start;
	uint8_t servo_end;
	uint8_t servo_bitmask;
	if(data->servo & SERVO_BIT_MODE) {
		servo_start = 0;
		servo_end = SERVO_NUM;
		servo_bitmask = data->servo;
	} else {
		servo_start = data->servo;
		servo_end = data->servo +1;
		servo_bitmask = 1 << data->servo;
	}

	for(uint8_t servo = servo_start; servo < servo_end; servo++) {
		if(servo_bitmask & (1 << servo)) {
			servo_update_data(servo,
							  servo_period_length[servo], period,
							  servo_period[servo], 1000000*1000/period,
							  servo_min_pulse_width[servo], servo_min_pulse_width[servo],
							  servo_max_pulse_width[servo], servo_max_pulse_width[servo],
							  servo_min_degree[servo], servo_min_degree[servo],
							  servo_max_degree[servo], servo_max_degree[servo]);

			servo_period_length[servo] = period;
			servo_period[servo] = 1000000*1000/period;

			servo_set_period(servo, data->period);
		}
	}

	logservoi("set_period: %d\n\r", data->period);
}

void get_period(uint8_t com, const GetPeriod *data) {
	GetPeriodReturn gpr;

	gpr.stack_id      = data->stack_id;
	gpr.type          = data->type;
	gpr.length        = sizeof(GetPeriodReturn);
	gpr.period        = servo_get_period(data->servo);

	send_blocking_with_timeout(&gpr, sizeof(GetPeriodReturn), com);
	logservoi("get_period: %d\n\r", gpr.period);
}

void get_servo_current(uint8_t com, const GetServoCurrent *data) {
	GetServoCurrentReturn gscr;

	gscr.stack_id      = data->stack_id;
	gscr.type          = data->type;
	gscr.length        = sizeof(GetServoCurrentReturn);

	gscr.current       = (servo_current[data->servo]*300*10)/(1023);

	send_blocking_with_timeout(&gscr, sizeof(GetServoCurrentReturn), com);
	logservoi("get_servo_current: %d\n\r", gscr.current);
}

void get_overall_current(uint8_t com, const GetOverallCurrent *data) {
	GetOverallCurrentReturn gocr;

	gocr.stack_id      = data->stack_id;
	gocr.type          = data->type;
	gocr.length        = sizeof(GetOverallCurrentReturn);

	gocr.current = 0;
	for(uint8_t i = 0; i < SERVO_NUM; i++) {
		gocr.current += servo_current[i];
	}
	gocr.current = (gocr.current*300*10)/(1023);

	send_blocking_with_timeout(&gocr, sizeof(GetOverallCurrentReturn), com);
}

void get_stack_input_voltage(uint8_t com, const GetStackInputVoltage *data) {
	GetStackInputVoltageReturn gsivr;

	gsivr.stack_id      = data->stack_id;
	gsivr.type          = data->type;
	gsivr.length        = sizeof(GetStackInputVoltageReturn);
    gsivr.voltage       = servo_get_stack_voltage();

	send_blocking_with_timeout(&gsivr, sizeof(GetStackInputVoltageReturn), com);
	logservoi("get_stack_input_voltage: %d\n\r", gsivr.voltage);
}

void get_external_input_voltage(uint8_t com, const GetExternalInputVoltage *data) {
	GetExternalInputVoltageReturn geivr;

	geivr.stack_id      = data->stack_id;
	geivr.type          = data->type;
	geivr.length        = sizeof(GetExternalInputVoltageReturn);
    geivr.voltage       = servo_get_external_voltage();

	send_blocking_with_timeout(&geivr, sizeof(GetExternalInputVoltageReturn), com);
	logservoi("get_external_input_voltage: %d\n\r", geivr.voltage);
}

void set_minimum_voltage(uint8_t com, const SetMinimumVoltage *data) {
	servo_minimum_voltage = BETWEEN(SERVO_MIN_VOLTAGE,
	                                data->voltage,
	                                SERVO_MAX_VOLTAGE);
}

void get_minimum_voltage(uint8_t com, const GetMinimumVoltage *data) {
	GetMinimumVoltageReturn gmvr;

	gmvr.stack_id      = data->stack_id;
	gmvr.type          = data->type;
	gmvr.length        = sizeof(GetMinimumVoltageReturn);
	gmvr.voltage       = servo_minimum_voltage;

	send_blocking_with_timeout(&gmvr, sizeof(GetMinimumVoltageReturn), com);
}
