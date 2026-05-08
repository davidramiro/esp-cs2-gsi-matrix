#include "LVGL_Display.h"

LGFX LVGLDisplay::_screen;
lv_display_t *LVGLDisplay::_display = nullptr;
lv_color_t *LVGLDisplay::_drawBuffer = nullptr;

void LVGLDisplay::begin() {
    _screen.init();
    _screen.setRotation(1);
    _screen.setColorDepth(16);
    _screen.fillScreen(TFT_BLACK);
    _screen.setBrightness(18);

    lv_init();

    constexpr uint32_t bufferLines = 40;
    constexpr uint32_t bufferPixels = SCREEN_WIDTH * bufferLines;

    _drawBuffer = static_cast<lv_color_t *>(
        heap_caps_malloc(bufferPixels * sizeof(lv_color_t), MALLOC_CAP_DMA));

    if (_drawBuffer == nullptr) {
        _drawBuffer = static_cast<lv_color_t *>(
            heap_caps_malloc(bufferPixels * sizeof(lv_color_t), MALLOC_CAP_8BIT));
    }

    if (_drawBuffer == nullptr) {
        Serial.println("LVGL draw buffer allocation failed");
        while (true) {
            delay(1000);
        }
    }

    _display = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_display_set_flush_cb(_display, flush);
    lv_display_set_buffers(
        _display,
        _drawBuffer,
        nullptr,
        bufferPixels * sizeof(lv_color_t),
        LV_DISPLAY_RENDER_MODE_PARTIAL);
}

void LVGLDisplay::handle() {
    lv_timer_handler();
}

LGFX &LVGLDisplay::screen() {
    return _screen;
}

void LVGLDisplay::flush(lv_display_t *display, const lv_area_t *area, uint8_t *pxMap) {
    const uint32_t width = area->x2 - area->x1 + 1;
    const uint32_t height = area->y2 - area->y1 + 1;

    _screen.startWrite();
    _screen.setAddrWindow(area->x1, area->y1, width, height);
    _screen.writePixels(reinterpret_cast<lgfx::rgb565_t *>(pxMap), width * height);
    _screen.endWrite();

    lv_display_flush_ready(display);
}