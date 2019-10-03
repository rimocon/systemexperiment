#include <Pushbutton.h>

const int buzzerPin = 3;
const int ledPin = 13;

Pushbutton button(ZUMO_BUTTON);

void setup() {
  pinMode(ledPin,OUTPUT);
  button.waitForButton();
  tone(buzzerPin,440);
  delay(500);
  noTone(buzzerPin);
}

void loop() {
  if (button.isPressed() == true) {
    digitalWrite(ledPin,HIGH);
  } else {
    digitalWrite(ledPin,LOW);
  }
}
