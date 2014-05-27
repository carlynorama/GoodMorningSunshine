//
// The Status LED indicated that a message has been sent
//
//  On button press the light goes to 1/3 birghtness
//  On confirmation of internet connection 2/3 brightness
//

int brightness = 255;
bool dimFlag = false;
const int unsigned long fadeTime = 6000;

void setStatusLED(byte myState) {
  switch (myState) {
    case 1:
      brightness = 200;
      break;
    case 2:
      brightness = 150;
      break;
     case 3:
      brightness = 20;
      break;
     case 4:
      dimFlag = true;
      break;
    default: 
      brightness = 255;
  }
}

void updateStatusLED() {
  if (dimFlag) {
    if (brightness < 255) {
      brightness = brightness + 1; 
      delay(10);
    } else {
      dimFlag = false;
    }
  }
  analogWrite(sentStatusLED, brightness);
}

