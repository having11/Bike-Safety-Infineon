#include "cybsp.h"
#include "cyhal.h"
#include "cycfg.h"
#include "cy_retarget_io.h"
#include "indicator_task.h"

#define ASSERT_WITH_PRINT(x, ...)   if(!(x)) { printf(__VA_ARGS__ ); CY_ASSERT(0); }

QueueHandle_t indicator_command_data_q;
TimerHandle_t indicator_timer_handle;
static indicator_command_data_t indicator_cmd_data;

void ws2812_timer_cb(TimerHandle_t handle);

void stop_timer()
{
    if (xTimerIsTimerActive(indicator_timer_handle) != pdFALSE)
    {
        xTimerStop(indicator_timer_handle, pdMS_TO_TICKS(500));
    }
}

void task_indicator(void* param)
{
    BaseType_t rtos_api_result = pdFAIL;
    ws2818_res_t ws_res;

    indicator_timer_handle = xTimerCreate
    (
        "WS2812_TIMER",
        pdMS_TO_TICKS(1000),
        pdTRUE,
        (void*)0,
        ws2812_timer_cb
    );

    (void)param;

    ws_res = ws2812_init(P5_0, NC, NC);
    ASSERT_WITH_PRINT(ws2812_success == ws_res, "ws2812_init failed\r\n");

    for(;;)
    {
        rtos_api_result = xQueueReceive(indicator_command_data_q, &indicator_cmd_data,
            portMAX_DELAY);
        if(pdPASS == rtos_api_result)
        {
            switch(indicator_cmd_data.command)
            {
                stop_timer();
                case INDICATOR_OFF:
                {
                    ws2812_set_all_leds(0, 0, 0);
                    ws2812_update();
                }
                break;

                case INDICATOR_BRAKE:
                {
                    ws2812_set_all_leds(255, 0, 0);
                    ws2812_update();
                }
                break;

                case INDICATOR_BLINK_LEFT:
                case INDICATOR_BLINK_RIGHT:
                {
                    xTimerStart(indicator_timer_handle, pdMS_TO_TICKS(500));
                }
                break;
            }
        }
    }
}

void ws2812_timer_cb(TimerHandle_t handle)
{
    static uint8_t state = 0;

    if(state == 0)
    {
        state = 1 - state;
        ws2812_set_all_leds(0, 0, 0);
        ws2812_update();

        return;
    }

    state = 1 - state;

    if(indicator_cmd_data.command == INDICATOR_BLINK_LEFT)
    {
        ws2812_set_range(0, (WS2812_LEDS_COUNT / 2) - 1, 150, 150, 0);
        ws2812_update();
    }
    else if(indicator_cmd_data.command == INDICATOR_BLINK_RIGHT)
    {
        ws2812_set_range((WS2812_LEDS_COUNT / 2), WS2812_LEDS_COUNT - 1, 150, 150, 0);
        ws2812_update();
    }
}