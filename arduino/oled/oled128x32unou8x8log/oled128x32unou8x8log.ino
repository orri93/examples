#include <Arduino.h>
#include <Wire.h>
#include <U8x8lib.h>

// U8x8 constructor for your display
U8X8_SSD1306_128X32_WINSTAR_HW_I2C u8x8();

// Create a U8x8log object
U8X8LOG u8x8log;

// Define the dimension of the U8x8log window
#define U8LOG_WIDTH 16
#define U8LOG_HEIGHT 4

// Allocate static memory for the U8x8log window
uint8_t u8log_buffer[U8LOG_WIDTH*U8LOG_HEIGHT];

void setup(void)
{
  // Startup U8x8
  u8x8.begin();
  
  // Set a suitable font. This font will be used for U8x8log
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  
  // Start U8x8log, connect to U8x8, set the dimension and assign the static memory
  u8x8log.begin(u8x8, U8LOG_WIDTH, U8LOG_HEIGHT, u8log_buffer);
  
  // Set the U8x8log redraw mode
  u8x8log.setRedrawMode(1);		// 0: Update screen with newline, 1: Update screen for every char  
}

void loop(void) {
  // Print a number on the U8x8log window
  // The display will be refreshed
  u8x8log.print(millis());
  // Print a new line, scroll the text window content if required
  // Refresh the screen
  u8x8log.print("\n");
  
  delay(500);
}
