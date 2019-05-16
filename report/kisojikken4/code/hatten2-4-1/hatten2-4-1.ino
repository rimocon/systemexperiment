#include <MsTimer2.h>
const int LED1_PIN = 13; //13番ピンにLEDを接続
const int LED2_PIN = 9; //9番ピンにLEDを接続
volatile int flag = 0; //10秒経過flag
int output = LOW;
unsigned long timePrev10 = 0; //基準となる時間を格納(10秒用)
unsigned long timePrev500 = 0; //基準となる時間を格納(500ms用)
void check() { //割り込みサービスルーチン(LEDの点滅)
  int sensorvalue = analogRead(A0); //A0ピンのAD変換結果を取得
  float vo = sensorvalue*(5.0/1024.0);
  float L =222*vo; //照度値に変換
  Serial.println(L); //シリアルモニタに表示
  if ( flag == 1){ //10秒経過したら
    digitalWrite(LED2_PIN,HIGH); //LED2_PINを点灯させる
    flag = 0; //flag初期化
  }
  else { //そうでないなら
    digitalWrite(LED2_PIN,LOW); //LED2_PINは消灯
  }
   digitalWrite(LED1_PIN,LOW);
}
void setup() {
  Serial.begin(9600); //シリアル通信を9600kbpsで初期化
  pinMode(LED1_PIN, OUTPUT); //13番ピンを出力ポートに設定
  pinMode(LED2_PIN,OUTPUT); //9番ピンを出力ポートに設定
  MsTimer2::set(1000, check); // タイマ割り込み間隔の設定(500ms)
  MsTimer2::start(); //タイマ割り込み開始
}

void loop() { //ボーリング処理
  
  unsigned long timeNow10 = millis(); //millis関数を用いて現在の時間情報を取得
  if((timeNow10 - timePrev10) >= 10000){ //10秒経過
    timePrev10 = timeNow10; //時間情報の更新
    flag = 1; //10秒経過を知らせる
  }
  if((millis() - timePrev500) >= 500){
     digitalWrite(LED1_PIN,output);
     timePrev500 = millis();
     output = !output
  }
}
