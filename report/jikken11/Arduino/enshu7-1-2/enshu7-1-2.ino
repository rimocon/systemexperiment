#include<Servo.h> //サーボライブラリのインクルード

Servo servo; //Servoクラスのインスタンスを生成

const int servoPin = 10; //サーボモータの信号線をデジタル10番ピンに接続

void setup() {
 servo.attach(servoPin); //制御の対象を10番ピンに割当
 Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0 ) {
    char val = (char)Serial.read(); //文字の読み込み
    switch (val) {
      case 'a':
        servo.write(0); //0度まで回転
        Serial.println("0度");
        break;
      case 'b':
        servo.write(90); //90度まで回転
        Serial.println("90度");
        break;
      case 'c':
        servo.write(180); //180度まで回転
        Serial.println("180度");
        break;
      case '\n': //エンターキーが入ってしまうので除去
        Serial.println("Enter"); //確認
        break;
      default:
        servo.write(0);
        Serial.println("default");
    }
  }
}
