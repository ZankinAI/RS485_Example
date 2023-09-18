/*
 * rs.c
 *
 *  Created on: Sep 17, 2023
 *      Author: zankin
 */

#include "rs.h"

static uint8_t * rsTxMessage;
static uint8_t * rsRxMessage;

static uint16_t  rsTxMessageLenght;
static uint16_t  rsRxMessageLenght;

rsMasterState rsMasterCurrentState;
uint8_t stte = 0;

uint8_t curDevice = 0;
uint32_t receivedCount = 0;
uint32_t errorCount = 0;

Device_t devices[DEVICE_COUNT];

void rs_loop()
{
	rsMasterCurrentState = getRsMasterState();
	switch (rsMasterCurrentState)
	{
	case STATE_IDLE:

		break;

	case STATE_START_POLLING:
		curDevice = 0;
		sendPoolingMessageToDevice(devices[curDevice].deviceId);

		break;

	case STATE_WAIT_ANSWER:

		break;

	case STATE_RECEIVE_ANSWER:

		parseMessage(); //Разбор сообщения

		if (curDevice < DEVICE_COUNT)
		{
			sendPoolingMessageToDevice(devices[curDevice].deviceId);
		}
		else
			setRsMasterState(STATE_IDLE);
		break;

	case STATE_RECEIVE_ERROR:

		devices[curDevice].deviceConnectionState = DISCONNECTED;
		curDevice++;
		if (curDevice < DEVICE_COUNT)
		{
			sendPoolingMessageToDevice(devices[curDevice].deviceId);
		}
		else
			setRsMasterState(STATE_IDLE);
		break;
	}

}

void parseMessage()
{

	// Если сообщение не содержит ошибок, начинается разбор
	if (rsReceiveMessage (&rsRxMessage, &rsRxMessageLenght) == RS_NOERROR)
	{
		devices[curDevice].deviceConnectionState = CONNECTED;

		if (getCommandId(rsRxMessage) == RS_CMD_POLLING)
		{
			devices[curDevice].amperage = getAmperage(rsRxMessage);
			devices[curDevice].voltage = getVoltage(rsRxMessage);

			if ((devices[curDevice].amperage > CRITICAL_AMPERAGE)
					&& 	(devices[curDevice].deviceState == WORK))
			{
				sendSwitchMessageToDevice(devices[curDevice].deviceId, SWITCH_OFF);
			}
			else
			{
				curDevice++;
			}
		}
		else
		{
			devices[curDevice].deviceState = NOT_WORK;
			curDevice++;
		}
	}
	else
	{
		devices[curDevice].deviceConnectionState = DISCONNECTED;
		setRsMasterState(STATE_RECEIVE_ERROR);
		curDevice++;
	}
}

void devicesInit()
{
	for (int i = 0; i < DEVICE_COUNT; i++)
	{
		initDevice(&devices[i], i + 1);
	}
}

void sendPoolingMessageToDevice(uint8_t deviceId)
{
	rsCreatePoolingMessage(&rsTxMessage, &rsTxMessageLenght, deviceId);
	rsSendMessage(rsTxMessage, rsTxMessageLenght);
}

void sendSwitchMessageToDevice(uint8_t deviceId, switch_t switchMode)
{
	rsCreateSwitchMessage(&rsTxMessage, &rsTxMessageLenght, deviceId, switchMode);
	rsSendMessage(rsTxMessage, rsTxMessageLenght);
}
