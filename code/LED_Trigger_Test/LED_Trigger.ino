bool NewRecievedMessage = false;
bool NewSentMesageFlag = false; 

void setup() {
  Serial.begin(9600);
  MaxM_forSetUpLoop();


}

void loop() {
  // put your main code here, to run repeatedly:
    sunRise();
}
