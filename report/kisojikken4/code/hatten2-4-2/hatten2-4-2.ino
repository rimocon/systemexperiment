#include <MsTimer2.h>
const int LED1_PIN = 13; //13番ピンにLEDを接続
const int LED2_PIN = 9; //9番ピンにLEDを接続
int flag10000 = 0; //10秒経過flag
int flag500 = 0; //500ms経過flag
int flag100 = 0; //100ms経過flag
int output = LOW;
unsigned long timePrev = 0; //基準となる時間を格納

void check() { //割り込みサービスルーチン(LEDの点滅)
  int sensorvalue = analogRead(A0); //A0ピンのAD変換結果を取得
  float vo = sensorvalue*(5.0/1024.0);
  float L =222*vo; //照度値に変換
  Serial.println(L); //シリアルモニタに表示
  digitalWrite(LED1_PIN,LOW);
  else { //そうでないなら
    digitalWrite(LED2_PIN,LOW); //LED2_PINは消灯
  }
}
void setup() {
  Serial.begin(9600); //シリアル通信を9600kbpsで初期化
  pinMode(LED1_PIN, OUTPUT); //13番ピンを出力ポートに設定
  pinMode(LED2_PIN,OUTPUT); //9番ピンを出力ポートに設定
}

void loop() { //ボーリング処理
  
  unsigned long timeNow = millis(); //millis関数を用いて現在の時間情報を取得
  if(timeNow - timePrev >= 10000){ //10秒経過
    timePrev = timeNow; //時間情報の更新
    flag10000 = 1; //10秒経過を知らせる
  }
  if(flag10000 = 1){
    digitalWrite(LED2_PIN,HIGH); //LED2_PINを点灯させる
    flag10000 = 0; //flag初期化
  }

}
