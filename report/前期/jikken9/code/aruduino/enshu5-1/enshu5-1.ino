const int D6 = 6;
float duty = 0.20;

void setup() {
  analogWrite(D6,duty*255);
}

void loop() {}
