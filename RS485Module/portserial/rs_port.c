/*
 * rs_port.c
 *
 *  Created on: 16 сент. 2023 г.
 *      Author: zankin
 */

#include "port.h"
#include "rs_protocol.h"

static volatile uint8_t  rsRxBuf[MAX_RS_RX_LENGHT];
static volatile uint16_t rsRcvBufferPos;

static volatile rsRxState rsRcvState;						//состояние приемника UART
static volatile rsMasterState rsMstrState = STATE_IDLE;



rsMasterState getRsMasterState()
{
	return rsMstrState;
}

void setRsMasterState(rsMasterState state)
{
	rsMstrState = state;
}

void rsByteReceived()
{
	uint8_t receivedByte = 0x00;

	portSerialGetByte(&receivedByte);

	switch (rsRcvState)
	{
	case STATE_RX_IDLE:
		rsRcvBufferPos = 0;
		rsRxBuf[rsRcvBufferPos++] = receivedByte;
		rsRcvState = STATE_RX_RCV;

		rsTimerInit(100);
		rsTimerEnable();

		break;

	case STATE_RX_RCV:

		if (rsRcvBufferPos < MAX_RS_RX_LENGHT)
		{
			rsRxBuf[rsRcvBufferPos++] = receivedByte;
			rsTimerEnable();
		}
		else
		{
			rsRcvState = STATE_RX_IDLE;
			rsMstrState = STATE_RECEIVE_ERROR;

			portSerialEnableReceive(FALSE);
		}
		break;
	}
}

void rsTimerExpired()
{

	if (rsRcvState == STATE_RX_RCV)
	{
		rsTimerDisable();

		rsMstrState = STATE_RECEIVE_ANSWER;
		rsRcvState = STATE_RX_IDLE;

	}
	else if (rsRcvState == STATE_RX_IDLE)
	{
		rsTimerDisable();

		rsMstrState = STATE_RECEIVE_ERROR;
		rsRcvState = STATE_RX_IDLE;
	}
	portSerialEnableReceive(FALSE);
}

void rsStartPolling()
{
	if (rsMstrState == STATE_IDLE)
		rsMstrState = STATE_START_POLLING;
}


rsError rsReceiveMessage (uint8_t ** message, uint16_t * msgLenght)
{
	uint16_t crc16 = 0;
	rsError errorCode = RS_NOERROR;

	if ((rsRcvBufferPos > MAX_RS_RX_LENGHT)||
			(rsRcvBufferPos < MIN_RS_RX_LENGHT))
	{
		errorCode = RS_ERROR;
		return errorCode;
	}

	if ((rsRxBuf[0] !=  0xAA)||(rsRxBuf[1] !=  0xAA))
	{
		errorCode = RS_ERROR;
		return errorCode;
	}

	crc16 = (rsRxBuf[rsRcvBufferPos - 1] << 8) | rsRxBuf[rsRcvBufferPos - 2];

	if (crc16 == rsCRC16_ccitt(&rsRxBuf[2], rsRcvBufferPos - PREAMBLE_BYTES - CRC16_BYTES))
	{
		*message = (uint8_t* ) &rsRxBuf[0];
		*msgLenght = rsRcvBufferPos;
	}
	else errorCode = RS_ERROR;

	return errorCode;
}

void rsSendMessage(uint8_t * buf, uint16_t bufSize)
{
	portSerialPutBytes(buf, bufSize);

	rsMstrState = STATE_WAIT_ANSWER;
	rsRcvState = STATE_RX_IDLE;

	rsTimerInit(WAIT_ANSWER_PERIOD / 50); //rsTimer настроен на прерывание в 50 мкс, заданный период делим на 50
	rsTimerEnable();

	portSerialEnableReceive(TRUE);
}
