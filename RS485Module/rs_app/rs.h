/*
 * rs.h
 *
 *  Created on: Sep 17, 2023
 *      Author: zankin
 */

#ifndef RS_APP_RS_H_
#define RS_APP_RS_H_

#include "port.h"
#include "rs_protocol.h"
#include "device.h"

#define DEVICE_COUNT 4


void sendPoolingMessageToDevice(uint8_t deviceId);
void sendSwitchMessageToDevice(uint8_t deviceId, switch_t switchMode);

#endif /* RS_APP_RS_H_ */
