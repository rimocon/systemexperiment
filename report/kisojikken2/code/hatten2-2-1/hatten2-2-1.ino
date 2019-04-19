const int LED_PIN = 3;
void setup() {
  pinMode(LED_PIN,OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  for(int i = 0; i <= 5;i++){
    digitalWrite(LED_PIN,HIGH);
    delay(500);
    digitalWrite(LED_PIN,LOW);
    delay(500);
  }
  delay(2000);
}
