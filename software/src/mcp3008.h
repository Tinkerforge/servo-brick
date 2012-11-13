/* servo-brick
 * Copyright (C) 2011-2012 Olaf Lüke <olaf@tinkerforge.com>
 *
 * mcp3008.h: Functions for reading values from mcp3008
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

#ifndef MCP3008_H
#define MCP3008_H

#include <stdint.h>

#define MCP3008_START_BIT          (1 << 8)
#define MCP3008_SINGLE_ENDED       0x80
#define MCP3008_SERVO_POS(servo)   ((servo) << 4)
#define MCP3008_START_MASK         ((1<<0) | (1<<1))

#define MCP3008_START_POS(value)   ((value) << 8)
#define MCP3008_END_POS(value)     ((value) >> 1)

#define MCP3008_START(servo)       (MCP3008_SINGLE_ENDED | \
	                                MCP3008_START_BIT    | \
	                                MCP3008_SERVO_POS((servo)))
#define MCP3008_END                0

#define mcp3008_select()           USART0->US_CR = US_CR_FCS
#define mcp3008_deselect()         USART0->US_CR = US_CR_RCS

void mcp3008_init();
uint16_t mcp3008_get_value(const uint8_t servo);
uint16_t mcp3008_transceive(const uint16_t value);


#endif
