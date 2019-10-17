#include <ZumoMotors.h> //モータライブラリの読み込み
#include <Pushbutton.h> //ボタンライブラリの読み込み

const int buttonPin = 12; //ボタンピンは12番
boolean circle = false;
boolean triangle = false;
boolean rectangle = false;

ZumoMotors motors; //ZumoMotorsクラスのインスタンス生成
Pushbutton button(ZUMO_BUTTON); //Pushbuttonクラスのインスタンスを生成

void setup() {
  button.waitForButton();
  circle = true;
}

void loop() {
  //四角形の場合
  if(rectangle){
    motors.setLeftSpeed(150);
    motors.setRightSpeed(150);
    delay(2000);
    motors.setLeftSpeed(150);
    motors.setRightSpeed(-150);
    delay(800);
    if(button.isPressed()){
      circle = false;
      triangle = true;
      rectangle = false;
    }
  }
  //三角形の場合
  if(triangle){
    motors.setLeftSpeed(150);
    motors.setRightSpeed(150);
    delay(2000);
    motors.setLeftSpeed(150);
    motors.setRightSpeed(-150);
    delay(1100);
  }
  //円形の場合
  if(circle){
    motors.setLeftSpeed(200);
    motors.setRightSpeed(30);
    if(button.isPressed()){
      circle = false;
      triangle = false;
      rectangle = true;
    }
  }
}
