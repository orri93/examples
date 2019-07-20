#include <Arduino.h>
#include <Wire.h>
#include <U8x8lib.h>

#define DELAY_U8X8 3000

#define PIN_SDA      A4
#define PIN_SCL      A5

/* Software I2C */
//U8X8_SSD1306_128X32_UNIVISION_SW_I2C u8x8(PIN_SCL, PIN_SDA);
/* Hardware I2C */
//U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8();
//U8X8_SSD1306_128X32_UNIVISION_2ND_HW_I2C u8x8();

//U8X8_SSD1306_128X32_WINSTAR_SW_I2C u8x8(PIN_SCL, PIN_SDA);
/* Hardware I2C */
U8X8_SSD1306_128X32_WINSTAR_HW_I2C u8x8();
//U8X8_SSD1306_128X32_WINSTAR_2ND_HW_I2C u8x8();

void setup() {
  u8x8.begin();
}

void loop() {
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,0,"Hello World!");
  u8x8.drawString(0,8,"Line 2");
  u8x8.drawString(0,16,"Line 3");
  
  delay(DELAY_U8X8);
}

