#include "BlinkM.h"
#include "Wire.h"

int unsigned long previousColorChangeTime = 0;

//INFORMATION ABOUT THE SUN
int currentColor = 0;
int newColor = 0;
byte sunState = 0;
// 0 = off
// 1 = rising
// 2 = risen
// 3 = setting

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
  if (debugFlag) {
    Console.println("done setting up");
  }
}

void initializeSunrise() {
  currentColor = 0;
  sunState = 1;
  if (debugFlag) {
    Console.println("sunRise");
  }
}

void initializeSunset() {
  if (sunState > 0) {
    sunState = 3;
    currentColor = 0;
    if (debugFlag) {
      Console.println("sunSet");
    }
  } else {
    if (debugFlag) {
      Console.println("already off");
    }
  }

}

void nightyNight() {
  blinkm.fadeToRGB(0, 0, 0);
  sunState = 0;
}

void updateSun() {
  if (sunState == 1) {
    sunRise();
  } else if (sunState == 3) {
    sunSet();
  } else if (sunState == 0) {
    nightyNight();
  }
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
      if (debugFlag) {
        Console.print("Changed to color: ");
        Console.println(newColor);
      }
    }
  } else if (currentColor >= num_colors_sunrise) {
    sunState = 2;
    if (debugFlag) {
        Console.print("Sunrise Complete");
    }
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
      if (debugFlag) {
        Console.print("Changed to color: ");
        Console.println(newColor);
      }
    }
  }  else if (currentColor >= num_colors_sunrise) {
    sunState = 0;
  }
}


