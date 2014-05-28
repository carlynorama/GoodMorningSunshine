
//
//
// Uses two ThingSpeak Talkback message queue to communicate
// First queue is for Device A to send to Device B
// Second queue is for Device B to send to Device A
// To set up the queues, sign up (for free) to ThingSpeak.com,
// and add two TalkBacks: https://thingspeak.com/apps/talkbacks
// Give it a name and click "Update Talkback".
// You will see a "TalkBack ID" and an "API Key" for that TalkBack queue.
// When you have both queues configured, enter their Ids and Keys below.
//

const int who_am_i = 'A';  // or 'B'

// CONFIGURATION: edit these four items for your set of TalkBack queues
String talkbackIdA = "420";
String talkbackIdB = "421";
String apiKeyA = "XDRCZ0LNWXFSJVIW";
String apiKeyB = "C0WRVX6WHAD92ZU1";


String thingSpeakBaseUrl = "https://api.thingspeak.com/talkbacks/";

String cmdSetA = "curl --data 'api_key=" +
  apiKeyA + "&command_string=hello' '" +
  thingSpeakBaseUrl + talkbackIdA + "/commands/execute.json'";
String cmdSetB = "curl --data 'api_key=" +
  apiKeyB + "&command_string=hello' '" +
  thingSpeakBaseUrl + talkbackIdB + "/commands/execute.json'";

String cmdGetA = "curl " + thingSpeakBaseUrl + talkbackIdA + 
  "/commands.json?api_key="+apiKeyA;
String cmdGetB = "curl " + thingSpeakBaseUrl + talkbackIdB + 
  "/commands.json?api_key="+apiKeyB;


//
boolean checkForMessage()
{
  String cmd;
  if( who_am_i=='A' ) {
    cmd = cmdGetA;
  }
  else if( who_am_i=='B' ) {
    cmd = cmdGetA;
  }
  Process p;
  p.begin( cmd );
  p.run(); 
  String str; 
  while( p.available() > 0 ) { 
     str += p.readString(); 
  } 
  if( str.indexOf("id") != 0 ) { 
    return true;
  }
  return false;  
}

//
void sendMessage()
{
  String cmd;
  if( who_am_i=='A' ) {
    cmd = cmdSetB; // if A, send to B
  }
  else if( who_am_i=='B' ) {
    cmd = cmdSetB;
  }
  Console.println("sendMessage: cmd="+cmd);
  Process p;  
  p.runShellCommand( cmd );
}


