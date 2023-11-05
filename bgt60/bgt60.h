/*
 * bgt60.h
 *
 *  Created on: Oct 29, 2023
 *      Author: gaton
 */

#ifndef BGT60_H_
#define BGT60_H_

#include "cybsp.h"
#include "cyhal.h"
#include "cycfg.h"
#include "cy_retarget_io.h"

typedef enum {
	BGT60_MOTION_INVALID = 0,
	BGT60_NO_MOTION,
	BGT60_MOTION
} Bgt60_Motion;

typedef enum {
	BGT60_DIR_INVALID = 0,
	BGT60_APPROACHING,
	BGT60_DEPARTING
} Bgt60_Direction;

typedef struct {
	Bgt60_Motion motion;
	Bgt60_Direction direction;
} bgt60_rslt_t;

typedef struct {
	GPIO_PRT_Type *tdPort;
	uint32_t tdPin;
	GPIO_PRT_Type *pdPort;
	uint32_t pdPin;
	uint32_t sampleNumber;
	bgt60_rslt_t lastResult;
} bgt60_t;

static const cy_stc_gpio_pin_config_t bgt60_gpio_cfg =
{
    .outVal = 1,
    .driveMode = CY_GPIO_DM_HIGHZ,
    .hsiom = HSIOM_SEL_GPIO,
    .intEdge = CY_GPIO_INTR_DISABLE,
    .intMask = 0UL,
    .vtrip = CY_GPIO_VTRIP_CMOS,
    .slewRate = CY_GPIO_SLEW_FAST,
    .driveSel = CY_GPIO_DRIVE_1_2,
    .vregEn = 0UL,
    .ibufMode = 0UL,
    .vtripSel = 0UL,
    .vrefSel = 0UL,
    .vohSel = 0UL,
};

cy_rslt_t bgt60_init(bgt60_t *bgt60);
bgt60_rslt_t bgt60_getReading(bgt60_t *bgt60);

#endif /* BGT60_H_ */
