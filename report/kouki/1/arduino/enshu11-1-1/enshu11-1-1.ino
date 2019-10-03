#include <ZumoMotors.h> //モータライブラリの読み込み

ZumoMotors motors; //ZumoMotorsクラスのインスタンスを生成

void setup() {}
void loop() {
  //前進
  motors.setLeftSpeed(100); //左モータの速度100(-400~400で設定可能)
  motors.setRightSpeed(100); //右モータの速度100(-400~400で設定可能)
  delay(1000);
  //停止
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
  delay(1000);
  //後進
  motors.setLeftSpeed(-100);
  motors.setRightSpeed(-100);
  delay(1000);
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
  delay(1000);
}
