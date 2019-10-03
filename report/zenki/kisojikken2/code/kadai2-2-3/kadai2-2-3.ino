const int LED_PIN = 3;
const int SW_PIN = 4;
int sw1;
void setup() {
  pinMode(LED_PIN,OUTPUT);
  pinMode(SW_PIN,INPUT);
}

// the loop function runs over and over again forever
void loop() {
  sw1=digitalRead(SW_PIN);
  if(sw1==LOW){//スイッチを押したとき
    digitalWrite(LED_PIN,HIGH);
  }
  else{//スイッチがOFFのとき
    digitalWrite(LED_PIN,HIGH);
    delay(200);
    digitalWrite(LED_PIN,LOW);
    delay(200);
  }
}
