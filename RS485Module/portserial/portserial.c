/*
 * portserial.c
 *
 *  Created on: Sep 15, 2023
 *      Author: zankin
 */
#include "port.h"
#include "main.h"


UART_HandleTypeDef* rsUart;


uint8_t txByte = 0x00;
uint8_t rxByte = 0x00;


/*----------------------------------------------------------------------------*/
/** Задание модуля UART.
 * Замените параметр функции для портирования
 **/
void RS_SetUartModule(UART_HandleTypeDef* uart)
{
	rsUart = uart;
}
/*----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------*/
/** Включение-выключение модуля UART.
 * Замените для портирования функции вкл/выкл приема по UART
 **/
void portSerialEnableReceive(BOOL xRxEnable)
{
  if (xRxEnable == FALSE)
  {
	HAL_UART_AbortReceive_IT(rsUart);
  }
  else
  {
	HAL_UART_Receive_IT(rsUart, &rxByte, 1);
  }

}

/* --------------------------------------------------------------------------*/
/** Передача байта по UART.
 *Для портирования замените функцию передачи по UART
 **/
BOOL portSerialPutByte(uint8_t ucByte)
{
  txByte = ucByte;
  HAL_UART_Transmit(rsUart, &txByte, 1, 100);
  return TRUE;
}


/* --------------------------------------------------------------------------*/
/** Передача байтов по UART.
 *Для портирования замените функцию передачи по UART
 **/
BOOL portSerialPutBytes(uint8_t * buffer, uint16_t bufferSize)
{
  HAL_UART_Transmit(rsUart, buffer, bufferSize,100);
  return TRUE;
}


/* --------------------------------------------------------------------------*/
/** Прием байта по UART.
 *Для портирования замените функцию приема по UART
 **/
BOOL portSerialGetByte(uint8_t * getByte)
{
  *getByte = rxByte;
  HAL_UART_Receive_IT(rsUart, &rxByte, 1);
  return TRUE;
}




/* --------------------------------------------------------------------------*/
/** Обработчик прерывания по UART.
 *Для портирования замените функцию обработчика
 **/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == rsUart->Instance)
  {
	  rsByteReceived();
  }
}

/* --------------------------------------------------------------------------*/

