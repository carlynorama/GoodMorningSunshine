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

//
void setup() 
{
  Bridge.begin();   // Initialize the Bridge
  Console.begin();   // Initialize the Console
  //while(!Console); // wait for console to connect
  
  delay(1000);
  Console.println("NetTests!");

  writeScript_goodmorning();

  sendPressToOther();  // just say "hi" now that we woke up
}

//
void loop() 
{
  int secs = getSecondsSinceOtherPressed();

  if( secs > 0 ) { 
    Console.print("They pressed their button ");
    Console.print(secs);
    Console.println(" seconds ago!");
  } else if( secs == 0 ) { 
    Console.println("They've not pressed their button lately.");
  } else if( secs < 0 ) { 
    Console.println("Uh-oh, error. Network down?");
  }

  delay(5000);  // wait 5 seconds before you do it again
}

// Send a button press to the other side
void sendPressToOther()
{
  runScript_goodmorning("set","thingyA.txt");
}

// Looks on the Net and checks the other's button.
// Returns number of minutes since other side pressed their button
// returns 1-65000 if button was pressed
// return 0 if unchanged 
// return <0 if an error occurred
int getSecondsSinceOtherPressed()
{
  String str = runScript_goodmorning("get","thingyB.txt");
  //Console.print("output: ");
  //Console.println( str );
  int secs = str.toInt();
  return secs;
}


//runScript_goodmorning_tod("set","thingyA.txt");
//String str = runScript_goodmorning_tod("get","thingyB.txt");

String runScript_goodmorning_tod(char* arg1, char* arg2) 
{  
  Process p;  
  p.begin( goodmorning_path ); 
  if(arg1) p.addParameter( arg1 );
  if(arg2) p.addParameter( arg2 );
  p.run();
  while(p.running()); // do nothing until cmd is finished
  String str;
  while( p.available() > 0 ) { 
    str += p.readString();
  }
  return str;
} 


