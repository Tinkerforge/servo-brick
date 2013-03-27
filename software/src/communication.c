/* servo-brick
 * Copyright (C) 2010-2012 Olaf Lüke <olaf@tinkerforge.com>
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
extern uint32_t servo_acceleration[];
extern uint32_t servo_max_pulse_width[];
extern uint32_t servo_min_pulse_width[];
extern int16_t servo_max_degree[];
extern int16_t servo_min_degree[];
extern uint16_t servo_current[];
extern uint16_t servo_position_orig[];
extern uint16_t servo_velocity_orig[];
extern uint16_t servo_acceleration_orig[];
extern uint16_t servo_minimum_voltage;

extern bool velocity_reached_callback_enabled;
extern bool position_reached_callback_enabled;

void enable(const ComType com, const Enable *data) {
	uint8_t servo_start;
	uint8_t servo_end;
	uint8_t servo_bitmask;
	if(data->servo & SERVO_BIT_MODE) {
		servo_start = 0;
		servo_end = SERVO_NUM;
		servo_bitmask = data->servo;
	} else {
		if(data->servo >= SERVO_NUM) {
			com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
			return;
		}

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

	com_return_setter(com, data);
}

void disable(const ComType com, const Disable *data) {
	uint8_t servo_start;
	uint8_t servo_end;
	uint8_t servo_bitmask;
	if(data->servo & SERVO_BIT_MODE) {
		servo_start = 0;
		servo_end = SERVO_NUM;
		servo_bitmask = data->servo;
	} else {
		if(data->servo >= SERVO_NUM) {
			com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
			return;
		}

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

	com_return_setter(com, data);
}

void is_enabled(const ComType com, const IsEnabled *data) {
	IsEnabledReturn ier;

	if(data->servo >= SERVO_NUM) {
		com_return_error(data, sizeof(IsEnabledReturn), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	ier.header        = data->header;
	ier.header.length = sizeof(IsEnabledReturn);
	ier.enabled       = servo_enabled[data->servo];

	send_blocking_with_timeout(&ier, sizeof(IsEnabledReturn), com);
	logservoi("is_enabled %d: %d\n\r", data->servo, ier.enabled);
}

void set_position(const ComType com, const SetPosition *data) {
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
		if(data->servo >= SERVO_NUM) {
			com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
			return;
		}

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

	com_return_setter(com, data);
}

void get_position(const ComType com, const GetPosition *data) {
	uint8_t servo = data->servo;
	GetPositionReturn gpr;

	if(servo >= SERVO_NUM) {
		com_return_error(data, sizeof(GetPositionReturn), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	gpr.header        = data->header;
	gpr.header.length = sizeof(GetPositionReturn);
	gpr.position      = servo_position_orig[servo];

	send_blocking_with_timeout(&gpr, sizeof(GetPositionReturn), com);
	logservoi("get_position %d: %d %d\n\r", servo, servo_position[servo], gpr.position);
}

void get_current_position(const ComType com, const GetCurrentPosition *data) {
	uint8_t servo = data->servo;
	GetCurrentPositionReturn gcpr;

	if(servo >= SERVO_NUM) {
		com_return_error(data, sizeof(GetCurrentPositionReturn), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	gcpr.header        = data->header;
	gcpr.header.length = sizeof(GetCurrentPositionReturn);
	gcpr.position      = SCALE((int64_t)servo_position[servo],
	                           (int64_t)servo_min_pulse_width[servo],
	                           (int64_t)servo_max_pulse_width[servo],
	                           (int64_t)servo_min_degree[servo],
	                           (int64_t)servo_max_degree[servo]);

	send_blocking_with_timeout(&gcpr, sizeof(GetCurrentPositionReturn), com);
	logservoi("get_current_position %d: %d %d\n\r", servo, servo_position[servo], gcpr.position);
}

void set_velocity(const ComType com, const SetVelocity *data) {
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
		if(data->servo >= SERVO_NUM) {
			com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
			return;
		}

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

	com_return_setter(com, data);
}

void get_velocity(const ComType com, const GetVelocity *data) {
	uint8_t servo = data->servo;
	GetVelocityReturn gvr;

	if(servo >= SERVO_NUM) {
		com_return_error(data, sizeof(GetVelocityReturn), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	gvr.header        = data->header;
	gvr.header.length = sizeof(GetVelocityReturn);
	gvr.velocity      = servo_velocity_orig[servo];

	send_blocking_with_timeout(&gvr, sizeof(GetVelocityReturn), com);
	logservoi("get_velocity %d: %d %d\n\r", servo, servo_velocity[servo], gvr.velocity);
}

void get_current_velocity(const ComType com, const GetCurrentVelocity *data) {
	uint8_t servo = data->servo;
	GetCurrentVelocityReturn gcvr;

	if(servo >= SERVO_NUM) {
		com_return_error(data, sizeof(GetCurrentVelocityReturn), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	gcvr.header        = data->header;
	gcvr.header.length = sizeof(GetCurrentVelocityReturn);
	gcvr.velocity      = SCALE((int64_t)servo_velocity[servo],
	                           0,
	                           (int64_t)(servo_max_pulse_width[servo] - servo_min_pulse_width[servo])/servo_period[servo],
	                           0,
	                           (int64_t)(servo_max_degree[servo] - servo_min_degree[servo]));

	send_blocking_with_timeout(&gcvr, sizeof(GetCurrentVelocityReturn), com);
	logservoi("get_current_velocity %d: %d %d\n\r", servo, servo_velocity[servo], gcvr.velocity);
}

void set_acceleration(const ComType com, const SetAcceleration *data) {
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
		if(data->servo >= SERVO_NUM) {
			com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
			return;
		}

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

	com_return_setter(com, data);
}

void get_acceleration(const ComType com, const GetAcceleration *data) {
	uint8_t servo = data->servo;
	GetAccelerationReturn gar;

	if(servo >= SERVO_NUM) {
		com_return_error(data, sizeof(GetAccelerationReturn), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	gar.header        = data->header;
	gar.header.length = sizeof(GetAccelerationReturn);
	gar.acceleration  = servo_acceleration_orig[servo];

	send_blocking_with_timeout(&gar, sizeof(GetAccelerationReturn), com);
	logservoi("get_acceleration %d: %d %d\n\r", servo, servo_acceleration[servo], gar.acceleration);
}

void set_output_voltage(const ComType com, const SetOutputVoltage *data) {
	servo_set_output_voltage(data->voltage);
	logservoi("set_output_voltage: %d\n\r", data->voltage);

	com_return_setter(com, data);
}

void get_output_voltage(const ComType com, const GetOutputVoltage *data) {
	GetOutputVoltageReturn govr;

	govr.header        = data->header;
	govr.header.length = sizeof(GetOutputVoltageReturn);
	govr.voltage       = servo_get_output_voltage();

	send_blocking_with_timeout(&govr, sizeof(GetOutputVoltageReturn), com);
	logservoi("get_output_voltage: %d\n\r", govr.voltage);
}

void set_pulse_width(const ComType com, const SetPulseWidth *data) {
	// min/max in ms
	uint32_t min_pulse_width = data->min_pulse_width*1000;
	uint32_t max_pulse_width = data->max_pulse_width*1000;


	if(data->max_pulse_width < data->min_pulse_width) {
		com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
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
		if(data->servo >= SERVO_NUM) {
			com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
			return;
		}

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

	com_return_setter(com, data);
}

void get_pulse_width(const ComType com, const GetPulseWidth *data) {
	GetPulseWidthReturn gpwr;

	if(data->servo >= SERVO_NUM) {
		com_return_error(data, sizeof(GetPulseWidthReturn), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	gpwr.header        = data->header;
	gpwr.header.length = sizeof(GetPulseWidthReturn);
	gpwr.max_pulse_width = servo_max_pulse_width[data->servo]/1000;
	gpwr.min_pulse_width = servo_min_pulse_width[data->servo]/1000;

	send_blocking_with_timeout(&gpwr, sizeof(GetPulseWidthReturn), com);

	logservoi("get_pulse_width (min/max): %d/%d\n\r", gpwr.min_pulse_width, gpwr.max_pulse_width);
}

void set_degree(const ComType com, const SetDegree *data) {
	if(data->min_degree > data->max_degree) {
		com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
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
		if(data->servo >= SERVO_NUM) {
			com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
			return;
		}

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

	com_return_setter(com, data);
}

void get_degree(const ComType com, const GetDegree *data) {
	GetDegreeReturn gdr;

	if(data->servo >= SERVO_NUM) {
		com_return_error(data, sizeof(GetDegreeReturn), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	gdr.header        = data->header;
	gdr.header.length = sizeof(GetDegreeReturn);
	gdr.max_degree    = servo_max_degree[data->servo];
	gdr.min_degree    = servo_min_degree[data->servo];

	send_blocking_with_timeout(&gdr, sizeof(GetDegreeReturn), com);

	logservoi("get_degree (min/max): %d/%d\n\r", gdr.min_degree, gdr.max_degree);
}

void set_period(const ComType com, const SetPeriod *data) {
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
		if(data->servo >= SERVO_NUM) {
			com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
			return;
		}

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

	com_return_setter(com, data);
}

void get_period(const ComType com, const GetPeriod *data) {
	GetPeriodReturn gpr;

	if(data->servo >= SERVO_NUM) {
		com_return_error(data, sizeof(GetPeriodReturn), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	gpr.header        = data->header;
	gpr.header.length = sizeof(GetPeriodReturn);
	gpr.period        = servo_get_period(data->servo);

	send_blocking_with_timeout(&gpr, sizeof(GetPeriodReturn), com);
	logservoi("get_period: %d\n\r", gpr.period);
}

void get_servo_current(const ComType com, const GetServoCurrent *data) {
	GetServoCurrentReturn gscr;

	if(data->servo >= SERVO_NUM) {
		com_return_error(data, sizeof(GetServoCurrentReturn), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	gscr.header        = data->header;
	gscr.header.length = sizeof(GetServoCurrentReturn);
	gscr.current       = (servo_current[data->servo]*300*10)/(1023);

	send_blocking_with_timeout(&gscr, sizeof(GetServoCurrentReturn), com);
	logservoi("get_servo_current: %d\n\r", gscr.current);
}

void get_overall_current(const ComType com, const GetOverallCurrent *data) {
	GetOverallCurrentReturn gocr;

	gocr.header        = data->header;
	gocr.header.length = sizeof(GetOverallCurrentReturn);

	gocr.current = 0;
	for(uint8_t i = 0; i < SERVO_NUM; i++) {
		gocr.current += servo_current[i];
	}
	gocr.current = (gocr.current*300*10)/(1023);

	send_blocking_with_timeout(&gocr, sizeof(GetOverallCurrentReturn), com);
}

void get_stack_input_voltage(const ComType com, const GetStackInputVoltage *data) {
	GetStackInputVoltageReturn gsivr;

	gsivr.header        = data->header;
	gsivr.header.length = sizeof(GetStackInputVoltageReturn);
    gsivr.voltage       = servo_get_stack_voltage();

	send_blocking_with_timeout(&gsivr, sizeof(GetStackInputVoltageReturn), com);
	logservoi("get_stack_input_voltage: %d\n\r", gsivr.voltage);
}

void get_external_input_voltage(const ComType com, const GetExternalInputVoltage *data) {
	GetExternalInputVoltageReturn geivr;

	geivr.header        = data->header;
	geivr.header.length = sizeof(GetExternalInputVoltageReturn);
    geivr.voltage       = servo_get_external_voltage();

	send_blocking_with_timeout(&geivr, sizeof(GetExternalInputVoltageReturn), com);
	logservoi("get_external_input_voltage: %d\n\r", geivr.voltage);
}

void set_minimum_voltage(const ComType com, const SetMinimumVoltage *data) {
	servo_minimum_voltage = BETWEEN(SERVO_MIN_VOLTAGE,
	                                data->voltage,
	                                SERVO_MAX_VOLTAGE);

	com_return_setter(com, data);
}

void get_minimum_voltage(const ComType com, const GetMinimumVoltage *data) {
	GetMinimumVoltageReturn gmvr;

	gmvr.header        = data->header;
	gmvr.header.length = sizeof(GetMinimumVoltageReturn);
	gmvr.voltage       = servo_minimum_voltage;

	send_blocking_with_timeout(&gmvr, sizeof(GetMinimumVoltageReturn), com);
}

void enable_velocity_reached_callback(const ComType com, const EnableVelocityReachedCallback *data) {
	velocity_reached_callback_enabled = true;
	com_return_setter(com, data);
}

void disable_velocity_reached_callback(const ComType com, const DisableVelocityReachedCallback *data) {
	velocity_reached_callback_enabled = false;
	com_return_setter(com, data);
}

void is_velocity_reached_callback_enabled(const ComType com, const IsVelocityReachedCallbackEnabled *data) {
	IsVelocityReachedCallbackEnabledReturn ivrcer;

	ivrcer.header        = data->header;
	ivrcer.header.length = sizeof(IsVelocityReachedCallbackEnabledReturn);
	ivrcer.enabled       = velocity_reached_callback_enabled;

	send_blocking_with_timeout(&ivrcer, sizeof(IsVelocityReachedCallbackEnabledReturn), com);
}

void enable_position_reached_callback(const ComType com, const EnablePositionReachedCallback *data) {
	position_reached_callback_enabled = true;
	com_return_setter(com, data);
}

void disable_position_reached_callback(const ComType com, const DisablePositionReachedCallback *data) {
	com_return_setter(com, data);
	position_reached_callback_enabled = false;
}

void is_position_reached_callback_enabled(const ComType com, const IsPositionReachedCallbackEnabled *data) {
	IsPositionReachedCallbackEnabledReturn iprcer;

	iprcer.header        = data->header;
	iprcer.header.length = sizeof(IsPositionReachedCallbackEnabledReturn);
	iprcer.enabled       = position_reached_callback_enabled;

	send_blocking_with_timeout(&iprcer, sizeof(IsPositionReachedCallbackEnabledReturn), com);
}
