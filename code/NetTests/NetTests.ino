//
// NetTests -- Yun Net Script Experiments
//

#include <FileIO.h>
#include <Process.h>

#include "script_goodmorning_get.h"

//
void setup() 
{
  delay(3000);
  Bridge.begin();   // Initialize the Bridge
  Console.begin();   // Initialize the Console
  //while(!Console); // wait for console to connect
  
  uploadScript_goodmorning_get();
  //runScript1();
}

//
void loop() 
{
  runScript_goodmorning_get_tod("mistery");
  delay(5000);  // wait 5 seconds before you do it again
}

void runScript_goodmorning_get_tod(char* arg1) {  
  Console.print("running script");
  Process p;  
  p.begin( goodmorning_get_path ); 
  p.addParamter( arg1 );
  p.run(); 

  while( p.available() > 0 ) { 
      char c = p.read();
      Console.print(c);
  }
  Console.flush();
} 

