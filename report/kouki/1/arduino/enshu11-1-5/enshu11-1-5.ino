#include <ZumoMotors.h> //モータライブラリの読み込み

ZumoMotors motors; //ZumoMotors クラスのインスタンス生成

void setup() {
  Serial.begin(9600);
}
void loop() {
  //前進
  Serial.write(0);
  motors.setLeftSpeed(100);
  motors.setRightSpeed(100);
  delay(1000);
  //後進
  Serial.write(1);
  motors.setLeftSpeed(-100);
  motors.setRightSpeed(-100);
  delay(1000);
}
