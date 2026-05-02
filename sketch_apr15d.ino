#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // ST7789 driver library
#include <SPI.h>             // SPI library
// Define pin connections
#define TFT_CS    22 // Chip Select pin
#define TFT_RST   17 // Reset pin
#define TFT_DC    16  // Data/Command pin
// Initialize the display object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  Serial.println("TFT ST7789V Test");

  // Initialize the display
  tft.init(240, 320); // Initialize with 240x320 resolution
  tft.setRotation(1); // Set display orientation (0-3)
tft.invertDisplay(false);
  // Fill the screen with a color
  tft.fillScreen(ST77XX_BLACK);

  // Draw a simple message
  tft.setTextColor(ST77XX_WHITE);

  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.println("Hello, ST7789");
}

void loop() {
  // Add your code here to update the display
}