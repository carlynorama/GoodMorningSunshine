#include "BlinkM.h"
#include "Wire.h"

int unsigned long previousColorChangeTime = 0;


int blinkm_addr = 0;  // 0 = broadcast, talk to all blinkms
BlinkM blinkm = BlinkM(blinkm_addr);

const int unsigned long sunrise_change_time = 60000;
int fadeTimeTicks = 1;  // 1 is slow 255 is fast

int currentColor = 0;
int newColor = 0;

const int num_colors_sunrise = 4;
byte sun_rise_color_list_rgb[][3] = {
  { 0x00, 0xff, 0xff }, // cyan
  { 0xff, 0x00, 0xff }, // purple
  { 0xff, 0xff, 0xff }, // white
  { 0xff, 0xff, 0x00 }, // orange
};

const int unsigned long sunrise_change_time_each =  sunrise_change_time / num_colors_sunrise;

void MaxM_forSetUpLoop() {
  blinkm.powerUp();
  blinkm.begin();
  blinkm.stopScript();  // turn off startup script
  blinkm.setFadeSpeed(fadeTimeTicks);
  Serial.println("done setting up");
}

void sunRise() {
  //every sunrise_change_time/num_colors_sunrise millis send a new
  //color to the blinkM with a fade command.
  if (currentColor < num_colors_sunrise) {
    if (millis() - previousColorChangeTime >= sunrise_change_time_each) {
      previousColorChangeTime = millis();
      newColor = currentColor;
      
      byte r = sun_rise_color_list_rgb[newColor][0];
      byte g = sun_rise_color_list_rgb[newColor][1];
      byte b = sun_rise_color_list_rgb[newColor][2];
      
      blinkm.fadeToRGB(r,g,b);
      
      currentColor = newColor +1;
      Serial.print("Changed to color: ");
      Serial.println(newColor);
    }
  }
}

void sunSet() {
}
