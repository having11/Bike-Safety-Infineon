#ifndef RADAR_TASK_H
#define RADAR_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <inttypes.h>
#define XENSIV_BGT60TRXX_CONF_IMPL
#include "lib/radar/presence_radar_settings.h"
#include "xensiv_bgt60trxx_mtb.h"

/*******************************************************************************
* Macros
*******************************************************************************/
/* sensor SPI interface */
#define PIN_XENSIV_BGT60TRXX_SPI_SCLK       P6_2
#define PIN_XENSIV_BGT60TRXX_SPI_MOSI       P6_0
#define PIN_XENSIV_BGT60TRXX_SPI_MISO       P6_1
#define PIN_XENSIV_BGT60TRXX_SPI_CSN        P6_3
/* sensor interrupt output pin */
#define PIN_XENSIV_BGT60TRXX_IRQ            P9_1
/* sensor HW reset pin */
#define PIN_XENSIV_BGT60TRXX_RSTN           P9_2
/* enable 1V8 LDO on radar wingboard*/
#define PIN_XENSIV_BGT60TRXX_LDO_EN         P9_4
#define XENSIV_BGT60TRXX_SPI_FREQUENCY      (25000000UL)
#define NUM_SAMPLES_PER_FRAME               (XENSIV_BGT60TRXX_CONF_NUM_RX_ANTENNAS *\
                                             XENSIV_BGT60TRXX_CONF_NUM_CHIRPS_PER_FRAME *\
                                             XENSIV_BGT60TRXX_CONF_NUM_SAMPLES_PER_CHIRP)

extern QueueHandle_t radar_command_data_q;

void task_radar(void* param);

#endif