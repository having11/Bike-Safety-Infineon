/*
From https://github.com/HunkoBohdan/music_synched_LED_PSoC/blob/topic/DMA-for-ws2812/psoc_project/music_synch_led_project/lib/ws2812/ws2812.h
@HunkoBohdan
*/

#ifndef __WS2812_H__
#define __WS2812_H__

#include "cybsp.h"

#define WS2812_LEDS_COUNT 12

typedef enum
{
    ws2812_success,
    ws2812_error_generic,
    ws2812_error_invalid_led_id
} ws2818_res_t;

ws2818_res_t ws2812_init(cyhal_gpio_t mosi, cyhal_gpio_t miso, cyhal_gpio_t sclk);
ws2818_res_t ws2812_set_led(uint16_t led, uint8_t red, uint8_t green, uint8_t blue);
ws2818_res_t ws2812_set_range(uint16_t start, uint16_t end, uint8_t red, uint8_t green, uint8_t blue);
ws2818_res_t ws2812_set_all_leds(uint8_t red, uint8_t green, uint8_t blue);
ws2818_res_t ws2812_update(void);

#endif /* __WS2812_H__ */
