
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
const int debug = 1; // set to 1 to get some Console debug output

// CONFIGURATION: edit these four items for your set of TalkBack queues
String talkbackIdA = "420";
String talkbackIdB = "421";
String apiKeyA = "XDRCZ0LNWXFSJVIW";
String apiKeyB = "C0WRVX6WHAD92ZU1";


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
// Get Cmds have form:
// curl 'https://api.thingspeak.com/talkbacks/420/commands/execute.json?api_key=XDRCZ0LNWXFSJVIW'
String cmdGetA = "curl -k '" + thingSpeakBaseUrl + 
    talkbackIdA + 
    "/commands/execute.json?api_key="+ 
    apiKeyA + 
    "'";
String cmdGetB = "curl -k '" + thingSpeakBaseUrl + 
    talkbackIdB + 
    "/commands/execute.json?api_key=" + 
    apiKeyB + 
    "'";


Process checkProcess;
void setupMessageCheck()
{
  String cmd;
  if( who_am_i=='A' ) {
    cmd = cmdGetA;
  }
  else if( who_am_i=='B' ) {
    cmd = cmdGetB;
  }

  // write a little shell script daemon to fetch our stuff
  // write to RAM so we don't wear out flash
  File f = FileSystem.open( "/tmp/goodmorningcheck.sh", FILE_WRITE); 
  f.print(F( "#!/bin/sh \n" ));
  f.print(F( "while [ 1 ] ; do : \n"));
  f.print(F( "  "));  
  f.print( cmd );
  f.print(F( " > /tmp/goodmorningcheck.out \n"));
  f.print(F( "  sleep 5 \n"));
  f.print(F( "done \n"));
  f.print(F( "\n" ));
  f.close();
 
  // make executable 
  Process chmod; 
  chmod.runShellCommand("chmod +x /tmp/goodmorningcheck.sh");

  // this seems to hang Yun on re-upload
  checkProcess.runShellCommandAsynchronously("/tmp/goodmorningcheck.sh");
  
  // this doesn't work, disown not available
  //checkProcess.runShellCommand("/tmp/goodmorningcheck.sh &; disown %1");

}

//decl
boolean checkForMessage();

//
boolean checkForMessageFile()
{
  File f = FileSystem.open("/tmp/goodmorningcheck.out");
  String str = f.readString();

  if(debug) Console.println("checkForMessageFile: "+str);

  // if empty set, got good response, but no results
  if( str.indexOf("{}") != -1 ) { // empty set
    return false;
  }
  // if result has json result set keys, likely a good message
  if( str.indexOf("id") != -1 && str.indexOf("command_string") != -1){ 
    return true;
  }
  return false;
}


boolean checkForMessageAsync()
{
  if( !checkProcess.running() ) {
    
    if( checkProcess.available() > 0 ) {
      
      String str; 
      while( checkProcess.available() >0 ) { 
        str += checkProcess.readString(); 
      }
      if(debug) Console.println("str="+str);

      // if empty set, got good response, but no results
      if( str.indexOf("{}") != -1 ) { // empty set
        return false;
      }
      // if result has json result set keys, likely a good message
      if( str.indexOf("id") != -1 && str.indexOf("command_string") != -1){ 
        return true;
      }

    }

    // restart
    String cmd;
    if( who_am_i=='A' ) {
      cmd = cmdGetA;
    }
    else if( who_am_i=='B' ) {
      cmd = cmdGetB;
    }
    if(debug) Console.println("checkForMessageAsync: cmd=\n  "+cmd);
      
    checkProcess.runShellCommandAsynchronously( cmd );
  }
  
  return false;
}


//
boolean checkForMessageSync()
{
  String cmd;
  if( who_am_i=='A' ) {
    cmd = cmdGetA;
  }
  else if( who_am_i=='B' ) {
    cmd = cmdGetB;
  }
  if(debug) Console.println("checkForMessage: cmd=\n  "+cmd);
  Process p;
  p.runShellCommand( cmd );
  while(p.running()); // do nothing until process finishes
  
  String str; 
  while( p.available() >0 ) { 
     str += p.readString(); 
  }
  if(debug)Console.println("str="+str);

  // if empty set, got good response, but no results
  if( str.indexOf("{}") != -1 ) { // empty set
      return false;
  }
  // if result has json result set keys, likely a good message
  if( str.indexOf("id") != -1 && str.indexOf("command_string") != -1 ) { 
      return true;
  }
  return false; // by default, no message
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
  if(debug) Console.println("sendMessage: cmd=\n  "+cmd);
  Process p;  
  p.runShellCommand( cmd );
}


uint32_t lastMessageCheckTime;
boolean checkForMessage()
{
  if (millis() - lastMessageCheckTime > 2000 ) {
    lastMessageCheckTime = millis();
    return checkForMessageFile();
    return checkForMessageASync();
    //return checkForMessageSync();
  }
  return false;
}
