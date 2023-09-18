/*
 * device.c
 *
 *  Created on: 17 сент. 2023 г.
 *      Author: zankin
 */

#include "device.h"



void initDevice(Device_t * device, uint8_t deviceId_)
{
	device -> deviceId = deviceId_;
	device -> deviceState = WORK;
	device -> deviceConnectionState = DISCONNECTED;
}
