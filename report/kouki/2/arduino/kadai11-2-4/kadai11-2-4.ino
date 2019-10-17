#include <ZumoMotors.h> //モータライブラリの読み込み
#include <Pushbutton.h> //ボタンライブラリの読み込み


const int buttonPin = 12; //ボタンピンは12番
int state;
ZumoMotors motors; //ZumoMotorsクラスのインスタンス生成
Pushbutton button(ZUMO_BUTTON); //Pushbuttonクラスのインスタンスを生成

void setup() {
  Serial.begin(9600);
  button.waitForButton();
  state = 0; //回転中かどうか判断するための変数
}

void loop() {
  if(Serial.available() >= 1){
    if(Serial.read() == 'H'){
      state = 1; //回転を始める(1)
    }
  }
  if (state == 1) {
    //回転
    motors.setLeftSpeed(-150);
    motors.setRightSpeed(150);
    delay(1000);
    state = 0; 
    //回転終わりをprocessingに報告
    Serial.println("end");
  }
}
