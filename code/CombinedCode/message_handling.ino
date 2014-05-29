
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

//turn on and off debugging messages for this section of code
const bool debug_mh = 0;

//---------------------------------------------------------------------
//------------------------------------------------------- CONFIGURATION
//---------------------------------------------------------------------
//Which device am I?
const int who_am_i = 'A';  // or 'B'
byte outMessageStatusState = 0;

//thingspeak.com:
//edit these four items for your set of TalkBack queues
String talkbackIdA = "420";
String talkbackIdB = "421";
String apiKeyA = "XDRCZ0LNWXFSJVIW";
String apiKeyB = "C0WRVX6WHAD92ZU1";

//---------------------------------------------------------------------
//------------------------------------------------------ THINGSPEAK API
//---------------------------------------------------------------------
String thingSpeakBaseUrl = "https://api.thingspeak.com/talkbacks/";

// Set Cmds have form:
// curl --data 'api_key=XDRCZ0LNWXFSJVIW&command_string=hello' 'https://api.thingspeak.com/talkbacks/420/commands.json'
String cmdSetA = "curl -k --data 'api_key=" +
                 apiKeyA +
                 "&command_string=hello' '" +
                 thingSpeakBaseUrl +
                 talkbackIdA +
                 "/commands.json'";
String cmdSetB = "curl -k --data 'api_key=" +
                 apiKeyB +
                 "&command_string=hello' '" +
                 thingSpeakBaseUrl +
                 talkbackIdB +
                 "/commands.json'";
// Get Cmds ahve form:
// curl 'https://api.thingspeak.com/talkbacks/420/commands/execute.json?api_key=XDRCZ0LNWXFSJVIW'
String cmdGetA = "curl -k '" + thingSpeakBaseUrl +
                 talkbackIdA +
                 "/commands/execute.json?api_key=" +
                 apiKeyA +
                 "'";
String cmdGetB = "curl -k '" + thingSpeakBaseUrl +
                 talkbackIdB +
                 "/commands/execute.json?api_key=" +
                 apiKeyB +
                 "'";

//---------------------------------------------------------------------
//------------------------------------------------------------- INBOUND
//---------------------------------------------------------------------
boolean checkForMessage()
{
  String cmd;
  if ( who_am_i == 'A' ) {
    cmd = cmdGetA;
  }
  else if ( who_am_i == 'B' ) {
    cmd = cmdGetB;
  }
  if (debug_mh) Console.println("checkForMessage: cmd=\n  " + cmd);
  Process p;
  p.runShellCommand( cmd );
  while (p.running()); // do nothing until process finishes

  String str;
  while ( p.available() > 0 ) {
    str += p.readString();
  }
  if (debug_mh)Console.println("str=" + str);

  // if empty set, got good response, but no results
  if ( str.indexOf("{}") != -1 ) { // empty set
    return false;
  }
  // if result has json result set keys, likely a good message
  if ( str.indexOf("id") != -1 && str.indexOf("command_string") != -1 ) {
    return true;
  }
  return false; // by default, no message
}
//-------------------------------------------------------------
//---------------------------------------------------- OUTBOUND
//-------------------------------------------------------------

void sendMessage() {
  outMessageStatusState = 1;
  setStatusLED(outMessageStatusState);
  checkForInternet();
  putMessage();
  messageReceivedConfirmation();
}

void checkForInternet() {
  outMessageStatusState = 2;
  setStatusLED(outMessageStatusState);
}

void putMessage() {
  outMessageStatusState = 3;
  setStatusLED(outMessageStatusState);
  String cmd;
  if ( who_am_i == 'A' ) {
    cmd = cmdSetB; // if A, send to B
  }
  else if ( who_am_i == 'B' ) {
    cmd = cmdSetB;
  }
  if (debug_mh) Console.println("sendMessage: cmd=\n  " + cmd);
  Process p;
  p.runShellCommand( cmd );
}

void messageReceivedConfirmation() {
  outMessageStatusState = 4;
  setStatusLED(outMessageStatusState);
}


