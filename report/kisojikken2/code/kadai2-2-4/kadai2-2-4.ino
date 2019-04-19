const int LED_RED_PIN = 3;
const int LED_YEL_PIN = 13;
const int SW_PIN = 4;
int sw1;
void setup() {
  pinMode(LED_RED_PIN,OUTPUT);
  pinMode(LED_YEL_PIN,OUTPUT);
  pinMode(SW_PIN,INPUT);
}

// the loop function runs over and over again forever
void loop() {
  sw1=digitalRead(SW_PIN);
  if(sw1==LOW){
    digitalWrite(LED_RED_PIN,HIGH);
    digitalWrite(LED_YEL_PIN,LOW);
  }
  else{
    digitalWrite(LED_RED_PIN,LOW);
    digitalWrite(LED_YEL_PIN,HIGH);
  }
}
