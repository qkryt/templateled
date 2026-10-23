#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#ifndef PICO_DEFAULT_WS2812_PIN
#define PICO_DEFAULT_WS2812_PIN 16
#endif

static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}

uint32_t get_rainbow_color(uint8_t pos, float brightness) {
    pos = 255 - pos;
    uint8_t r, g, b;
    if (pos < 85) {
        r = (uint8_t)((255 - pos * 3) * brightness);
        g = 0;
        b = (uint8_t)((pos * 3) * brightness);
    } else if (pos < 170) {
        pos -= 85;
        r = 0;
        g = (uint8_t)((pos * 3) * brightness);
        b = (uint8_t)((255 - pos * 3) * brightness);
    } else {
        pos -= 170;
        r = (uint8_t)((pos * 3) * brightness);
        g = (uint8_t)((255 - pos * 3) * brightness);
        b = 0;
    }
    return urgb_u32(r, g, b);
}

int main() {
    stdio_init_all();
    
    uint offset = pio_add_program(pio0, &ws2812_program);
    ws2812_program_init(pio0, 0, offset, PICO_DEFAULT_WS2812_PIN, 800000, false);

    uint8_t color_position = 0;
    float safe_brightness = 0.2f;

    while (true) {
        uint32_t color = get_rainbow_color(color_position, safe_brightness);
        put_pixel(color);
        color_position++;
        sleep_ms(20);
    }
    return 0;
}
