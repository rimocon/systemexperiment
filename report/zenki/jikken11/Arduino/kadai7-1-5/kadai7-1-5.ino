#include<Servo.h> //サーボライブラリのインクルード

Servo servo; //Servoクラスのインスタンスを生成

const int servoPin = 10; //サーボモータの信号線をデジタル10番ピンに接続
int angle; //回す角度
int sensorvalue; //半固定抵抗の値
float wait; //待機時間
boolean clockwise = false; //時計回りかどうか
void setup() {
 servo.attach(servoPin); //制御の対象を10番ピンに割当
 Serial.begin(9600);
 angle = 0;
}

void loop() { 
  sensorvalue = analogRead(A0); //A0ピンのAD変換結果を取得(半固定抵抗の値)
  servo.write(angle);
  if (clockwise)  angle--; //時計回りなら角度を小さくしていく
  else {
    angle++; //半時計回りなら角度を大きくしていく
  }
  if (angle == 180) clockwise = true; //角度が180に到達したら時計回りに変更
  if (angle == 0) clockwise = false; //角度が0に到達したら半時計回りにする
  Serial.println(angle);
  Serial.println(sensorvalue);
  /*
  戻ってくるまでの回転は合計360度
  5秒で360度回転するということは
  1度の回転にかかる時間は5/360秒
  msに直すと
  5000/360ms ≒14ms
  18秒も同様に考えて
  18/360秒
  msに直して
  50ms
  */
  wait = map(sensorvalue,0,1023,14,50);// 0~1023のセンサの値を14~50に変換
  Serial.println(wait); //確認用
  delay(wait); //待ち時間(1度回転あたりの秒)
}
