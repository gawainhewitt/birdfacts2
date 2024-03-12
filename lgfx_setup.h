class LGFX : public lgfx::LGFX_Device
{

  lgfx::Panel_GC9A01      _panel_instance;

  lgfx::Bus_SPI        _bus_instance;   // SPI

  lgfx::Light_PWM     _light_instance;

  public:

    LGFX(void)
  {
    { 
      auto cfg = _bus_instance.config();    

// SPIバスの設定
      cfg.spi_host = VSPI_HOST;     // ESP32-S2,C3 : SPI2_HOST or SPI3_HOST / ESP32 : VSPI_HOST or HSPI_HOST
      cfg.spi_mode = 0;             // SPI (0 ~ 3)
      cfg.freq_write = 27000000;    // (80MHz, 80MHz)
      cfg.freq_read  = 20000000;    // SPI
      cfg.spi_3wire  = true;        // MOSI
      cfg.use_lock   = true;        // true
      cfg.dma_channel = SPI_DMA_CH_AUTO; // (0=DMA/ 1=1ch / 2=ch / SPI_DMA_CH_AUTO)
      cfg.pin_sclk = 18;            // SPI SCLK
      cfg.pin_mosi = 23;            // SPI MOSI
      cfg.pin_miso = -1;            // SPI MISO (-1 = disable)
      cfg.pin_dc   = 32;            // SPI D/C  (-1 = disable)
  
      _bus_instance.config(cfg);    
      _panel_instance.setBus(&_bus_instance);      
    }

    { 
      auto cfg = _panel_instance.config();    

      cfg.pin_cs           =    5;  // CS   (-1 = disable)
      cfg.pin_rst          =    4;  // RST  (-1 = disable)
      cfg.pin_busy         =    -1;  // BUSY (-1 = disable)

      cfg.panel_width      =   240;  
      cfg.panel_height     =   240;  
      cfg.offset_x         =     0;  
      cfg.offset_y         =     0;  
      cfg.offset_rotation  =     0;   // 0~7 
      cfg.dummy_read_pixel =     8;  
      cfg.dummy_read_bits  =     1;  
      cfg.readable         =  true; 
      cfg.invert           = true;  
      cfg.rgb_order        = false;  
      cfg.dlen_16bit       = false;  
      cfg.bus_shared       =  true;  

      _panel_instance.config(cfg);
    }

//*
    { 
      auto cfg = _light_instance.config();  

      cfg.pin_bl = 32;              
      cfg.invert = false;           
      cfg.freq   = 44100;          
      cfg.pwm_channel = 7;         

      _light_instance.config(cfg);
      _panel_instance.setLight(&_light_instance);  
    }

    setPanel(&_panel_instance); 
  }
};