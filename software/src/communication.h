/* servo-brick
 * Copyright (C) 2010-2011 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.h: Implementation of Servo-Brick specific messages
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


#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>
#include <stdbool.h>

#define TYPE_ENABLE 1
#define TYPE_DISABLE 2
#define TYPE_IS_ENABLED 3
#define TYPE_SET_POSITION 4
#define TYPE_GET_POSITION 5
#define TYPE_GET_CURRENT_POSITION 6
#define TYPE_SET_VELOCITY 7
#define TYPE_GET_VELOCITY 8
#define TYPE_GET_CURRENT_VELOCITY 9
#define TYPE_SET_ACCELERATION 10
#define TYPE_GET_ACCELERATION 11
#define TYPE_SET_OUTPUT_VOLTAGE 12
#define TYPE_GET_OUTPUT_VOLTAGE 13
#define TYPE_SET_PULSE_WIDTH 14
#define TYPE_GET_PULSE_WIDTH 15
#define TYPE_SET_DEGREE 16
#define TYPE_GET_DEGREE 17
#define TYPE_SET_PERIOD 18
#define TYPE_GET_PERIOD 19
#define TYPE_GET_SERVO_CURRENT 20
#define TYPE_GET_OVERALL_CURRENT 21
#define TYPE_GET_STACK_INPUT_VOLTAGE 22
#define TYPE_GET_EXTERNAL_INPUT_VOLTAGE 23
#define TYPE_SET_MINIMUM_VOLTAGE 24
#define TYPE_GET_MINIMUM_VOLTAGE 25
#define TYPE_UNDER_VOLTAGE 26
#define TYPE_POSITION_REACHED 27
#define TYPE_VELOCITY_REACHED 28

#define COM_MESSAGES_USER \
	{TYPE_ENABLE, (message_handler_func_t)enable}, \
	{TYPE_DISABLE, (message_handler_func_t)disable}, \
	{TYPE_IS_ENABLED, (message_handler_func_t)is_enabled}, \
	{TYPE_SET_POSITION, (message_handler_func_t)set_position}, \
	{TYPE_GET_POSITION, (message_handler_func_t)get_position}, \
	{TYPE_GET_CURRENT_POSITION, (message_handler_func_t)get_current_position}, \
	{TYPE_SET_VELOCITY, (message_handler_func_t)set_velocity}, \
	{TYPE_GET_VELOCITY, (message_handler_func_t)get_velocity}, \
	{TYPE_GET_CURRENT_VELOCITY, (message_handler_func_t)get_current_velocity}, \
	{TYPE_SET_ACCELERATION, (message_handler_func_t)set_acceleration}, \
	{TYPE_GET_ACCELERATION, (message_handler_func_t)get_acceleration}, \
	{TYPE_SET_OUTPUT_VOLTAGE, (message_handler_func_t)set_output_voltage}, \
	{TYPE_GET_OUTPUT_VOLTAGE, (message_handler_func_t)get_output_voltage}, \
	{TYPE_SET_PULSE_WIDTH, (message_handler_func_t)set_pulse_width}, \
	{TYPE_GET_PULSE_WIDTH, (message_handler_func_t)get_pulse_width}, \
	{TYPE_SET_DEGREE, (message_handler_func_t)set_degree}, \
	{TYPE_GET_DEGREE, (message_handler_func_t)get_degree}, \
	{TYPE_SET_PERIOD, (message_handler_func_t)set_period}, \
	{TYPE_GET_PERIOD, (message_handler_func_t)get_period}, \
	{TYPE_GET_SERVO_CURRENT, (message_handler_func_t)get_servo_current}, \
	{TYPE_GET_OVERALL_CURRENT, (message_handler_func_t)get_overall_current}, \
	{TYPE_GET_STACK_INPUT_VOLTAGE, (message_handler_func_t)get_stack_input_voltage}, \
	{TYPE_GET_EXTERNAL_INPUT_VOLTAGE, (message_handler_func_t)get_external_input_voltage}, \
	{TYPE_SET_MINIMUM_VOLTAGE, (message_handler_func_t)set_minimum_voltage}, \
    {TYPE_GET_MINIMUM_VOLTAGE, (message_handler_func_t)get_minimum_voltage},

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo;
} __attribute__((__packed__)) Enable;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo;
} __attribute__((__packed__)) Disable;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo;
} __attribute__((__packed__)) IsEnabled;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	bool enabled;
} __attribute__((__packed__)) IsEnabledReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo;
	int16_t position;
} __attribute__((__packed__)) SetPosition;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo;
} __attribute__((__packed__)) GetPosition;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	int16_t position;
} __attribute__((__packed__)) GetPositionReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo;
} __attribute__((__packed__)) GetCurrentPosition;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	int16_t position;
} __attribute__((__packed__)) GetCurrentPositionReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo;
	uint16_t velocity;
} __attribute__((__packed__)) SetVelocity;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo;
} __attribute__((__packed__)) GetVelocity;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t velocity;
} __attribute__((__packed__)) GetVelocityReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo;
} __attribute__((__packed__)) GetCurrentVelocity;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t velocity;
} __attribute__((__packed__)) GetCurrentVelocityReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo;
	uint16_t acceleration;
} __attribute__((__packed__)) SetAcceleration;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo;
} __attribute__((__packed__)) GetAcceleration;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t acceleration;
} __attribute__((__packed__)) GetAccelerationReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} __attribute__((__packed__)) SetOutputVoltage;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetOutputVoltage;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} __attribute__((__packed__)) GetOutputVoltageReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo;
	uint16_t min_pulse_width;
	uint16_t max_pulse_width;
} __attribute__((__packed__)) SetPulseWidth;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo;
} __attribute__((__packed__)) GetPulseWidth;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t min_pulse_width;
	uint16_t max_pulse_width;
} __attribute__((__packed__)) GetPulseWidthReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo;
	int16_t min_degree;
	int16_t max_degree;
} __attribute__((__packed__)) SetDegree;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo;
} __attribute__((__packed__)) GetDegree;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	int16_t min_degree;
	int16_t max_degree;
} __attribute__((__packed__)) GetDegreeReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo;
	uint16_t period;
} __attribute__((__packed__)) SetPeriod;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo;
} __attribute__((__packed__)) GetPeriod;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t period;
} __attribute__((__packed__)) GetPeriodReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo;
} __attribute__((__packed__)) GetServoCurrent;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t current;
} __attribute__((__packed__)) GetServoCurrentReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetOverallCurrent;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t current;
} __attribute__((__packed__)) GetOverallCurrentReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetStackInputVoltage;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} __attribute__((__packed__)) GetStackInputVoltageReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetExternalInputVoltage;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} __attribute__((__packed__)) GetExternalInputVoltageReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} __attribute__((__packed__)) SetMinimumVoltage;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetMinimumVoltage;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} __attribute__((__packed__)) GetMinimumVoltageReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} __attribute__((__packed__)) UnderVoltageSignal;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo;
	int16_t position;
} __attribute__((__packed__)) PositionReachedSignal;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo;
	int16_t velocity;
} __attribute__((__packed__)) VelocityReachedSignal;

void enable(uint8_t com, const Enable *data);
void disable(uint8_t com, const Disable *data);
void is_enabled(uint8_t com, const IsEnabled *data);
void set_position(uint8_t com, const SetPosition *data);
void get_position(uint8_t com, const GetPosition *data);
void get_current_position(uint8_t com, const GetCurrentPosition *data);
void set_velocity(uint8_t com, const SetVelocity *data);
void get_velocity(uint8_t com, const GetVelocity *data);
void get_current_velocity(uint8_t com, const GetCurrentVelocity *data);
void set_acceleration(uint8_t com, const SetAcceleration *data);
void get_acceleration(uint8_t com, const GetAcceleration *data);
void set_output_voltage(uint8_t com, const SetOutputVoltage *data);
void get_output_voltage(uint8_t com, const GetOutputVoltage *data);
void set_pulse_width(uint8_t com, const SetPulseWidth *data);
void get_pulse_width(uint8_t com, const GetPulseWidth *data);
void set_degree(uint8_t com, const SetDegree *data);
void get_degree(uint8_t com, const GetDegree *data);
void set_period(uint8_t com, const SetPeriod *data);
void get_period(uint8_t com, const GetPeriod *data);
void get_servo_current(uint8_t com, const GetServoCurrent *data);
void get_overall_current(uint8_t com, const GetOverallCurrent *data);
void get_stack_input_voltage(uint8_t com, const GetStackInputVoltage *data);
void get_external_input_voltage(uint8_t com, const GetExternalInputVoltage *data);
void set_minimum_voltage(uint8_t com, const SetMinimumVoltage *data);
void get_minimum_voltage(uint8_t com, const GetMinimumVoltage *data);

#endif
