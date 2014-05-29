//For Communications
#include <Console.h>
#include <Bridge.h>
#include <Process.h>

//For the Button
//https://github.com/carlynorama/Arduino-Library-Button
#include <Button.h>

//turn on and off debugging messages for this section of code
const bool debug_main = 1; 

//-----------------------------------------------------------  MESSAGES
bool newReceivedMessageFlag = false;
bool newSentMessageFlag = false;

// 0 = no pending message, 1 = trying to reach internet,  2 = found internet

//------------------------------------------------------------------ IO
Button sendButton = Button(11, LOW);
int sentStatusLED = 9; 
//everything about the sun lives in its own section

//---------------------------------------------------------------------
//--------------------------------------------------------------- SETUP
//---------------------------------------------------------------------

void setup() {
  //COMMUNICATION
  
  Bridge.begin();
  Console.begin(); 
  //while (!Console); // wait for Console port to connect. halts sketch
  Console.println(F("You're connected to the Console!!!!"));
  
  //INPUT AND OUTPUT
  //Inputs:
  //set button parameters
  sendButton.setDebounceDelay(50);
  
  //Outputs:
  blinkm_setup(); //in sun_handling tab
  pinMode(sentStatusLED, OUTPUT);
  
  //INTERNET & THINGSPEAK
  //sendMessage();  // just to start off the conversation


}

//---------------------------------------------------------------------
//---------------------------------------------------------------- LOOP
//---------------------------------------------------------------------


void loop() {
  //STEP 1: LISTEN TO THE WORLD
  
  //new messages on server?
  newReceivedMessageFlag = checkForMessage();
  
  //new button press?
  sendButton.listen();  
  if (sendButton.onPress()){
    newSentMessageFlag = true;
  }
  
  //STEP 2: DO SOMETHING ABOUT IT
  
  if (newReceivedMessageFlag) {
    if (debug_main) { Console.println(F("New Message Received")); }
    initializeSunrise();
    newReceivedMessageFlag = false;
  }

  if (newSentMessageFlag) {
    sendMessage();
    if (debug_main) { Console.println(F("New Message Sent")); }
    initializeSunset();
    newSentMessageFlag = false;

  }

 //STEP 3: UPDATE LOCAL DISPLAY
 updateSun();
 updateStatusLED();

}


