/*
 */

#include <Bridge.h>
#include <Process.h>

#include "NetMessaging.h"

//
void setup()
{
  Bridge.begin();   // Initialize the Bridge
  Console.begin();   // Initialize the Console
  //while(!Console); // wait for console to connect
  
  delay(1000);
  Console.println("ThingSpeakTest!");

  sendMessage();  // just to start off the conversation
}

//
void loop()
{
  boolean hasMsg = checkForMessage();

  if( hasMsg ) {
    Console.println("woot! got a message!");
  } else { 
    Console.println("no message yet for me.");
  }

  delay(5000);
}




