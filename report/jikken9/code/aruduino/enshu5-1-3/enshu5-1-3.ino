#include <MsTimer2.h>
const int D6 = 6;
float dutyH = 0.30, dutyL = 0.2, duty = dutyL;
boolean isHigh = true;
int iteration = 0;
int Ts = 40; //サンプリング周期
void control() {
  iteration++;
  if (iteration >= 100) {
    iteration=0;
    if( isHigh){
      isHigh = false;
      duty = dutyL;
    }
    else {
      isHigh = true;
      duty = dutyH;
    }
  }

  analogWrite(D6,duty*255);
}
void setup() {
  analogWrite(D6,0);
  MsTimer2::set(Ts,control); //40[ms]ごと
  MsTimer2::start();
}
void loop() {}
