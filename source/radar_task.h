#ifndef RADAR_TASK_H
#define RADAR_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <inttypes.h>
#include "ble_task.h"

/*******************************************************************************
* Macros
*******************************************************************************/

extern QueueHandle_t radar_command_data_q;

void task_radar(void* param);

#endif
