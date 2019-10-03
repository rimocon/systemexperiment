#include <ZumoMotors.h> //モータライブラリの読み込み
#include <Pushbutton.h> //ボタンライブラリの読み込み

const int trig = 2; //Trigピン2番
const int echo = 4; //Echoピン4番
const int buttonPin = 12; //ボタンピンは12番

unsigned long interval; //Echoのパルス幅(μs)
int distance; //距離(cm)

ZumoMotors motors; //ZumoMotorsクラスのインスタンス生成
Pushbutton button(ZUMO_BUTTON); //Pushbuttonクラスのインスタンスを生成

void setup() {
  Serial.begin(9600);
  pinMode(trig,OUTPUT); //trigを出力
  pinMode(echo,INPUT); //echoを入力
  button.waitForButton();
}

void loop() {
  //10μsのパルスを超音波センサのTrigピンに出力
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  interval = pulseIn(echo,HIGH,23068); //echoがhighである時間を計測
  distance = 340* interval / 10000/ 2; //距離(cm)に変換
  Serial.write(distance);

  //距離が10cm以下なら後進
  if( distance < 10 ){
    motors.setLeftSpeed(-100);
    motors.setRightSpeed(-100);
  }
  //距離が10cm以上なら前進
  if(distance > 10) {
    motors.setLeftSpeed(100);
    motors.setRightSpeed(100);
  }
  //距離が10cmなら停止
  if(distance == 10) {
    motors.setLeftSpeed(0);
    motors.setRightSpeed(0);
  }
  
  delay(60); 
}
