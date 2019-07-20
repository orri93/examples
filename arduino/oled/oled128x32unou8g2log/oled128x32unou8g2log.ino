#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C u8g2(U8G2_R0);
//U8G2_SSD1306_128X32_UNIVISION_2_HW_I2C u8g2(U8G2_R0);
//U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);
//U8G2_SSD1306_128X32_UNIVISION_1_2ND_HW_I2C u8g2(U8G2_R0);
//U8G2_SSD1306_128X32_UNIVISION_2_2ND_HW_I2C u8g2(U8G2_R0);
//U8G2_SSD1306_128X32_UNIVISION_F_2ND_HW_I2C u8g2(U8G2_R0);

U8G2LOG u8g2log;

// assume 4x6 font, define width and height
#define U8LOG_WIDTH 32
#define U8LOG_HEIGHT 5

// allocate memory
uint8_t u8log_buffer[U8LOG_WIDTH*U8LOG_HEIGHT];

void setup() {
  u8g2.begin();    
  u8g2.setFont(u8g2_font_tom_thumb_4x6_mf);	// set the font for the terminal window
  u8g2log.begin(u8g2, U8LOG_WIDTH, U8LOG_HEIGHT, u8log_buffer);	// connect to u8g2, assign buffer
  u8g2log.setLineHeightOffset(0);	// set extra space between lines in pixel, this can be negative
  u8g2log.setRedrawMode(0);		// 0: Update screen with newline, 1: Update screen for every char  
}

void loop() {
  // Print a number on the U8g2log window
  u8g2log.print(millis());
  // Print a new line, scroll the text window content if required
  // Refresh the screen
  u8g2log.print("\n");
  
  delay(500);
}
