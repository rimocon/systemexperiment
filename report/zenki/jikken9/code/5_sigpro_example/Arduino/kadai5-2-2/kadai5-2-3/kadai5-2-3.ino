// list 5.1 ロータリエンコーダによる回転速度の計測
#include <MsTimer2.h>

const int D2 = 2;
const int D6 = 6;    // PWM出力ディジタルピンの定義
float dutyH = 0.25;    // duty変数の定義. duty比変更
float dutyL = 0.20;
float duty = dutyL;
boolean isHigh=false;
int Ts = 40;  // [msec]
int iteration=0;
unsigned long timep=0;
volatile float motrpm = 0;
volatile float motrpmf = 0;
volatile boolean isD2High=false;

void countUp() {
  if ((isD2High)&&(digitalRead(D2)==LOW)) {
    unsigned long timen = millis();
    motrpm = 1000.0*60.0/(float)(timen-timep);
    if( (motrpm >= 0) && (motrpm < 5000)){
      motrpmf = (3.0*motrpmf+motrpm)/4.0;
    }
    timep=timen;
    isD2High=false;
  } else if ((!isD2High)&&(digitalRead(D2)==HIGH)) {
    isD2High=true;
  }
}

void control() {
  iteration++;
  if (iteration>=100) {
    iteration=0;
    if (isHigh) {
      isHigh=false;
      duty = dutyL;
    } else {
      isHigh=true;
      duty =  dutyH;
    }
  }
  
  unsigned int x = (unsigned int)motrpm;
  unsigned int y = (unsigned int )(100.0 * duty);
  unsigned int z = (unsigned int)motrpmf;
  Serial.write('H');
  Serial.write(x >> 8);
  Serial.write(x & 255);
  Serial.write(y >> 8);
  Serial.write(y & 255);
  Serial.write(z >> 8);
  Serial.write(z & 255);
  analogWrite(D6,duty*255);
  Serial.println((unsigned)motrpm);
}

void setup() {
  analogWrite(D6,dutyH*255);
  attachInterrupt(0,countUp,CHANGE);
  MsTimer2::set(Ts, control); // 40ms period
  MsTimer2::start();  
  Serial.begin(115200);
}

void loop() {}
