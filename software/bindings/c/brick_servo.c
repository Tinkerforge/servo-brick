/*************************************************************
 * This file was automatically generated on 2011-08-23.      *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#include "brick_servo.h"

#include <string.h>

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

typedef void (*under_voltage_func_t)(uint16_t);
typedef void (*position_reached_func_t)(uint8_t, int16_t);
typedef void (*velocity_reached_func_t)(uint8_t, int16_t);

#ifdef _MSC_VER
	#pragma pack(push)
	#pragma pack(1)

	#define PACKED
#else
	#define PACKED __attribute__((packed))
#endif

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo_num;
} PACKED Enable;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo_num;
} PACKED Disable;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo_num;
} PACKED IsEnabled;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	bool enabled;
} PACKED IsEnabledReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo_num;
	int16_t position;
} PACKED SetPosition;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo_num;
} PACKED GetPosition;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	int16_t position;
} PACKED GetPositionReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo_num;
} PACKED GetCurrentPosition;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	int16_t position;
} PACKED GetCurrentPositionReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo_num;
	uint16_t velocity;
} PACKED SetVelocity;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo_num;
} PACKED GetVelocity;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t velocity;
} PACKED GetVelocityReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo_num;
} PACKED GetCurrentVelocity;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t velocity;
} PACKED GetCurrentVelocityReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo_num;
	uint16_t acceleration;
} PACKED SetAcceleration;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo_num;
} PACKED GetAcceleration;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t acceleration;
} PACKED GetAccelerationReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} PACKED SetOutputVoltage;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetOutputVoltage;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} PACKED GetOutputVoltageReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo_num;
	uint16_t min;
	uint16_t max;
} PACKED SetPulseWidth;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo_num;
} PACKED GetPulseWidth;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t min;
	uint16_t max;
} PACKED GetPulseWidthReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo_num;
	int16_t min;
	int16_t max;
} PACKED SetDegree;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo_num;
} PACKED GetDegree;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	int16_t min;
	int16_t max;
} PACKED GetDegreeReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo_num;
	uint16_t period;
} PACKED SetPeriod;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo_num;
} PACKED GetPeriod;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t period;
} PACKED GetPeriodReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo_num;
} PACKED GetServoCurrent;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t current;
} PACKED GetServoCurrentReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetOverallCurrent;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t current;
} PACKED GetOverallCurrentReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetStackInputVoltage;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} PACKED GetStackInputVoltageReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetExternalInputVoltage;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} PACKED GetExternalInputVoltageReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} PACKED SetMinimumVoltage;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetMinimumVoltage;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} PACKED GetMinimumVoltageReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} PACKED UnderVoltageCallback;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo_num;
	int16_t position;
} PACKED PositionReachedCallback;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t servo_num;
	int16_t velocity;
} PACKED VelocityReachedCallback;

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

int servo_enable(Servo *servo, uint8_t servo_num) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	Enable e;
	e.stack_id = servo->stack_id;
	e.type = TYPE_ENABLE;
	e.length = sizeof(Enable);
	e.servo_num = servo_num;

	ipcon_device_write(servo, (char *)&e, sizeof(Enable));

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_disable(Servo *servo, uint8_t servo_num) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	Disable d;
	d.stack_id = servo->stack_id;
	d.type = TYPE_DISABLE;
	d.length = sizeof(Disable);
	d.servo_num = servo_num;

	ipcon_device_write(servo, (char *)&d, sizeof(Disable));

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_is_enabled(Servo *servo, uint8_t servo_num, bool *ret_enabled) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	servo->answer.type = TYPE_IS_ENABLED;
	servo->answer.length = sizeof(IsEnabledReturn);
	IsEnabled ie;
	ie.stack_id = servo->stack_id;
	ie.type = TYPE_IS_ENABLED;
	ie.length = sizeof(IsEnabled);
	ie.servo_num = servo_num;

	ipcon_device_write(servo, (char *)&ie, sizeof(IsEnabled));

	if(ipcon_answer_sem_wait_timeout(servo) != 0) {
		ipcon_sem_post_write(servo);
		return E_TIMEOUT;
	}

	IsEnabledReturn *ier = (IsEnabledReturn *)servo->answer.buffer;
	*ret_enabled = ier->enabled;

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_set_position(Servo *servo, uint8_t servo_num, int16_t position) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	SetPosition sp;
	sp.stack_id = servo->stack_id;
	sp.type = TYPE_SET_POSITION;
	sp.length = sizeof(SetPosition);
	sp.servo_num = servo_num;
	sp.position = position;

	ipcon_device_write(servo, (char *)&sp, sizeof(SetPosition));

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_get_position(Servo *servo, uint8_t servo_num, int16_t *ret_position) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	servo->answer.type = TYPE_GET_POSITION;
	servo->answer.length = sizeof(GetPositionReturn);
	GetPosition gp;
	gp.stack_id = servo->stack_id;
	gp.type = TYPE_GET_POSITION;
	gp.length = sizeof(GetPosition);
	gp.servo_num = servo_num;

	ipcon_device_write(servo, (char *)&gp, sizeof(GetPosition));

	if(ipcon_answer_sem_wait_timeout(servo) != 0) {
		ipcon_sem_post_write(servo);
		return E_TIMEOUT;
	}

	GetPositionReturn *gpr = (GetPositionReturn *)servo->answer.buffer;
	*ret_position = gpr->position;

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_get_current_position(Servo *servo, uint8_t servo_num, int16_t *ret_position) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	servo->answer.type = TYPE_GET_CURRENT_POSITION;
	servo->answer.length = sizeof(GetCurrentPositionReturn);
	GetCurrentPosition gcp;
	gcp.stack_id = servo->stack_id;
	gcp.type = TYPE_GET_CURRENT_POSITION;
	gcp.length = sizeof(GetCurrentPosition);
	gcp.servo_num = servo_num;

	ipcon_device_write(servo, (char *)&gcp, sizeof(GetCurrentPosition));

	if(ipcon_answer_sem_wait_timeout(servo) != 0) {
		ipcon_sem_post_write(servo);
		return E_TIMEOUT;
	}

	GetCurrentPositionReturn *gcpr = (GetCurrentPositionReturn *)servo->answer.buffer;
	*ret_position = gcpr->position;

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_set_velocity(Servo *servo, uint8_t servo_num, uint16_t velocity) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	SetVelocity sv;
	sv.stack_id = servo->stack_id;
	sv.type = TYPE_SET_VELOCITY;
	sv.length = sizeof(SetVelocity);
	sv.servo_num = servo_num;
	sv.velocity = velocity;

	ipcon_device_write(servo, (char *)&sv, sizeof(SetVelocity));

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_get_velocity(Servo *servo, uint8_t servo_num, uint16_t *ret_velocity) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	servo->answer.type = TYPE_GET_VELOCITY;
	servo->answer.length = sizeof(GetVelocityReturn);
	GetVelocity gv;
	gv.stack_id = servo->stack_id;
	gv.type = TYPE_GET_VELOCITY;
	gv.length = sizeof(GetVelocity);
	gv.servo_num = servo_num;

	ipcon_device_write(servo, (char *)&gv, sizeof(GetVelocity));

	if(ipcon_answer_sem_wait_timeout(servo) != 0) {
		ipcon_sem_post_write(servo);
		return E_TIMEOUT;
	}

	GetVelocityReturn *gvr = (GetVelocityReturn *)servo->answer.buffer;
	*ret_velocity = gvr->velocity;

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_get_current_velocity(Servo *servo, uint8_t servo_num, uint16_t *ret_velocity) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	servo->answer.type = TYPE_GET_CURRENT_VELOCITY;
	servo->answer.length = sizeof(GetCurrentVelocityReturn);
	GetCurrentVelocity gcv;
	gcv.stack_id = servo->stack_id;
	gcv.type = TYPE_GET_CURRENT_VELOCITY;
	gcv.length = sizeof(GetCurrentVelocity);
	gcv.servo_num = servo_num;

	ipcon_device_write(servo, (char *)&gcv, sizeof(GetCurrentVelocity));

	if(ipcon_answer_sem_wait_timeout(servo) != 0) {
		ipcon_sem_post_write(servo);
		return E_TIMEOUT;
	}

	GetCurrentVelocityReturn *gcvr = (GetCurrentVelocityReturn *)servo->answer.buffer;
	*ret_velocity = gcvr->velocity;

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_set_acceleration(Servo *servo, uint8_t servo_num, uint16_t acceleration) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	SetAcceleration sa;
	sa.stack_id = servo->stack_id;
	sa.type = TYPE_SET_ACCELERATION;
	sa.length = sizeof(SetAcceleration);
	sa.servo_num = servo_num;
	sa.acceleration = acceleration;

	ipcon_device_write(servo, (char *)&sa, sizeof(SetAcceleration));

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_get_acceleration(Servo *servo, uint8_t servo_num, uint16_t *ret_acceleration) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	servo->answer.type = TYPE_GET_ACCELERATION;
	servo->answer.length = sizeof(GetAccelerationReturn);
	GetAcceleration ga;
	ga.stack_id = servo->stack_id;
	ga.type = TYPE_GET_ACCELERATION;
	ga.length = sizeof(GetAcceleration);
	ga.servo_num = servo_num;

	ipcon_device_write(servo, (char *)&ga, sizeof(GetAcceleration));

	if(ipcon_answer_sem_wait_timeout(servo) != 0) {
		ipcon_sem_post_write(servo);
		return E_TIMEOUT;
	}

	GetAccelerationReturn *gar = (GetAccelerationReturn *)servo->answer.buffer;
	*ret_acceleration = gar->acceleration;

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_set_output_voltage(Servo *servo, uint16_t voltage) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	SetOutputVoltage sov;
	sov.stack_id = servo->stack_id;
	sov.type = TYPE_SET_OUTPUT_VOLTAGE;
	sov.length = sizeof(SetOutputVoltage);
	sov.voltage = voltage;

	ipcon_device_write(servo, (char *)&sov, sizeof(SetOutputVoltage));

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_get_output_voltage(Servo *servo, uint16_t *ret_voltage) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	servo->answer.type = TYPE_GET_OUTPUT_VOLTAGE;
	servo->answer.length = sizeof(GetOutputVoltageReturn);
	GetOutputVoltage gov;
	gov.stack_id = servo->stack_id;
	gov.type = TYPE_GET_OUTPUT_VOLTAGE;
	gov.length = sizeof(GetOutputVoltage);

	ipcon_device_write(servo, (char *)&gov, sizeof(GetOutputVoltage));

	if(ipcon_answer_sem_wait_timeout(servo) != 0) {
		ipcon_sem_post_write(servo);
		return E_TIMEOUT;
	}

	GetOutputVoltageReturn *govr = (GetOutputVoltageReturn *)servo->answer.buffer;
	*ret_voltage = govr->voltage;

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_set_pulse_width(Servo *servo, uint8_t servo_num, uint16_t min, uint16_t max) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	SetPulseWidth spw;
	spw.stack_id = servo->stack_id;
	spw.type = TYPE_SET_PULSE_WIDTH;
	spw.length = sizeof(SetPulseWidth);
	spw.servo_num = servo_num;
	spw.min = min;
	spw.max = max;

	ipcon_device_write(servo, (char *)&spw, sizeof(SetPulseWidth));

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_get_pulse_width(Servo *servo, uint8_t servo_num, uint16_t *ret_min, uint16_t *ret_max) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	servo->answer.type = TYPE_GET_PULSE_WIDTH;
	servo->answer.length = sizeof(GetPulseWidthReturn);
	GetPulseWidth gpw;
	gpw.stack_id = servo->stack_id;
	gpw.type = TYPE_GET_PULSE_WIDTH;
	gpw.length = sizeof(GetPulseWidth);
	gpw.servo_num = servo_num;

	ipcon_device_write(servo, (char *)&gpw, sizeof(GetPulseWidth));

	if(ipcon_answer_sem_wait_timeout(servo) != 0) {
		ipcon_sem_post_write(servo);
		return E_TIMEOUT;
	}

	GetPulseWidthReturn *gpwr = (GetPulseWidthReturn *)servo->answer.buffer;
	*ret_min = gpwr->min;
	*ret_max = gpwr->max;

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_set_degree(Servo *servo, uint8_t servo_num, int16_t min, int16_t max) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	SetDegree sd;
	sd.stack_id = servo->stack_id;
	sd.type = TYPE_SET_DEGREE;
	sd.length = sizeof(SetDegree);
	sd.servo_num = servo_num;
	sd.min = min;
	sd.max = max;

	ipcon_device_write(servo, (char *)&sd, sizeof(SetDegree));

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_get_degree(Servo *servo, uint8_t servo_num, int16_t *ret_min, int16_t *ret_max) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	servo->answer.type = TYPE_GET_DEGREE;
	servo->answer.length = sizeof(GetDegreeReturn);
	GetDegree gd;
	gd.stack_id = servo->stack_id;
	gd.type = TYPE_GET_DEGREE;
	gd.length = sizeof(GetDegree);
	gd.servo_num = servo_num;

	ipcon_device_write(servo, (char *)&gd, sizeof(GetDegree));

	if(ipcon_answer_sem_wait_timeout(servo) != 0) {
		ipcon_sem_post_write(servo);
		return E_TIMEOUT;
	}

	GetDegreeReturn *gdr = (GetDegreeReturn *)servo->answer.buffer;
	*ret_min = gdr->min;
	*ret_max = gdr->max;

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_set_period(Servo *servo, uint8_t servo_num, uint16_t period) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	SetPeriod sp;
	sp.stack_id = servo->stack_id;
	sp.type = TYPE_SET_PERIOD;
	sp.length = sizeof(SetPeriod);
	sp.servo_num = servo_num;
	sp.period = period;

	ipcon_device_write(servo, (char *)&sp, sizeof(SetPeriod));

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_get_period(Servo *servo, uint8_t servo_num, uint16_t *ret_period) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	servo->answer.type = TYPE_GET_PERIOD;
	servo->answer.length = sizeof(GetPeriodReturn);
	GetPeriod gp;
	gp.stack_id = servo->stack_id;
	gp.type = TYPE_GET_PERIOD;
	gp.length = sizeof(GetPeriod);
	gp.servo_num = servo_num;

	ipcon_device_write(servo, (char *)&gp, sizeof(GetPeriod));

	if(ipcon_answer_sem_wait_timeout(servo) != 0) {
		ipcon_sem_post_write(servo);
		return E_TIMEOUT;
	}

	GetPeriodReturn *gpr = (GetPeriodReturn *)servo->answer.buffer;
	*ret_period = gpr->period;

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_get_servo_current(Servo *servo, uint8_t servo_num, uint16_t *ret_current) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	servo->answer.type = TYPE_GET_SERVO_CURRENT;
	servo->answer.length = sizeof(GetServoCurrentReturn);
	GetServoCurrent gsc;
	gsc.stack_id = servo->stack_id;
	gsc.type = TYPE_GET_SERVO_CURRENT;
	gsc.length = sizeof(GetServoCurrent);
	gsc.servo_num = servo_num;

	ipcon_device_write(servo, (char *)&gsc, sizeof(GetServoCurrent));

	if(ipcon_answer_sem_wait_timeout(servo) != 0) {
		ipcon_sem_post_write(servo);
		return E_TIMEOUT;
	}

	GetServoCurrentReturn *gscr = (GetServoCurrentReturn *)servo->answer.buffer;
	*ret_current = gscr->current;

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_get_overall_current(Servo *servo, uint16_t *ret_current) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	servo->answer.type = TYPE_GET_OVERALL_CURRENT;
	servo->answer.length = sizeof(GetOverallCurrentReturn);
	GetOverallCurrent goc;
	goc.stack_id = servo->stack_id;
	goc.type = TYPE_GET_OVERALL_CURRENT;
	goc.length = sizeof(GetOverallCurrent);

	ipcon_device_write(servo, (char *)&goc, sizeof(GetOverallCurrent));

	if(ipcon_answer_sem_wait_timeout(servo) != 0) {
		ipcon_sem_post_write(servo);
		return E_TIMEOUT;
	}

	GetOverallCurrentReturn *gocr = (GetOverallCurrentReturn *)servo->answer.buffer;
	*ret_current = gocr->current;

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_get_stack_input_voltage(Servo *servo, uint16_t *ret_voltage) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	servo->answer.type = TYPE_GET_STACK_INPUT_VOLTAGE;
	servo->answer.length = sizeof(GetStackInputVoltageReturn);
	GetStackInputVoltage gsiv;
	gsiv.stack_id = servo->stack_id;
	gsiv.type = TYPE_GET_STACK_INPUT_VOLTAGE;
	gsiv.length = sizeof(GetStackInputVoltage);

	ipcon_device_write(servo, (char *)&gsiv, sizeof(GetStackInputVoltage));

	if(ipcon_answer_sem_wait_timeout(servo) != 0) {
		ipcon_sem_post_write(servo);
		return E_TIMEOUT;
	}

	GetStackInputVoltageReturn *gsivr = (GetStackInputVoltageReturn *)servo->answer.buffer;
	*ret_voltage = gsivr->voltage;

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_get_external_input_voltage(Servo *servo, uint16_t *ret_voltage) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	servo->answer.type = TYPE_GET_EXTERNAL_INPUT_VOLTAGE;
	servo->answer.length = sizeof(GetExternalInputVoltageReturn);
	GetExternalInputVoltage geiv;
	geiv.stack_id = servo->stack_id;
	geiv.type = TYPE_GET_EXTERNAL_INPUT_VOLTAGE;
	geiv.length = sizeof(GetExternalInputVoltage);

	ipcon_device_write(servo, (char *)&geiv, sizeof(GetExternalInputVoltage));

	if(ipcon_answer_sem_wait_timeout(servo) != 0) {
		ipcon_sem_post_write(servo);
		return E_TIMEOUT;
	}

	GetExternalInputVoltageReturn *geivr = (GetExternalInputVoltageReturn *)servo->answer.buffer;
	*ret_voltage = geivr->voltage;

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_set_minimum_voltage(Servo *servo, uint16_t voltage) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	SetMinimumVoltage smv;
	smv.stack_id = servo->stack_id;
	smv.type = TYPE_SET_MINIMUM_VOLTAGE;
	smv.length = sizeof(SetMinimumVoltage);
	smv.voltage = voltage;

	ipcon_device_write(servo, (char *)&smv, sizeof(SetMinimumVoltage));

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_get_minimum_voltage(Servo *servo, uint16_t *ret_voltage) {
	if(servo->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(servo);

	servo->answer.type = TYPE_GET_MINIMUM_VOLTAGE;
	servo->answer.length = sizeof(GetMinimumVoltageReturn);
	GetMinimumVoltage gmv;
	gmv.stack_id = servo->stack_id;
	gmv.type = TYPE_GET_MINIMUM_VOLTAGE;
	gmv.length = sizeof(GetMinimumVoltage);

	ipcon_device_write(servo, (char *)&gmv, sizeof(GetMinimumVoltage));

	if(ipcon_answer_sem_wait_timeout(servo) != 0) {
		ipcon_sem_post_write(servo);
		return E_TIMEOUT;
	}

	GetMinimumVoltageReturn *gmvr = (GetMinimumVoltageReturn *)servo->answer.buffer;
	*ret_voltage = gmvr->voltage;

	ipcon_sem_post_write(servo);

	return E_OK;
}

int servo_callback_under_voltage(Servo *servo, const unsigned char *buffer) {
	UnderVoltageCallback *uvc = (UnderVoltageCallback *)buffer;
	((under_voltage_func_t)servo->callbacks[uvc->type])(uvc->voltage);
	return sizeof(UnderVoltageCallback);
}

int servo_callback_position_reached(Servo *servo, const unsigned char *buffer) {
	PositionReachedCallback *prc = (PositionReachedCallback *)buffer;
	((position_reached_func_t)servo->callbacks[prc->type])(prc->servo_num, prc->position);
	return sizeof(PositionReachedCallback);
}

int servo_callback_velocity_reached(Servo *servo, const unsigned char *buffer) {
	VelocityReachedCallback *vrc = (VelocityReachedCallback *)buffer;
	((velocity_reached_func_t)servo->callbacks[vrc->type])(vrc->servo_num, vrc->velocity);
	return sizeof(VelocityReachedCallback);
}

void servo_register_callback(Servo *servo, uint8_t cb, void *func) {
    servo->callbacks[cb] = func;
}

void servo_create(Servo *servo, const char *uid) {
	ipcon_device_create(servo, uid);

	servo->device_callbacks[TYPE_UNDER_VOLTAGE] = servo_callback_under_voltage;
	servo->device_callbacks[TYPE_POSITION_REACHED] = servo_callback_position_reached;
	servo->device_callbacks[TYPE_VELOCITY_REACHED] = servo_callback_velocity_reached;
}
