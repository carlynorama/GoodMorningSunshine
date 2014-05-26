bool newReceivedMessageFlag = false;
bool newSentMessageFlag = false; 

//INFORMATION ABOUT THE SUN
int currentColor = 0;
int newColor = 0;
byte sunState = 0;
// 0 = off
// 1 = rising
// 2 = risen
// 3 = setting


//FOR TESTING RECIEVED MESSAGES
int receiveMessagePin = 10;
int sendMessagePin = 11;
int sentStatusPin = 13;

void setup() {
  Serial.begin(9600);
  MaxM_forSetUpLoop(); //in sun_handling tab
  pinMode(receiveMessagePin, INPUT);
  pinMode(sendMessagePin, INPUT);
  pinMode(sentStatusPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  newReceivedMessageFlag = !digitalRead(receiveMessagePin);
  newSentMessageFlag = !digitalRead(receiveMessagePin);
  
  if(newReceivedMessageFlag) {
     currentColor = 0;
     sunState = 1;
  }
  
  if(newSentMessageFlag) {
     currentColor = 0;
     if (sunState > 0) {
       sunState = 3;
     }
  }
  
  
  if (sunState == 1) {
    sunRise();
  } else if (sunState == 3) {
    sunSet();
  }
}
