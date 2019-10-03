#include <MsTimer2.h>
const int LED1_PIN = 13; //13番ピンにLEDを接続
const int LED2_PIN = 9; //9番ピンにLEDを接続

void flash() { //割り込みサービスルーチン(LEDの点滅)
  for ( int i = 255; i >= 0 ; i--){ //発光状態から消灯状態へ
    analogWrite(LED2_PIN,i); //LED2_PINにPWM出力
    delay(5000/256); //256回(発光->消灯間5000ms)
  }
  
}

void setup() {
  pinMode(LED1_PIN, OUTPUT); //13番ピンを出力ポートに設定
  pinMode(LED2_PIN,OUTPUT); //9番ピンを出力ポートに設定
  MsTimer2::set(20, flash); // タイマ割り込み間隔の設定(500ms)
  MsTimer2::start(); //タイマ割り込み開始
}

void loop() { //ボーリング処理
  digitalWrite(LED1_PIN,HIGH); //13番ピンに5V出力
  delay(500); //500ms待機
  digitalWrite(LED1_PIN,LOW); //13番ピンに0V出力
  delay(500); //500ms待機
}
