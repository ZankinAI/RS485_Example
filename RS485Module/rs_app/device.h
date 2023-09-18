/*
 * device.h
 *
 *  Created on: 17 ����. 2023 �.
 *      Author: zankin
 */

#ifndef RS_APP_DEVICE_H_
#define RS_APP_DEVICE_H_

#include <inttypes.h>

#define CRITICAL_AMPERAGE 10 //��������� �������� ���� ��� ���������� - 10 �����

typedef enum{
	NOT_WORK,
	WORK,
}deviceState_t;

typedef enum{
	DISCONNECTED,
	CONNECTED,
}deviceConnectionState_t;

typedef struct{
	uint8_t deviceId;
	deviceState_t deviceState;
	deviceConnectionState_t deviceConnectionState;
	float voltage;
	float amperage;
} Device_t;


void initDevice(Device_t * device, uint8_t deviceId_);
#endif /* RS_APP_DEVICE_H_ */
