
void sendMessage() {
  checkForInternet();
  putMessage();
  messageReceivedConfirmation();
}

void checkForInternet() {
  outMessageStatusState = 2;
  setStatusLED(outMessageStatusState);
}

void putMessage() {
  outMessageStatusState = 3;
  setStatusLED(outMessageStatusState);
}

void messageReceivedConfirmation() {
  outMessageStatusState = 4;
  setStatusLED(outMessageStatusState);
}

