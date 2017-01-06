/* servo-brick
 * Copyright (C) 2010-2013 Olaf Lüke <olaf@tinkerforge.com>
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

#include "bricklib/com/com_common.h"

#define FID_ENABLE 1
#define FID_DISABLE 2
#define FID_IS_ENABLED 3
#define FID_SET_POSITION 4
#define FID_GET_POSITION 5
#define FID_GET_CURRENT_POSITION 6
#define FID_SET_VELOCITY 7
#define FID_GET_VELOCITY 8
#define FID_GET_CURRENT_VELOCITY 9
#define FID_SET_ACCELERATION 10
#define FID_GET_ACCELERATION 11
#define FID_SET_OUTPUT_VOLTAGE 12
#define FID_GET_OUTPUT_VOLTAGE 13
#define FID_SET_PULSE_WIDTH 14
#define FID_GET_PULSE_WIDTH 15
#define FID_SET_DEGREE 16
#define FID_GET_DEGREE 17
#define FID_SET_PERIOD 18
#define FID_GET_PERIOD 19
#define FID_GET_SERVO_CURRENT 20
#define FID_GET_OVERALL_CURRENT 21
#define FID_GET_STACK_INPUT_VOLTAGE 22
#define FID_GET_EXTERNAL_INPUT_VOLTAGE 23
#define FID_SET_MINIMUM_VOLTAGE 24
#define FID_GET_MINIMUM_VOLTAGE 25
#define FID_UNDER_VOLTAGE 26
#define FID_POSITION_REACHED 27
#define FID_VELOCITY_REACHED 28
#define FID_ENABLE_POSITION_REACHED_CALLBACK 29
#define FID_DISABLE_POSITION_REACHED_CALLBACK 30
#define FID_IS_POSITION_REACHED_CALLBACK_ENABLED 31
#define FID_ENABLE_VELOCITY_REACHED_CALLBACK 32
#define FID_DISABLE_VELOCITY_REACHED_CALLBACK 33
#define FID_IS_VELOCITY_REACHED_CALLBACK_ENABLED 34

#define COM_MESSAGE_USER_LAST_FID 34

#define COM_MESSAGES_USER \
	{FID_ENABLE, (message_handler_func_t)enable}, \
	{FID_DISABLE, (message_handler_func_t)disable}, \
	{FID_IS_ENABLED, (message_handler_func_t)is_enabled}, \
	{FID_SET_POSITION, (message_handler_func_t)set_position}, \
	{FID_GET_POSITION, (message_handler_func_t)get_position}, \
	{FID_GET_CURRENT_POSITION, (message_handler_func_t)get_current_position}, \
	{FID_SET_VELOCITY, (message_handler_func_t)set_velocity}, \
	{FID_GET_VELOCITY, (message_handler_func_t)get_velocity}, \
	{FID_GET_CURRENT_VELOCITY, (message_handler_func_t)get_current_velocity}, \
	{FID_SET_ACCELERATION, (message_handler_func_t)set_acceleration}, \
	{FID_GET_ACCELERATION, (message_handler_func_t)get_acceleration}, \
	{FID_SET_OUTPUT_VOLTAGE, (message_handler_func_t)set_output_voltage}, \
	{FID_GET_OUTPUT_VOLTAGE, (message_handler_func_t)get_output_voltage}, \
	{FID_SET_PULSE_WIDTH, (message_handler_func_t)set_pulse_width}, \
	{FID_GET_PULSE_WIDTH, (message_handler_func_t)get_pulse_width}, \
	{FID_SET_DEGREE, (message_handler_func_t)set_degree}, \
	{FID_GET_DEGREE, (message_handler_func_t)get_degree}, \
	{FID_SET_PERIOD, (message_handler_func_t)set_period}, \
	{FID_GET_PERIOD, (message_handler_func_t)get_period}, \
	{FID_GET_SERVO_CURRENT, (message_handler_func_t)get_servo_current}, \
	{FID_GET_OVERALL_CURRENT, (message_handler_func_t)get_overall_current}, \
	{FID_GET_STACK_INPUT_VOLTAGE, (message_handler_func_t)get_stack_input_voltage}, \
	{FID_GET_EXTERNAL_INPUT_VOLTAGE, (message_handler_func_t)get_external_input_voltage}, \
	{FID_SET_MINIMUM_VOLTAGE, (message_handler_func_t)set_minimum_voltage}, \
    {FID_GET_MINIMUM_VOLTAGE, (message_handler_func_t)get_minimum_voltage}, \
    {FID_UNDER_VOLTAGE, (message_handler_func_t)NULL}, \
    {FID_POSITION_REACHED, (message_handler_func_t)NULL}, \
    {FID_VELOCITY_REACHED, (message_handler_func_t)NULL}, \
    {FID_ENABLE_POSITION_REACHED_CALLBACK, (message_handler_func_t)enable_position_reached_callback}, \
    {FID_DISABLE_POSITION_REACHED_CALLBACK, (message_handler_func_t)disable_position_reached_callback}, \
    {FID_IS_POSITION_REACHED_CALLBACK_ENABLED, (message_handler_func_t)is_position_reached_callback_enabled}, \
    {FID_ENABLE_VELOCITY_REACHED_CALLBACK, (message_handler_func_t)enable_velocity_reached_callback}, \
    {FID_DISABLE_VELOCITY_REACHED_CALLBACK, (message_handler_func_t)disable_velocity_reached_callback}, \
    {FID_IS_VELOCITY_REACHED_CALLBACK_ENABLED, (message_handler_func_t)is_velocity_reached_callback_enabled},

typedef struct {
	MessageHeader header;
	uint8_t servo;
} __attribute__((__packed__)) Enable;

typedef struct {
	MessageHeader header;
	uint8_t servo;
} __attribute__((__packed__)) Disable;

typedef struct {
	MessageHeader header;
	uint8_t servo;
} __attribute__((__packed__)) IsEnabled;

typedef struct {
	MessageHeader header;
	bool enabled;
} __attribute__((__packed__)) IsEnabledReturn;

typedef struct {
	MessageHeader header;
	uint8_t servo;
	int16_t position;
} __attribute__((__packed__)) SetPosition;

typedef struct {
	MessageHeader header;
	uint8_t servo;
} __attribute__((__packed__)) GetPosition;

typedef struct {
	MessageHeader header;
	int16_t position;
} __attribute__((__packed__)) GetPositionReturn;

typedef struct {
	MessageHeader header;
	uint8_t servo;
} __attribute__((__packed__)) GetCurrentPosition;

typedef struct {
	MessageHeader header;
	int16_t position;
} __attribute__((__packed__)) GetCurrentPositionReturn;

typedef struct {
	MessageHeader header;
	uint8_t servo;
	uint16_t velocity;
} __attribute__((__packed__)) SetVelocity;

typedef struct {
	MessageHeader header;
	uint8_t servo;
} __attribute__((__packed__)) GetVelocity;

typedef struct {
	MessageHeader header;
	uint16_t velocity;
} __attribute__((__packed__)) GetVelocityReturn;

typedef struct {
	MessageHeader header;
	uint8_t servo;
} __attribute__((__packed__)) GetCurrentVelocity;

typedef struct {
	MessageHeader header;
	uint16_t velocity;
} __attribute__((__packed__)) GetCurrentVelocityReturn;

typedef struct {
	MessageHeader header;
	uint8_t servo;
	uint16_t acceleration;
} __attribute__((__packed__)) SetAcceleration;

typedef struct {
	MessageHeader header;
	uint8_t servo;
} __attribute__((__packed__)) GetAcceleration;

typedef struct {
	MessageHeader header;
	uint16_t acceleration;
} __attribute__((__packed__)) GetAccelerationReturn;

typedef struct {
	MessageHeader header;
	uint16_t voltage;
} __attribute__((__packed__)) SetOutputVoltage;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetOutputVoltage;

typedef struct {
	MessageHeader header;
	uint16_t voltage;
} __attribute__((__packed__)) GetOutputVoltageReturn;

typedef struct {
	MessageHeader header;
	uint8_t servo;
	uint16_t min_pulse_width;
	uint16_t max_pulse_width;
} __attribute__((__packed__)) SetPulseWidth;

typedef struct {
	MessageHeader header;
	uint8_t servo;
} __attribute__((__packed__)) GetPulseWidth;

typedef struct {
	MessageHeader header;
	uint16_t min_pulse_width;
	uint16_t max_pulse_width;
} __attribute__((__packed__)) GetPulseWidthReturn;

typedef struct {
	MessageHeader header;
	uint8_t servo;
	int16_t min_degree;
	int16_t max_degree;
} __attribute__((__packed__)) SetDegree;

typedef struct {
	MessageHeader header;
	uint8_t servo;
} __attribute__((__packed__)) GetDegree;

typedef struct {
	MessageHeader header;
	int16_t min_degree;
	int16_t max_degree;
} __attribute__((__packed__)) GetDegreeReturn;

typedef struct {
	MessageHeader header;
	uint8_t servo;
	uint16_t period;
} __attribute__((__packed__)) SetPeriod;

typedef struct {
	MessageHeader header;
	uint8_t servo;
} __attribute__((__packed__)) GetPeriod;

typedef struct {
	MessageHeader header;
	uint16_t period;
} __attribute__((__packed__)) GetPeriodReturn;

typedef struct {
	MessageHeader header;
	uint8_t servo;
} __attribute__((__packed__)) GetServoCurrent;

typedef struct {
	MessageHeader header;
	uint16_t current;
} __attribute__((__packed__)) GetServoCurrentReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetOverallCurrent;

typedef struct {
	MessageHeader header;
	uint16_t current;
} __attribute__((__packed__)) GetOverallCurrentReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetStackInputVoltage;

typedef struct {
	MessageHeader header;
	uint16_t voltage;
} __attribute__((__packed__)) GetStackInputVoltageReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetExternalInputVoltage;

typedef struct {
	MessageHeader header;
	uint16_t voltage;
} __attribute__((__packed__)) GetExternalInputVoltageReturn;

typedef struct {
	MessageHeader header;
	uint16_t voltage;
} __attribute__((__packed__)) SetMinimumVoltage;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetMinimumVoltage;

typedef struct {
	MessageHeader header;
	uint16_t voltage;
} __attribute__((__packed__)) GetMinimumVoltageReturn;

typedef struct {
	MessageHeader header;
	uint16_t voltage;
} __attribute__((__packed__)) UnderVoltageCallback;

typedef struct {
	MessageHeader header;
	uint8_t servo;
	int16_t position;
} __attribute__((__packed__)) PositionReachedCallback;

typedef struct {
	MessageHeader header;
	uint8_t servo;
	int16_t velocity;
} __attribute__((__packed__)) VelocityReachedCallback;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) EnableVelocityReachedCallback;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) DisableVelocityReachedCallback;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) IsVelocityReachedCallbackEnabled;

typedef struct {
	MessageHeader header;
	bool enabled;
} __attribute__((__packed__)) IsVelocityReachedCallbackEnabledReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) EnablePositionReachedCallback;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) DisablePositionReachedCallback;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) IsPositionReachedCallbackEnabled;

typedef struct {
	MessageHeader header;
	bool enabled;
} __attribute__((__packed__)) IsPositionReachedCallbackEnabledReturn;

void enable(const ComType com, const Enable *data);
void disable(const ComType com, const Disable *data);
void is_enabled(const ComType com, const IsEnabled *data);
void set_position(const ComType com, const SetPosition *data);
void get_position(const ComType com, const GetPosition *data);
void get_current_position(const ComType com, const GetCurrentPosition *data);
void set_velocity(const ComType com, const SetVelocity *data);
void get_velocity(const ComType com, const GetVelocity *data);
void get_current_velocity(const ComType com, const GetCurrentVelocity *data);
void set_acceleration(const ComType com, const SetAcceleration *data);
void get_acceleration(const ComType com, const GetAcceleration *data);
void set_output_voltage(const ComType com, const SetOutputVoltage *data);
void get_output_voltage(const ComType com, const GetOutputVoltage *data);
void set_pulse_width(const ComType com, const SetPulseWidth *data);
void get_pulse_width(const ComType com, const GetPulseWidth *data);
void set_degree(const ComType com, const SetDegree *data);
void get_degree(const ComType com, const GetDegree *data);
void set_period(const ComType com, const SetPeriod *data);
void get_period(const ComType com, const GetPeriod *data);
void get_servo_current(const ComType com, const GetServoCurrent *data);
void get_overall_current(const ComType com, const GetOverallCurrent *data);
void get_stack_input_voltage(const ComType com, const GetStackInputVoltage *data);
void get_external_input_voltage(const ComType com, const GetExternalInputVoltage *data);
void set_minimum_voltage(const ComType com, const SetMinimumVoltage *data);
void get_minimum_voltage(const ComType com, const GetMinimumVoltage *data);
void enable_velocity_reached_callback(const ComType com, const EnableVelocityReachedCallback *data);
void disable_velocity_reached_callback(const ComType com, const DisableVelocityReachedCallback *data);
void is_velocity_reached_callback_enabled(const ComType com, const IsVelocityReachedCallbackEnabled *data);
void enable_position_reached_callback(const ComType com, const EnablePositionReachedCallback *data);
void disable_position_reached_callback(const ComType com, const DisablePositionReachedCallback *data);
void is_position_reached_callback_enabled(const ComType com, const IsPositionReachedCallbackEnabled *data);

#endif
