/*
 */

#include <Bridge.h>
#include <Process.h>
#include <FileIO.h>

#include "NetMessaging.h"

//
void setup()
{
  Bridge.begin();   // Initialize the Bridge
  Console.begin();   // Initialize the Console
  //while(!Console); // wait for console to connect (halts sketch)
  
  delay(1000);
  Console.println("ThingSpeakTest!");

  setupMessageCheck();

  //sendMessage();  // just to start off the conversation

}

//
void loop()
{
  boolean hasMsg = checkForMessage();

  if( hasMsg ) {
      Console.print(millis()); Console.println("  woot! got a message!");
  } else { 
      Console.print(millis()); Console.println("  no message yet for me.");
  }

  delay(100);
}

//
void loop1()
{
  boolean hasMsg = checkForMessageAsync();

  if( hasMsg ) {
      Console.println(millis() + "  woot! got a message!");
  } else { 
      Console.println(millis() + "  no message yet for me.");
  }

  delay(100);
}

//
void loop0()
{
  boolean hasMsg = checkForMessageSync();

  if( hasMsg ) {
      Console.print(millis()); Console.println("  woot! got a message!");
  } else { 
      Console.print(millis()); Console.println("  no message yet for me.");
  }

  delay(100);
}



