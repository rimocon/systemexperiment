#include <MsTimer2.h>

void flash() { //割り込みサービスルーチン(LEDの点滅)
  static boolean output = HIGH;
  
  digitalWrite(13, output); //LEDのD13の出力設定
  output = !output; //HIGH->LOW,LOW->HIGH反転させる
}

void setup() {
  pinMode(13, OUTPUT); //13番ピンを出力ポートに設定

  MsTimer2::set(500, flash); // タイマ割り込み間隔の設定(500ms)
  MsTimer2::start(); //タイマ割り込み開始
}

void loop() { //ボーリングによるタスクなし
}
