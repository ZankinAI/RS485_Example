/*
 * port.h
 *
 *  Created on: Sep 15, 2023
 *      Author: zankin
 */

#ifndef PORTSERIAL_PORT_H_
#define PORTSERIAL_PORT_H_

#include <inttypes.h>
#include "main.h"
typedef uint8_t BOOL;

#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif

#define WAIT_ANSWER_PERIOD 500 //����� �������� ������ �� ����������, ���

void portSerialEnableReceive(BOOL xRxEnable);


void RS_SetUartModule(UART_HandleTypeDef* uart);
BOOL xMBPortSerialPutByte(uint8_t ucByte);
BOOL portSerialGetByte(uint8_t * getByte);
BOOL portSerialPutBytes(uint8_t * buffer, uint16_t bufferSize);
void rsSendMessage(uint8_t * buf, uint16_t bufSize);
void rsByteReceived();
void rsStartPolling();
void rsTimerExpired();

typedef enum{
	RS_NOERROR,
	RS_ERROR,
}rsError;

rsError rsReceiveMessage (uint8_t ** message, uint16_t * msgLenght);

void rsTimerEnable();
void rsTimerDisable();
BOOL rsTimerInit(uint16_t usTim1Timerout50us);


//��������� ������ RS-�������
typedef enum{
	STATE_NOT_INIT,
	STATE_IDLE,				//����� ��������
	STATE_START_POLLING,	//����� �������� �����
	STATE_TRANSMITE_FRAME,	//�������� ����
	STATE_WAIT_ANSWER,		//������� �����
	STATE_RECEIVE_ANSWER,	//������ ���������� �����
	STATE_RECEIVE_ERROR,	//������ ���
}rsMasterState;


rsMasterState getRsMasterState();
void setRsMasterState(rsMasterState state);


typedef enum{
	STATE_RX_IDLE,  //�������� � ������ ��������
	STATE_RX_RCV	//�������� � �������� ������
}rsRxState;

typedef enum{
	TX_IDLE,		//���������� � ������ ��������
	TX_RCV			//���������� � �������� ��������
}rsTxState;



#endif /* PORTSERIAL_PORT_H_ */
