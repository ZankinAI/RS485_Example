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

#define WAIT_ANSWER_PERIOD 500 //Время ожидания ответа от устройства, мкс

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


//Возможные режимы RS-мастера
typedef enum{
	STATE_NOT_INIT,
	STATE_IDLE,				//режим ожидания
	STATE_START_POLLING,	//готов начинать опрос
	STATE_TRANSMITE_FRAME,	//передает кадр
	STATE_WAIT_ANSWER,		//ожидает ответ
	STATE_RECEIVE_ANSWER,	//принят правильный ответ
	STATE_RECEIVE_ERROR,	//ответа нет
}rsMasterState;


rsMasterState getRsMasterState();
void setRsMasterState(rsMasterState state);


typedef enum{
	STATE_RX_IDLE,  //Приемник в режиме ожидания
	STATE_RX_RCV	//Приемник в процессе приема
}rsRxState;

typedef enum{
	TX_IDLE,		//Передатчик в режиме ожидания
	TX_RCV			//Передатчик в процессе передачи
}rsTxState;



#endif /* PORTSERIAL_PORT_H_ */
