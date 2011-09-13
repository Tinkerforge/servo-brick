/* servo-brick
 * Copyright (C) 2011 Olaf Lüke <olaf@tinkerforge.com>
 *
 * mcp3008.c: Functions for reading values from mcp3008
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

#include "mcp3008.h"

#include "bricklib/drivers/pio/pio.h"
#include "bricklib/drivers/usart/usart.h"
#include "servo.h"

#include <stdio.h>

#include "config.h"

typedef enum {
	MCP3008_FIRST_BYTE = 0,
	MCP3008_SECOND_BYTE = 1
} MCP3008State;

static uint8_t mcp3008_state = MCP3008_FIRST_BYTE;

uint32_t servo_current_counter = 0;
uint32_t servo_current_sum[SERVO_NUM] = {0};

void mcp3008_init() {
	Pin usart_spi_pins[] = {PINS_USART_SPI};
	PIO_Configure(usart_spi_pins, PIO_LISTSIZE(usart_spi_pins));

    // Enable peripheral clock
    PMC->PMC_PCER0 = 1 << ID_USART0;

    // Configure the USART0 as SPI (with data lenght of 9 bit)
    USART_Configure(USART0,
                    US_MR_USART_MODE_SPI_MASTER |
                    US_MR_USCLKS_MCK            |
                    US_MR_CHRL_8_BIT            |
                    US_MR_PAR_NO                |
                    US_MR_CHMODE_NORMAL         |
                    US_MR_CLKO                  |
                    US_MR_MODE9                 |
                    US_SPI_CPOL_0               |
                    US_SPI_CPHA_1,
                    USART_SPI_CLK,
                    BOARD_MCK);

    // Enable receiver and transmitter
    USART0->US_CR = US_CR_TXEN;
    USART0->US_CR = US_CR_RXEN;

    NVIC_DisableIRQ(USART0_IRQn);
    NVIC_ClearPendingIRQ(USART0_IRQn);
    NVIC_SetPriority(USART0_IRQn, PRIORITY_MCP3008_USART0);
    NVIC_EnableIRQ(USART0_IRQn);

    USART0->US_IER = US_IER_TXEMPTY;
}
void USART0_IrqHandler(void) {
	static uint16_t value = 0;
	static uint8_t pos = 0;

	if(mcp3008_state == MCP3008_FIRST_BYTE) {
		value |= MCP3008_END_POS(USART0->US_RHR);
		mcp3008_deselect();

		servo_current_sum[6-pos] += value;

		pos = (pos + 1) % SERVO_NUM;
		if(pos == 0) {
			servo_current_counter++;
		}

		for(int i = 0; i < 100; i++) {
			__NOP();
		}

		mcp3008_select();
		USART0->US_THR = MCP3008_START(pos+1);
		mcp3008_state = MCP3008_SECOND_BYTE;
	} else if(mcp3008_state == MCP3008_SECOND_BYTE){
		value = MCP3008_START_POS(USART0->US_RHR & MCP3008_START_MASK) ;
		USART0->US_THR = MCP3008_END;
		mcp3008_state = MCP3008_FIRST_BYTE;
	}
}

// Transfer and Receive 9 bit to/from MCP3008
inline uint16_t mcp3008_transceive(uint16_t value) {
	// Wait for transfer buffer to be empty
	while((USART0->US_CSR & US_CSR_TXEMPTY) == 0);
	USART0->US_THR = value;

	// Wait until receive buffer has new data
	while((USART0->US_CSR & US_CSR_RXRDY) == 0);
	return USART0->US_RHR;
}

// Get AD value from ACP3008, use 9 bit mode for most efficient transfer
// rate (only 1 bit at the end of the communication is wasted)
uint16_t mcp3008_get_value(uint8_t pos) {
	mcp3008_select();

	uint16_t value;

	// Send start bit, single ended bit and pin to measure (p)
	// Receive 0 bit and first 2 data bits (d)
	// send: 0b11ppp0000, recv: 0bXXXXXX0dd
	value = MCP3008_START_POS(mcp3008_transceive(MCP3008_START(pos)) &
	                          MCP3008_START_MASK);

	// Send Zeros and receive last 8 bits of data
	value |= MCP3008_END_POS(mcp3008_transceive(MCP3008_END));

    mcp3008_deselect();

    return value;
}
