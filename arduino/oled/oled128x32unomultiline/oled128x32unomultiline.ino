#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

#define DELAY_OLED 3000
#define PIN_SDA      A4
#define PIN_SCL      A5

U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C u8g2(U8G2_R0);
//U8G2_SSD1306_128X32_UNIVISION_2_HW_I2C u8g2(U8G2_R0);
//U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);
//U8G2_SSD1306_128X32_UNIVISION_1_2ND_HW_I2C u8g2(U8G2_R0);
//U8G2_SSD1306_128X32_UNIVISION_2_2ND_HW_I2C u8g2(U8G2_R0);
//U8G2_SSD1306_128X32_UNIVISION_F_2ND_HW_I2C u8g2(U8G2_R0);

void twolinesmono11();
void twolines13();
void threelines();
void forelines();

void setup() {
  u8g2.begin();
}

void loop() {
  // picture loop
  u8g2.firstPage();
  do {
    twolinesmono11();
  } while( u8g2.nextPage() );
 
  // rebuild the picture after some delay
  delay(DELAY_OLED);
 
  // picture loop
  u8g2.firstPage();
  do {
    threelines();
  } while( u8g2.nextPage() );
 
  // rebuild the picture after some delay
  delay(DELAY_OLED);

    // picture loop
  u8g2.firstPage();
  do {
    forelines();
  } while( u8g2.nextPage() );
 
  // rebuild the picture after some delay
  delay(DELAY_OLED);

}

void twolinesmono11() {
  u8g2.setFont(u8g2_font_profont22_mf    );
  u8g2.drawStr(0, 14, "u8g2_font_t0_17_mf");
  u8g2.setFont(u8g2_font_profont22_mf    );
  u8g2.drawStr(16, 32, "Line 2 123 $%( þæö");
}

void threelines() {
  u8g2.setFont(u8g2_font_t0_11b_mf    );
  u8g2.drawStr(0, 8, "u8g2_font_t0_17_mf");
  u8g2.setFont(u8g2_font_t0_11b_mf    );
  u8g2.drawStr(16, 18, "Line 2 123 $%( þæö");
  u8g2.setFont(u8g2_font_t0_11b_mf    );
  u8g2.drawStr(16, 32, "Line 2 123 $%( þæö");
}

void twolines13() {
  u8g2.setFont(u8g2_font_10x20_tf );
  u8g2.drawStr(0, 16, "Line 1 u8g2_font_10x20_tf");
  u8g2.setFont(u8g2_font_10x20_tf );
  u8g2.drawStr(16, 32, "Line 2 123 $%( þæö");
}

void twolines12() {
  u8g2.setFont(u8g2_font_ncenR12_tf );
  u8g2.drawStr(0, 16, "Line 1 u8g2_font_ncenR12_tf");
  u8g2.setFont(u8g2_font_ncenR12_tf );
  u8g2.drawStr(16, 32, "Line 2 123 $%( þæö");
}

void forelines() {
  u8g2.setFont(u8g2_font_5x7_mf   );
  u8g2.drawStr(0, 6, "ABC defg");
  u8g2.setFont(u8g2_font_5x7_mf   );
  u8g2.drawStr(16, 14, "123 $%(");
  u8g2.setFont(u8g2_font_5x7_mf   );
  u8g2.drawStr(24, 22, "Line 3");
  u8g2.setFont(u8g2_font_5x7_mf   );
  u8g2.drawStr(32, 32, "Line 4");
}

void waittolater() {
  u8g2.setFont(u8x8_font_chroma48medium8_r);
  u8g2.drawStr(0, 0, "ABC defg");
  u8g2.setFont(u8x8_font_chroma48medium8_r);
  u8g2.drawStr(0, 2, "123 Þæö");

  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8x8_font_chroma48medium8_r);
  u8g2.drawStr(10, 0, "Góðan");
  u8g2.setFont(u8x8_font_chroma48medium8_r);
  u8g2.drawStr(12, 2, "Daginn");
  u8g2.sendBuffer();					// transfer internal memory to the u8g2
  delay(DELAY_OLED);
}
