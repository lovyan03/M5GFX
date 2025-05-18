
#if __has_include(<SPIFFS.h>)
  #include <SPIFFS.h>
#endif

#include <M5GFX.h>

#if defined SKIP_I2C_TEST
  #define DUMMY_DISPLAY
#endif

static M5GFX display1;
static LGFX_Sprite sprite(&display1);

void test(LGFX_Device &lcd)
{
  lcd.init();
  lcd.setRotation(1);
  lcd.setBrightness(128);
  lcd.setColorDepth(24);
  lcd.drawPixel(0, 0, 0xFFFF);
  lcd.drawFastVLine(2, 0, 100, lcd.color888(255,   0,   0));
  lcd.drawFastVLine(4, 0, 100, lcd.color565(  0, 255,   0));
  lcd.drawFastVLine(6, 0, 100, lcd.color332(  0,   0, 255));
  uint32_t red = 0xFF0000;
  lcd.drawFastHLine(0, 2, 100, red);
  lcd.drawFastHLine(0, 4, 100, 0x00FF00U);
  lcd.drawFastHLine(0, 6, 100, (uint32_t)0xFF);
  uint16_t green = 0x07E0;
  lcd.drawRect(10, 10, 50, 50, 0xF800);
  lcd.drawRect(12, 12, 50, 50, green);
  lcd.drawRect(14, 14, 50, 50, (uint16_t)0x1F);
  uint8_t blue = 0x03;
  lcd.fillRect(20, 20, 20, 20, (uint8_t)0xE0);
  lcd.fillRect(30, 30, 20, 20, (uint8_t)0x1C);
  lcd.fillRect(40, 40, 20, 20, blue);
  lcd.setColor(0xFF0000U);
  lcd.fillCircle ( 40, 80, 20    );
  lcd.fillEllipse( 80, 40, 10, 20);
  lcd.fillArc    ( 80, 80, 20, 10, 0, 90);
  lcd.fillTriangle(80, 80, 60, 80, 80, 60);
  lcd.setColor(0x0000FFU);
  lcd.drawCircle ( 40, 80, 20    );
  lcd.drawEllipse( 80, 40, 10, 20);
  lcd.drawArc    ( 80, 80, 20, 10, 0, 90);
  lcd.drawTriangle(60, 80, 80, 80, 80, 60);

  sprite.setColorDepth(24);
  sprite.createSprite(65, 65);

  for (uint32_t x = 0; x < 64; ++x) {
    for (uint32_t y = 0; y < 64; ++y) {
      sprite.drawPixel(x, y, lcd.color888(3 + x*4, (x + y)*2, 3 + y*4));
    }
  }
  sprite.drawRect(0, 0, 65, 65, 0xFFFF);
  sprite.pushSprite(64, 0);
  sprite.pushSprite(&lcd, 0, 64);

  sprite.deleteSprite();
}

void setup()
{
  test(display1);
}

void loop(void)
{
  delay(1000);
}

#if !defined ARDUINO
extern "C" {
  void loopTask(void*)
  {
    setup();
    for(;;) {
      loop();
    }
  }
  void app_main()
  {
    xTaskCreatePinnedToCore( loopTask, "loopTask", 8192, NULL, 1, NULL, 1 );
  }
}
#endif
