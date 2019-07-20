#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

#define DELAY_OLED 3000
#define PIN_SDA      A4
#define PIN_SCL      A5

U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C u8g2(U8G2_R0);

//const uint8_t* font8 = u8x8_font_px437wyse700a_2x2_r;
//const uint8_t* font82 = u8x8_font_chroma48medium8_r;
//const uint8_t* DefaultFont = u8g2_font_inr16_mf;
//const uint8_t* fontthatworks = u8g2_font_logisoso28_tr;

void forelines();
void twolines();

void setup() {
  u8g2.begin();
}

void loop() {
  twolines();
  delay(DELAY_OLED);
  forelines();
  delay(DELAY_OLED);
}

void twolines() {
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_inr16_mf);
  u8g2.drawStr(0, 16, "ABC defg");
  u8g2.setFont(u8g2_font_inr16_mf);
  u8g2.drawStr(16, 34, "123 $%(");
  u8g2.sendBuffer();					// transfer internal memory to the u8g2
}

void forelines() {
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_Wizzard_tr);
  u8g2.drawStr(0, 8, "ABC defg");
  u8g2.setFont(u8g2_font_Wizzard_tr);
  u8g2.drawStr(16, 18, "123 $%(");
  u8g2.sendBuffer();					// transfer internal memory to the u8g2
}

void waittolater() {
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8x8_font_chroma48medium8_r);
  u8g2.drawStr(0, 0, "ABC defg");
  u8g2.setFont(u8x8_font_chroma48medium8_r);
  u8g2.drawStr(0, 2, "123 Þæö");
  u8g2.sendBuffer();					// transfer internal memory to the u8g2
  delay(DELAY_OLED);

  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8x8_font_chroma48medium8_r);
  u8g2.drawStr(10, 0, "Góðan");
  u8g2.setFont(u8x8_font_chroma48medium8_r);
  u8g2.drawStr(12, 2, "Daginn");
  u8g2.sendBuffer();					// transfer internal memory to the u8g2
  delay(DELAY_OLED);
}
