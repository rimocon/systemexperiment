const int buzzerPin = 3; //ブザーは3番ピン
const int buttonPin = 12; //ユーザーボタンは12番ピン
const int ledPin = 13; //led 13番ピン

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin,OUTPUT);
}

void loop() {
  while(digitalRead(buttonPin));
  digitalWrite(ledPin,HIGH);
  tone(buzzerPin,960);
  delay(650);
  tone(buzzerPin,770);
  delay(650);
  digitalWrite(ledPin,LOW);
  noTone(buzzerPin);
}
