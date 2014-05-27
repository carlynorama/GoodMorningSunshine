
void checkForMessages() {
if (Console.available() > 0) {
    // read the oldest byte in the serial buffer:
    byte incomingByte = Console.read();
    if (incomingByte == 'H') {
      newReceivedMessageFlag;
    } 
  }
}

