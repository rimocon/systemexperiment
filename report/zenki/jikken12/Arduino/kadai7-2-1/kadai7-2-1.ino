#include <Servo.h>
#include <MsTimer2.h>

Servo servo; //Servo クラスのインスタンス servo を生成
const int trig = 7; //Trig ピンに接続する Arduino のピン番号
const int echo = 8; //Echo ピンに接続する Arduino のピン番号
const int servoPin = 11; //サーボモータの信号線に接続する Arduino のピン番号
unsigned long interval; //Echo のパルス幅(μs)
int distance; //距離(cm)
int angle; //回す角度
float wait; //待機時間
boolean clockwise = false; //時計回りかどうか

void setup() {
  Serial.begin(9600); //シリアル通信を 9600bps で初期化
  pinMode(trig, OUTPUT); //trig を出力ポートに設定
  pinMode(echo, INPUT); //echo を入力ポートに設定
  servo.attach(servoPin); //制御の対象を servoPin に割り当て
  angle = 0;
  wait = 80;
  //15秒で180度回転したいので
  //1度回転ごとに15 / 180秒待てば良い
  MsTimer2::set(wait,anglechange);
  MsTimer2::start(); //タイマ割り込みスタート

  // 
}
void anglechange() {
  servo.write(angle); //角度をサーボモータに出力
  if (clockwise)  angle --; //時計回りなら角度を小さくしていく
  else {
    angle ++; //半時計回りなら角度を大きくしていく
  }
  if (angle == 180) clockwise = true; //角度が180に到達したら時計回りに変更
  if (angle == 0) clockwise = false; //角度が0に到達したら半時計回りにする
}

void loop() {
  digitalWrite(trig, HIGH); //10μs のパルスを超音波センサの Trig ピンに出力
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  interval = pulseIn(echo, HIGH, 3452); //Echo 信号が HIGH である時間(μs)を計測
  //0.61*25 + 331.5 = 346.75
  //346.75 * x * 100 / 2 = 60
  //x = 3452
  distance = 340 * interval / 10000 / 2; //距離(cm)に変換
  
  if (distance > 60 ) { //距離が60cmを超えたら60とする
    distance = 60;
  } 
  Serial.write('H'); //ハンドシェイク用の記号
  Serial.write(distance); //距離を送信,60までなので1byteでok
  Serial.write(angle); //角度を送信,180までなので1byteでok
  delay(60);
   //Trig を再度 HIGH にするまでに 60ms 以上の間隔をあける(HC-SR04 の仕様)
   //この処理をしない場合、動作が不安定になる
}
