#include <Arduino.h>

// esp32 sdk imports
#include "esp_heap_caps.h"
#include "esp_log.h"

#include <Adafruit_GFX.h> //Graphics drawing library
#include <GxEPD2_BW.h> //Black and White Display Driver
#include <Fonts/FreeMonoBold9pt7b.h> //Font

#include "GxEPD2_display_selection_new_style.h" //Sets up configuration for display

const char HelloWorld[] = "Hello World!"; //String to print


void setup()
{
  delay(2000); //wait for serial monitor to open up in Platformio
  Serial.begin(115200);
  while (!Serial); //Apparently does nothing on USB - Serial converter boards. 
  Serial.println("\nNow Starting Up...");
  
  display.init(115200, true, 2, false); //Initialize the display 115200 bit rate

  Serial.println("helloWorld");
  display.setRotation(1); //Set screen rotation
  display.setFont(&FreeMonoBold9pt7b); //Set font
    display.setTextColor(GxEPD_BLACK); //Set font color
  int16_t tbx, tby; 
  uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(HelloWorld);
  }
  while (display.nextPage());
  Serial.println("helloWorld done");

}

void loop()
{
/*
From: https://www.codeproject.com/Articles/5318639/Render-Professional-Screens-on-IoT
Don't Use the loop() Function!
Just don't. The issue is that on the ESP32's implementation of the Arduino framework, a second FreeRTOS "task" (read thread) is created with a miserly stack size, and loop() is run on that thread, 
so trying to do anything non-trivial inside loop() will probably blow up your stack and cause a reboot.

Instead, spin a while() loop inside setup() and just work with that. If anyone can tell me a good reason not to do things this way, you let me know. 
Otherwise, I will continue to recommend this in order to gain access to the primary thread's much more generous stack.
*/
  
}