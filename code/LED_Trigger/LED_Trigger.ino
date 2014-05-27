//For Communications
#include <Console.h>

const bool debugFlag = 1; 

bool newReceivedMessageFlag = false;
bool newSentMessageFlag = false;

//FOR TESTING RECIEVED MESSAGES
int receiveMessagePin = 10;  //sunrise, orange wire
int sendMessagePin = 11;  //sunset, yellow wire
int sentStatusPin = 13;

void setup() {
  // initialize serial communication:
  Bridge.begin();
  Console.begin(); 

  while (!Console){
    ; // wait for Console port to connect.
  }
  Console.println("You're connected to the Console!!!!");
  
  MaxM_forSetUpLoop(); //in sun_handling tab
  pinMode(receiveMessagePin, INPUT);
  pinMode(sendMessagePin, INPUT);
  pinMode(sentStatusPin, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  newReceivedMessageFlag = !digitalRead(receiveMessagePin);
  newSentMessageFlag = !digitalRead(sendMessagePin);

  if (newReceivedMessageFlag) {
    if (debugFlag) { Console.println("New Message Recived"); }
    initializeSunrise();
  }

  if (newSentMessageFlag) {
    if (debugFlag) { Console.println("New Message Sent"); }
    initializeSunset();

  }

 updateSun();

}

