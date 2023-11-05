#include "cybsp.h"
#include "cyhal.h"
#include "cycfg.h"
#include "cy_retarget_io.h"
#include "radar_task.h"
#include "bgt60/bgt60.h"

void task_radar(void* param)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    (void)param;

    bgt60_t radar =
	{
	    .tdPort = RADAR_TD_PORT,
		.tdPin = RADAR_TD_PIN,
		.pdPort = RADAR_PD_PORT,
		.pdPin = RADAR_PD_PIN,
	};

    result = bgt60_init(&radar);
    if (CY_RSLT_SUCCESS != result) {
    	printf("ERROR initializing BGT60\n");

    	vTaskSuspend(NULL);
    }

    for (;;)
    {
    	bgt60_rslt_t reading = bgt60_getReading(&radar);
		printf("radar motion = %d\n", (int)reading.motion);

		ble_capsense_data_t ble_capsense_data;
		ble_capsense_data.updateRadar = 1u;
		ble_capsense_data.radarStatus = (uint8_t)BGT60_DIR_INVALID;

		// Approaching radar
		if (BGT60_MOTION == reading.motion)
		{
			printf("motion detected\n");
			printf("Direction = %d\n", (int)reading.direction);
			ble_capsense_data.radarStatus = (uint8_t)reading.direction;
		}

		xQueueSendToBack(ble_capsense_data_q, &ble_capsense_data, 0u);
		vTaskDelay(500u / portTICK_PERIOD_MS);
    }

	vTaskSuspend(NULL);
}
