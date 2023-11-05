/*
 * bgt60.c
 *
 *  Created on: Oct 29, 2023
 *      Author: gaton
 */

#include "bgt60.h"

cy_rslt_t bgt60_init(bgt60_t *bgt60) {
	cy_en_gpio_status_t res;
	res = Cy_GPIO_Pin_Init(bgt60->tdPort, bgt60->tdPin, &bgt60_gpio_cfg);
	if (CY_GPIO_SUCCESS != res) {
		return -1;
	}

	res = Cy_GPIO_Pin_Init(bgt60->pdPort, bgt60->pdPin, &bgt60_gpio_cfg);
	if (CY_GPIO_SUCCESS != res) {
		return -1;
	}

	bgt60->sampleNumber = 0;
}

bgt60_rslt_t bgt60_getReading(bgt60_t *bgt60) {
	bgt60_rslt_t result;
	int val;
	result.motion = BGT60_MOTION_INVALID;
	result.direction = BGT60_DIR_INVALID;

	val = Cy_GPIO_Read(bgt60->tdPort, bgt60->tdPin);
	result.motion = BGT60_NO_MOTION;

	if (1UL == val) {
		result.motion = BGT60_MOTION;
	}

	val = Cy_GPIO_Read(bgt60->pdPort, bgt60->pdPin);
	result.direction = BGT60_APPROACHING;

	if (1UL == val) {
		result.motion = BGT60_DEPARTING;
	}

	bgt60->lastResult = result;
	bgt60->sampleNumber++;

	return result;
}
