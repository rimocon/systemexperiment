const int SW1_PIN = 3;
const int SW2_PIN = 4;
const int LED_PIN = 13;
int sw1;
int sw2;
void setup() {
  pinMode(SW1_PIN,INPUT);
  pinMode(SW2_PIN,INPUT);
  pinMode(LED_PIN,OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  sw1=digitalRead(SW1_PIN);
  sw2=digitalRead(SW2_PIN);
  if(sw1==LOW&&sw2==LOW){//1,1
    digitalWrite(LED_PIN,HIGH);
  }
  if(sw1==LOW&&sw2==HIGH){//1,0
    digitalWrite(LED_PIN,HIGH);
  }
  if(sw1==HIGH&&sw2==LOW){//0,1
    digitalWrite(LED_PIN,HIGH);
  }
  if(sw1==HIGH&&sw2==HIGH){//0,0
    digitalWrite(LED_PIN,LOW);
  }
}
