const int D9 = 9;
float top = 31250;
void initPWM1() {
// PWM freq = 16MHz / r (prescaler) / 2 (phase-correct) / (top)
// when r=256
//  1Hz -> top = 31250 (60rpm)
// 10Hz -> top = 3125 (600rpm)
TCCR1A = 0b10100000;
// TCCR1B = 0b00010001; //r=1
// TCCR1B = 0b00010010; //r=8
// TCCR1B = 0b00010011; //r=64
TCCR1B = 0b00010100;    //r=256
// TCCR1B = 0b00010101; //r=1024
ICR1 = top;
}

void setup() {
  initPWM1();
  analogWrite(D9, 255 * 0.03);
}

void loop() {}
