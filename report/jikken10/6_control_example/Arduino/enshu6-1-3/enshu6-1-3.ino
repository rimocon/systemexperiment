#include<MsTimer2.h>
const int D9 = 9;
const int tops[4] = {31250, 15626, 6250, 3125};
const int Ts = 40;
int iteration = 0;
int cnt = 0;
void control() {
  iteration++;
  if ( iteration >= 100){
    iteration = 0;
    cnt++;
    if ( cnt >= 4 ){
      cnt = 0;
    }
    ICR1 = tops[cnt];
  }
}
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
ICR1 = tops[0];
}

void setup() {
  initPWM1();
  analogWrite(D9, 255 * 0.03);
  MsTimer2::set(Ts,control);
  MsTimer2::start();
}

void loop() {}
