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
/** ������� ������ UART.
 * �������� �������� ������� ��� ������������
 **/
void RS_SetUartModule(UART_HandleTypeDef* uart)
{
	rsUart = uart;
}
/*----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------*/
/** ���������-���������� ������ UART.
 * �������� ��� ������������ ������� ���/���� ������ �� UART
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
/** �������� ����� �� UART.
 *��� ������������ �������� ������� �������� �� UART
 **/
BOOL portSerialPutByte(uint8_t ucByte)
{
  txByte = ucByte;
  HAL_UART_Transmit(rsUart, &txByte, 1, 100);
  return TRUE;
}


/* --------------------------------------------------------------------------*/
/** �������� ������ �� UART.
 *��� ������������ �������� ������� �������� �� UART
 **/
BOOL portSerialPutBytes(uint8_t * buffer, uint16_t bufferSize)
{
  HAL_UART_Transmit(rsUart, buffer, bufferSize,100);
  return TRUE;
}


/* --------------------------------------------------------------------------*/
/** ����� ����� �� UART.
 *��� ������������ �������� ������� ������ �� UART
 **/
BOOL portSerialGetByte(uint8_t * getByte)
{
  *getByte = rxByte;
  HAL_UART_Receive_IT(rsUart, &rxByte, 1);
  return TRUE;
}




/* --------------------------------------------------------------------------*/
/** ���������� ���������� �� UART.
 *��� ������������ �������� ������� �����������
 **/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == rsUart->Instance)
  {
	  rsByteReceived();
  }
}

/* --------------------------------------------------------------------------*/

