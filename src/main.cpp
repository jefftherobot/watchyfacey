/////////////////////////////////////////////////////////////////////////////
// Hardware Setup: SQFMI E-Paper Watch "Watchy"
// https://watchy.sqfmi.com/
// - ESP32-PICO-D4
// - E-Paper Display GDEH0154D67
// - 3-Axis Accelerometer BMA423
// - Real Time Clock DS3231
// - Tactile Buttons K2-1114SA-A4SW-06
// - Vibration Motor 1020
// - Battery LiPo Battery 3.7V 200mAh
/////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <Watchy.h> //include the Watchy library
#include "fonts/DIN_1451_Engschrift_Regular64pt7b.h"
#include "fonts/DIN_1451_Engschrift_Regular12pt7b.h"
				

class WatchFace : public Watchy { //inherit and extend Watchy class
  public:
    void drawWatchFace() { //override this method to customize how the watch face looks
      
      int16_t  x1, y1, lasty;
      uint16_t w, h;
      String textstring;
      bool light = true;
      
      //drawbg
      display.fillScreen(light ? GxEPD_WHITE : GxEPD_BLACK);
      display.fillRoundRect(2,2,196,196,8,light ? GxEPD_BLACK : GxEPD_WHITE);
      display.fillRoundRect(6,6,188,188,5,light ? GxEPD_WHITE : GxEPD_BLACK);
      
      display.setFont(&DIN_1451_Engschrift_Regular64pt7b);
      display.setTextColor(light ? GxEPD_BLACK : GxEPD_WHITE);
      display.setTextWrap(false);

      //draw hours
      textstring = currentTime.Hour;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(183-w, 100-5);
      display.print(textstring);
      
      //draw minutes
      if (currentTime.Minute < 10) {
        textstring = "0";
      } else {
        textstring = "";
      }
      textstring += currentTime.Minute;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(183-w, 100+3+h);
      display.print(textstring);

      // draw battery
      display.fillRoundRect(16,16,34,12,4,light ? GxEPD_BLACK : GxEPD_WHITE);
      display.fillRoundRect(49,20,3,4,2,light ? GxEPD_BLACK : GxEPD_WHITE);
      display.fillRoundRect(18,18,30,8,3,light ? GxEPD_WHITE : GxEPD_BLACK);
      float batt = (getBatteryVoltage()-3.3)/0.9;
      if (batt > 0) {
       display.fillRoundRect(20,20,26*batt,4,2,light ? GxEPD_BLACK : GxEPD_WHITE);
      }									

      display.setFont(&DIN_1451_Engschrift_Regular12pt7b);
      lasty = 200 - 16;

      //draw steps
      textstring = sensor.getCounter();
      textstring += " steps";
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.fillRoundRect(16,lasty-h-2,w + 7,h+4,2,light ? GxEPD_BLACK : GxEPD_WHITE);
      display.setCursor(19, lasty-3);
      display.setTextColor(light ? GxEPD_WHITE : GxEPD_BLACK);
      display.print(textstring);
      display.setTextColor(light ? GxEPD_BLACK : GxEPD_WHITE);
      lasty += -8-h;

      // draw year
      textstring = currentTime.Year + 1970;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(16, lasty);
      display.print(textstring);
      lasty += -20;

      // draw date
      textstring = monthShortStr(currentTime.Month);
      textstring += " ";
      textstring += currentTime.Day;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(16, lasty);
      display.print(textstring);
      lasty += -20;
      
      // draw day
      textstring = dayStr(currentTime.Wday);
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(16, lasty);
      display.print(textstring);

    }
};

WatchFace m; //instantiate your watchface

void setup() {
  m.init(); //call init in setup
}

void loop() {
  // this should never run, Watchy deep sleeps after init();
}
