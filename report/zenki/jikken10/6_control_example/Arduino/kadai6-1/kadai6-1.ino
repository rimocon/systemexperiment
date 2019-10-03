//I-P制御
// 大域変数の定義
#include<MsTimer2.h>
//定義
const int D2 = 2;
const int D6 = 6;
const int D9 = 9;
//キャスト
 float duty = 0;
int Ts = 40; // サンプリング周期 [msec]
int iteration = 0;
unsigned long timep=0;
volatile float motrpm = 0;
volatile float motrpmf = 0;
volatile boolean isD2High=false;
//目標回転速度
float refL = 2000.0; // 目標回転速度 1[rpm]
float refH = 3000.0; // 目標回転速度 2[rpm]
float ref = refL; // 目標回転速度 [rpm]
boolean isrefHigh = false;
//I-P制御
float U0 = 0.2; // 動作点を duty 比 0.2 近傍とする
float Y0 = 1950.0; // U0=0.2 のときの定常的な回転速度 [rpm]
float sum_e = 0;
float Kp = 0.00004;
float Ki = 0.00016*0.5*((float)Ts/1000.0); // サンプリング周期をあらかじめ掛けておく

void countUp() {
  if ((isD2High)&&(digitalRead(D2)==LOW)) {
    unsigned long timen = millis();
    motrpm = 1000.0*60.0/(float)(timen-timep);
    motrpmf = (3.0*motrpmf+motrpm)/4.0;
    timep=timen;
    isD2High=false;
  } else if ((!isD2High)&&(digitalRead(D2)==HIGH)) {
    isD2High=true;
  }
}
void control() {
// タイマ割り込み (MsTimer2) の ISR 40[msec] ごと
  iteration++;
  if (iteration >= 100) {
    // 4[sec] ごとに
    // 目標値 ref の設定 ; 4[sec] ごとに refH, refL に交互に変更
    iteration = 0;
    if ( isrefHigh ){
      ref = refL;
      isrefHigh = false;
    }
    else {
      ref = refH;
      isrefHigh = true;
    }
  }
  // 制御入力の決定
  float e = ref-motrpmf; // 誤差
  sum_e += e; // 誤差の積分 ( 和分 )
  duty = Kp*(Y0-motrpmf)+Ki*sum_e+U0; // I-P 制御
  if (duty<0) {
    // duty 比を [0,0.5] に制限
    duty = 0.0;
  }
  if (duty>0.5) {
    duty = 0.5;
   }
  // データの送信
  unsigned int x = (unsigned int)motrpmf;
  unsigned int y = (unsigned int)(255.0 * duty);
  unsigned int z = (unsigned int)ref;
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
  analogWrite(D6,duty*255.0);
  attachInterrupt(0,countUp,CHANGE);
  MsTimer2::set(Ts,control); //40ms period
  MsTimer2::start();
  Serial.begin(115200);
}
void loop() {}
