#pragma once

#define LGFX_USE_V1

#define TFT_CS 15
#define TFT_DC 2
#define TFT_RST 4
#define TFT_SCLK 18
#define TFT_MOSI 23
#define TFT_BLK 32



#include <LovyanGFX.hpp>
#include "main.h"

class LGFX : public lgfx::LGFX_Device
{
  lgfx::Panel_ST7789 _panel_instance;
  lgfx::Bus_SPI _bus_instance;
 
public:
  LGFX(void)
  {
    {
      auto cfg = _bus_instance.config();
      cfg.spi_host = VSPI_HOST;     // ESP32 VSPI (SPI3)
      cfg.spi_mode = 0;
      cfg.freq_write = 40000000;    // 40MHz (ST7789 supports higher speeds)
      cfg.freq_read  = 16000000;

      cfg.spi_3wire  = false;
      cfg.use_lock   = true;
      cfg.dma_channel = SPI_DMA_CH_AUTO;
      cfg.pin_sclk = TFT_SCLK;            // SPI SCK (connect to display SCL)
      cfg.pin_mosi = TFT_MOSI;            // SPI MOSI (connect to display SDA)
      cfg.pin_miso = -1;            // SPI MISO (not connected)
      cfg.pin_dc   = TFT_DC;             // Data/Command pin

      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }
 
    {
      auto cfg = _panel_instance.config();

      cfg.pin_cs           = TFT_CS;    // Chip Select
      cfg.pin_rst          = TFT_RST;     // Reset
      cfg.pin_busy         = -1;    // Not used

      cfg.panel_width      = SCREEN_HEIGHT;   // Physical width
      cfg.panel_height     = SCREEN_WIDTH;   // Physical height
      cfg.offset_x         = 52;     // X offset
      cfg.offset_y         = 40;     // Y offset
      cfg.offset_rotation  = 0;
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits  = 1;

      cfg.readable         = false;
      cfg.invert           = true;  // Color inversion (may need to toggle)
      cfg.rgb_order        = true;
      cfg.dlen_16bit       = false;
      cfg.bus_shared       = true;
 
      _panel_instance.config(cfg);
    }
 
    setPanel(&_panel_instance);
  }
};