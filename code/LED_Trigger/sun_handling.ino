#include "BlinkM.h"
#include "Wire.h"

int unsigned long previousColorChangeTime = 0;


int blinkm_addr = 0;  // 0 = broadcast, talk to all blinkms
BlinkM blinkm = BlinkM(blinkm_addr);

const int unsigned long sunrise_change_time = 60000;
int fadeTimeTicks = 1;  // 1 is slow 255 is fast


const int num_colors_sunrise = 5;
byte sunrise_color_list_rgb[][3] = {
  { 142, 165, 173 },
  { 238, 160, 242 },
  { 255, 255, 255 },
  { 251, 248, 190 },
  { 250, 187, 25 },
};

const int num_colors_sunset = 6;
byte sunset_color_list_rgb[][3] = {
  { 250, 168, 25 },
  { 255, 146, 0 },
  {255, 122, 0 },
  {142, 49, 0 },
  {33, 49, 64 },
  {0, 0, 0 },
};

const int unsigned long sunrise_change_time_each =  sunrise_change_time / num_colors_sunrise;

void MaxM_forSetUpLoop() {
  blinkm.powerUp();
  blinkm.begin();
  blinkm.stopScript();  // turn off startup script
  blinkm.setFadeSpeed(fadeTimeTicks);
  nightyNight();
  Serial.println("done setting up");
}

void sunRise() {
  //every sunrise_change_time/num_colors_sunrise millis send a new
  //color to the blinkM with a fade command.
  if (currentColor < num_colors_sunrise) {
    sunState = 1;
    if (millis() - previousColorChangeTime >= sunrise_change_time_each) {
      previousColorChangeTime = millis();
      newColor = currentColor;

      byte r = sunrise_color_list_rgb[newColor][0];
      byte g = sunrise_color_list_rgb[newColor][1];
      byte b = sunrise_color_list_rgb[newColor][2];

      blinkm.fadeToRGB(r, g, b);

      currentColor = newColor + 1;
      Serial.print("Changed to color: ");
      Serial.println(newColor);
    }
  } else if (currentColor >= num_colors_sunrise) {
    sunState = 2;
  }
}

void sunSet() {
  //every sunrise_change_time/num_colors_sunrise millis send a new
  //color to the blinkM with a fade command.
  if (currentColor < num_colors_sunset) {
    sunState = 3;
    if (millis() - previousColorChangeTime >= sunrise_change_time_each) {
      previousColorChangeTime = millis();
      newColor = currentColor;

      byte r = sunset_color_list_rgb[newColor][0];
      byte g = sunset_color_list_rgb[newColor][1];
      byte b = sunset_color_list_rgb[newColor][2];

      blinkm.fadeToRGB(r, g, b);

      currentColor = newColor + 1;
      Serial.print("Changed to color: ");
      Serial.println(newColor);
    }
  }  else if (currentColor >= num_colors_sunrise) {
    sunState = 0;
  }
}

void nightyNight() {
   blinkm.fadeToRGB(0, 0, 0);
}