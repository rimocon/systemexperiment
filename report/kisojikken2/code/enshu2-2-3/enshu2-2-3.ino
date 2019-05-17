const int LED_PIN = 13;
const int SW_PIN = 2;
int sw1;
void setup() {
  pinMode(LED_PIN,OUTPUT);
  pinMode(SW_PIN,INPUT);
}

// the loop function runs over and over again forever
void loop() {
  sw1=digitalRead(SW_PIN);
  if(sw1==LOW){
    digitalWrite(LED_PIN,HIGH);
  }
  else{
    digitalWrite(LED_PIN,LOW);
  }
}
