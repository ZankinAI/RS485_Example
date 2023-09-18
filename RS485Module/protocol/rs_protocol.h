/*
 * rs_protocol.h
 *
 *  Created on: Sep 16, 2023
 *      Author: zankin
 */

#ifndef PROTOCOL_RS_PROTOCOL_H_
#define PROTOCOL_RS_PROTOCOL_H_

#include <inttypes.h>
#include "main.h"

#define MAX_RS_TX_LENGHT 7
#define MAX_RS_RX_LENGHT 14

#define MIN_RS_TX_LENGHT 6
#define MIN_RS_RX_LENGHT 6

#define PREAMBLE_BYTES 2
#define CRC16_BYTES 2

#define AMPERAGE_START_POS 8
#define VOLTAGE_START_POS 4

#define COOMMAND_POS 3
#define DEVICE_ID_POS 2

typedef enum{
	RS_CMD_POLLING = 1,
	RS_CMD_SWITCHING
} rsCommands;

typedef enum{
	SWITCH_OFF,
	SWITCH_ON
} switch_t;

uint16_t rsCRC16_ccitt(volatile uint8_t * buf, uint16_t bufLenght);
void rsCreatePoolingMessage(uint8_t** message, uint16_t* lenght, uint8_t idDevice);
void rsCreateSwitchMessage(uint8_t** message, uint16_t* lenght, uint8_t idDevice, uint8_t switchDevice);
float getAmperage(uint8_t* message);
float getVoltage(uint8_t* message);
rsCommands getCommandId(uint8_t* message);
uint8_t getDeviceId(uint8_t* message);


#endif /* PROTOCOL_RS_PROTOCOL_H_ */
