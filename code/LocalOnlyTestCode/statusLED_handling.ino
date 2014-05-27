//
// The Status LED indicated that a message has been sent
//
//  On button press the light goes to 1/3 birghtness
//  On confirmation of internet connection 2/3 brightness
//

int brightness = 255;

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
    default: 
      brightness = 255;
  }
}

void updateStatusLED() {
  analogWrite(sentStatusLED, brightness);
}

