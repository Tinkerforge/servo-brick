/*************************************************************
 * This file was automatically generated on 23.08.2011.      *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICK_SERVO_H
#define BRICK_SERVO_H

#include "ip_connection.h"

typedef Device Servo;

#define SERVO_CALLBACK_UNDER_VOLTAGE 26
#define SERVO_CALLBACK_POSITION_REACHED 27
#define SERVO_CALLBACK_VELOCITY_REACHED 28

void servo_create(Servo *servo, const char *uid);

int servo_enable(Servo *servo, uint8_t servo_num);
int servo_disable(Servo *servo, uint8_t servo_num);
int servo_is_enabled(Servo *servo, uint8_t servo_num, bool *ret_enabled);
int servo_set_position(Servo *servo, uint8_t servo_num, int16_t position);
int servo_get_position(Servo *servo, uint8_t servo_num, int16_t *ret_position);
int servo_get_current_position(Servo *servo, uint8_t servo_num, int16_t *ret_position);
int servo_set_velocity(Servo *servo, uint8_t servo_num, uint16_t velocity);
int servo_get_velocity(Servo *servo, uint8_t servo_num, uint16_t *ret_velocity);
int servo_get_current_velocity(Servo *servo, uint8_t servo_num, uint16_t *ret_velocity);
int servo_set_acceleration(Servo *servo, uint8_t servo_num, uint16_t acceleration);
int servo_get_acceleration(Servo *servo, uint8_t servo_num, uint16_t *ret_acceleration);
int servo_set_output_voltage(Servo *servo, uint16_t voltage);
int servo_get_output_voltage(Servo *servo, uint16_t *ret_voltage);
int servo_set_pulse_width(Servo *servo, uint8_t servo_num, uint16_t min, uint16_t max);
int servo_get_pulse_width(Servo *servo, uint8_t servo_num, uint16_t *ret_min, uint16_t *ret_max);
int servo_set_degree(Servo *servo, uint8_t servo_num, int16_t min, int16_t max);
int servo_get_degree(Servo *servo, uint8_t servo_num, int16_t *ret_min, int16_t *ret_max);
int servo_set_period(Servo *servo, uint8_t servo_num, uint16_t period);
int servo_get_period(Servo *servo, uint8_t servo_num, uint16_t *ret_period);
int servo_get_servo_current(Servo *servo, uint8_t servo_num, uint16_t *ret_current);
int servo_get_overall_current(Servo *servo, uint16_t *ret_current);
int servo_get_stack_input_voltage(Servo *servo, uint16_t *ret_voltage);
int servo_get_external_input_voltage(Servo *servo, uint16_t *ret_voltage);
int servo_set_minimum_voltage(Servo *servo, uint16_t voltage);
int servo_get_minimum_voltage(Servo *servo, uint16_t *ret_voltage);
int servo_under_voltage(Servo *servo, uint16_t *ret_voltage);
int servo_position_reached(Servo *servo, uint8_t *ret_servo_num, int16_t *ret_position);
int servo_velocity_reached(Servo *servo, uint8_t *ret_servo_num, int16_t *ret_velocity);

void servo_register_callback(Servo *servo, uint8_t cb, void *func);

#endif