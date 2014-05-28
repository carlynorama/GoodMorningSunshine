//
// NetTests -- testing out the "goodmorning.py" script functionality
//
// to try this out, load it up on a Yun
// then do "./goodmorning py set thingyB.txt" from your computer's terminal
// this is doing a fake button press to this sketch
// Note there's some oddness when seconds < 60 I think due to 
// ftp or filesystem strangeness
//

#include <FileIO.h>
#include <Process.h>

#include "script_goodmorning.h"
#include "NetMessagingFTP.h"

//
void setup() 
{
  Bridge.begin();   // Initialize the Bridge
  Console.begin();   // Initialize the Console
  //while(!Console); // wait for console to connect
  
  delay(1000);
  Console.println("NetTests!");

  writeScript_goodmorning();

  sendMessage();
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

  delay(5000);  // wait 5 seconds before you do it again
}


