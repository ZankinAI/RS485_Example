/*
 * port_timer.c
 *
 *  Created on: 16 ����. 2023 �.
 *      Author: zankin
 */

#include "port.h"



TIM_HandleTypeDef* rsTimer;				//������ ��� �������� ������
TIM_HandleTypeDef* rsPollingTimer;		//������ ��� ������


uint16_t rsTimerPeriodWaitByte = 0;
uint16_t rsTimerCounter = 0;


uint16_t rsPollingTimerPeriod = 10;
uint16_t rsPollingTimerCounter = 0;

/*----------------------------------------------------------------------------*/
/** ������� �������, ���������������� ��� ������� ������� �������� ������.
 * �������� �������� ������� ��� ������������
 **/
void RS_SetTimerModule(TIM_HandleTypeDef* timer)
{
	rsTimer = timer;
}

/* --------------------------------------------------------------------------*/
BOOL rsTimerInit(uint16_t usTim1Timerout50us)
{
	rsTimerPeriodWaitByte = usTim1Timerout50us;
	return TRUE;
}

/* --------------------------------------------------------------------------*/
/** ������ �������, ���������������� ��� ������� ������� �������� ������.
 * �������� ��� � ������ ������� ��� ������������
 **/
void rsTimerEnable()
{
	rsTimerCounter = 0;
	HAL_TIM_Base_Start_IT(rsTimer);
}



/* --------------------------------------------------------------------------*/
/** ������ �������, ���������������� ��� ������� ������� �������� ������.
 * �������� ��� � ������ ������� ��� ������������
 **/
void rsTimerDisable()
{
	HAL_TIM_Base_Stop_IT(rsTimer);
}


void RS_SetPollingTimerModule(TIM_HandleTypeDef* timer)
{
	rsPollingTimer = timer;
}

/* --------------------------------------------------------------------------*/
BOOL rsPollingTimerInit(uint16_t usPollingTimer)
{
	rsPollingTimerPeriod = usPollingTimer;
	return TRUE;
}

/* --------------------------------------------------------------------------*/
/** ������ �������, ���������������� ��� ������� ������� ������.
 * �������� ��� � ������ ������� ��� ������������
 **/
void rsPollingTimerEnable()
{
	rsPollingTimerCounter = 0;
	HAL_TIM_Base_Start_IT(rsPollingTimer);
}



/* --------------------------------------------------------------------------*/
/** ��������� �������, ���������������� ��� ������� ������� ������.
 * �������� ��� � ������ ������� ��� ������������
 **/
void rsPollingTimerDisable()
{
	HAL_TIM_Base_Stop_IT(rsPollingTimer);
}

/* --------------------------------------------------------------------------*/
/** ��������� ����������.
 * �������� ��� ��� ������������
 **/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
	  if (htim->Instance == rsTimer->Instance)
	  {
	      rsTimerCounter++;
	      if (rsTimerCounter == rsTimerPeriodWaitByte)
	      {
	    	  rsTimerExpired();
	      }
	  }
  /* USER CODE END Callback 0 */


  /* USER CODE BEGIN Callback 1 */
	  if (htim->Instance == rsPollingTimer->Instance)
	  {
	       rsPollingTimerCounter++;
	       if (rsPollingTimerCounter == rsPollingTimerPeriod)
	       {
	    	   rsPollingTimerCounter = 0;
			   rsStartPolling();
	       }
	  }
  /* USER CODE END Callback 1 */
}
