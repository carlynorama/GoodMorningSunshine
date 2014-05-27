
void checkForMessages() {
  //if (debugFlag) { Console.println("checking for messages");}
  if (Console.available() > 0) {
      // read the oldest byte in the serial buffer:
      byte incomingByte = Console.read();
      if (incomingByte == 'G') {
        if (debugFlag) { Console.println("Good Morning Message"); }
        newReceivedMessageFlag = true;
      }
    }
}

