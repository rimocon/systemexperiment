#include <ZumoMotors.h> //モータライブラリの読み込み

const int trig = 2;
const int echo = 4;
unsigned long interval;
int distance;

ZumoMotors motors; 

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  //10μs のパルスを超音波センサの Trig ピンに出力
  interval = pulseIn(echo, HIGH, 23068);
  distance = 340 * interval / 10000 / 2;
  Serial.println(distance);
  if (distance < 10) {
    motors.setLeftSpeed(0);
    motors.setRightSpeed(0);
  } else {
    motors.setLeftSpeed(100);
    motors.setRightSpeed(100);
  }
  delay(60); //trig が HIGH になる間隔を 60ms 以上空ける
}
