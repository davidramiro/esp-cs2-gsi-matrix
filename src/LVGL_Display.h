#pragma once

#include <Arduino.h>
#include <lvgl.h>

#include "AppConfig.h"
#include "LGFX_Config.hpp"

class LVGLDisplay {
public:
    static void begin();
    static void handle();

    static LGFX &screen();

private:
    static void flush(lv_display_t *display, const lv_area_t *area, uint8_t *pxMap);

    static LGFX _screen;
    static lv_display_t *_display;
    static lv_color_t *_drawBuffer;
};