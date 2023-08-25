#ifndef INDICATOR_TASK_H
#define INDICATOR_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "ws2812.h"

typedef enum
{
    INDICATOR_OFF,
    INDICATOR_BRAKE,
    INDICATOR_BLINK_LEFT,
    INDICATOR_BLINK_RIGHT
} indicator_command_t;

typedef struct
{
    indicator_command_t command;
    uint8_t brightness;
} indicator_command_data_t;

extern QueueHandle_t indicator_command_data_q;

void task_indicator(void* param);

#endif