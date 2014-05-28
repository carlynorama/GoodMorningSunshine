//
// Uses FTP to send & receive messages
//

const int who_am_i = 'A';  // or 'B'
const int debug = 0; // set to 1 to get some Console debug output

char filenameA[] = "thingyA.txt";
char filenameB[] = "thingyB.txt";

//
boolean checkForMessage()
{
  char* fname;
  if( who_am_i=='A' ) {
    fname = filenameA; 
  }
  else if( who_am_i=='B' ) {
    fname = filenameB;
  }
  String str = runScript_goodmorning("get",fname);
  int secs = str.toInt();
  if(debug) { 
    Console.print("output: "); Console.println( str );
  }

  if( secs > 0 ) {   // if not zero and not negative, message!
    return true;
  }
  return false;
}

//
void sendMessage() 
{
  char* fname;
  if( who_am_i=='A' ) {
    fname = filenameB; // if A, send to B
  }
  else if( who_am_i=='B' ) {
    fname = filenameA;
  }

  runScript_goodmorning("set", fname);
}




