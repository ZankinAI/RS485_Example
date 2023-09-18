/*
 * rs_protocol.c
 *
 *  Created on: Sep 16, 2023
 *      Author: zankin
 */

#include "rs_protocol.h"



uint8_t  rsTxBuf[MAX_RS_TX_LENGHT];
uint16_t rsTxBufferPos = 0;


void rsCreatePoolingMessage(uint8_t** message, uint16_t* lenght, uint8_t idDevice)
{
	uint16_t crc16 = 0xFFFF;
	rsTxBufferPos = 0;

	rsTxBuf[rsTxBufferPos++] = 0xAA;
	rsTxBuf[rsTxBufferPos++] = 0xAA;
	rsTxBuf[rsTxBufferPos++] = idDevice;
	rsTxBuf[rsTxBufferPos++] = RS_CMD_POLLING;

	crc16 = rsCRC16_ccitt(&rsTxBuf[2], 2);

	rsTxBuf[rsTxBufferPos++] = crc16 & 0xFF;
	rsTxBuf[rsTxBufferPos++] = crc16 >> 8;

	*message = (uint8_t * ) &rsTxBuf[0];
	*lenght = rsTxBufferPos;
}

void rsCreateSwitchMessage(uint8_t** message, uint16_t* lenght, uint8_t idDevice, uint8_t switchDevice)
{
	uint16_t crc16 = 0xFFFF;

	rsTxBufferPos = 0;

	rsTxBuf[rsTxBufferPos++] = 0xAA;
	rsTxBuf[rsTxBufferPos++] = 0xAA;
	rsTxBuf[rsTxBufferPos++] = idDevice;
	rsTxBuf[rsTxBufferPos++] = RS_CMD_SWITCHING;
	rsTxBuf[rsTxBufferPos++] = switchDevice;

	crc16 = rsCRC16_ccitt(&rsTxBuf[2], 3);

	rsTxBuf[rsTxBufferPos++] = crc16 >> 8;
	rsTxBuf[rsTxBufferPos++] = crc16 & 0xFF;

	*message = (uint8_t * ) &rsTxBuf[0];
	*lenght = rsTxBufferPos;
}


uint16_t rsCRC16_ccitt(volatile uint8_t * buf, uint16_t bufLenght)
{
	uint16_t crc16 = 0xFFFF;
	uint8_t i;

	while (bufLenght--)
	{
		crc16 ^= *buf++ << 8;
		for (i = 0; i < 8; i++)
			crc16 = crc16 & 0x8000 ? (crc16 << 1) ^ 0x1021 : crc16 << 1;
	}
	return crc16;
}


float getAmperage(uint8_t* message)
{
	uint32_t temp;
	float * floatTemp;
	float amperage = 0.0f;

	temp = *(message + AMPERAGE_START_POS)|(*(message + AMPERAGE_START_POS + 1) << 8)|
			(*(message + AMPERAGE_START_POS + 2) << 16)|(*(message + AMPERAGE_START_POS + 3) << 24);

	floatTemp = &temp;
	amperage = *floatTemp;

	return amperage;
}

float getVoltage(uint8_t* message)
{
	uint32_t temp;

	float * floatTemp;
	float voltage = 0.0f;

	temp = *(message + VOLTAGE_START_POS)|(*(message + VOLTAGE_START_POS + 1) << 8)|
			(*(message + VOLTAGE_START_POS + 2) << 16)|(*(message + VOLTAGE_START_POS + 3) << 24);

	floatTemp = &temp;
	voltage = *floatTemp;

	return voltage;
}

rsCommands getCommandId(uint8_t* message)
{
	return *(message + COOMMAND_POS);
}

uint8_t getDeviceId(uint8_t* message)
{
	return *(message + DEVICE_ID_POS);
}
