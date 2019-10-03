#include <ZumoMotors.h> //モータライブラリの読み込み
#include <Pushbutton.h> //ボタンライブラリの読み込み

ZumoMotors motors; //ZumoMotorsクラスのインスタンス生成
Pushbutton button(ZUMO_BUTTON); //Pushbuttonクラスのインスタンスを生成

const int buzzerPin = 3; //ブザーピンは3
const int buttonPin = 12; //ボタンピンは12
const int ledPin = 13; //ledピンは13
int v; //速度
int i; //繰り返し数

void setup() {
  i = 0;
  v = 100;
  pinMode(ledPin,OUTPUT); //13番ピンを出力モードに設定
  button.waitForButton(); //ユーザーボタンが押されるまで待機
}
void loop() {
  //3秒間時計回り
  motors.setLeftSpeed(v);
  motors.setRightSpeed(-v);
  tone(buzzerPin,200);
  delay(3000);
  noTone(buzzerPin);
  //0.5秒停止
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
  digitalWrite(ledPin,HIGH); //led点灯
  delay(500);
  digitalWrite(ledPin,LOW); //led消灯
  //3秒間半時計回り
  motors.setLeftSpeed(-v);
  motors.setRightSpeed(v);
  tone(buzzerPin,400);
  delay(3000);
  noTone(buzzerPin);
  //0.5秒停止
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
  digitalWrite(ledPin,HIGH); //led点灯
  delay(500);
  digitalWrite(ledPin,LOW); //led消灯
  //速度を100~200に変更
  i++; 
  if (i == 3) i =0;
  v = 100 + i*50;
}
