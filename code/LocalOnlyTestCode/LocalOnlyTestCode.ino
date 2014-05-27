//For Communications
#include <Console.h>
#include <Button.h>

const bool debugFlag = 1; 

bool newReceivedMessageFlag = false;
bool newSentMessageFlag = false;

byte outMessageStatusState = 0;
// 0 = no pending message, 1 = trying to reach internet,  2 = found internet

//IO
Button sendButton = Button(11, LOW);
int sentStatusLED = 9; 


void setup() {
  // initialize serial communication:
  Bridge.begin();
  Console.begin(); 

  sendButton.setDebounceDelay(50);
  
  while (!Console){
    ; // wait for Console port to connect.
  }
  Console.println("You're connected to the Console!!!!");
  
  MaxM_forSetUpLoop(); //in sun_handling tab
  pinMode(sentStatusLED, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  checkForMessages();
  
  sendButton.listen();  
  if (sendButton.onPress()){
    newSentMessageFlag = true;
    outMessageStatusState = 1;
    sendMessage();
    setStatusLED(outMessageStatusState);
  }
  

  if (newReceivedMessageFlag) {
    if (debugFlag) { Console.println("New Message Recived"); }
    initializeSunrise();
    newReceivedMessageFlag = false;
  }

  if (newSentMessageFlag) {
    if (debugFlag) { Console.println("New Message Sent"); }
    initializeSunset();
    newSentMessageFlag = false;
  }

 updateSun();
 updateStatusLED();

}


