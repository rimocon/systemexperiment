#include <Servo.h>

Servo servo; //Servo クラスのインスタンス servo を生成
const int trig = 7; //Trig ピンに接続する Arduino のピン番号
const int echo = 8; //Echo ピンに接続する Arduino のピン番号
const int servoPin = 11; //サーボモータの信号線に接続する Arduino のピン番号
unsigned long interval; //Echo のパルス幅(μs)
int distance; //距離(cm)

void setup() {
  Serial.begin(9600); //シリアル通信を 9600bps で初期化
  pinMode(trig, OUTPUT); //trig を出力ポートに設定
  pinMode(echo, INPUT); //echo を入力ポートに設定
  servo.attach(servoPin); //制御の対象を servoPin に割り当て
}

void loop() {
  digitalWrite(trig, HIGH); //10μs のパルスを超音波センサの Trig ピンに出力
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  interval = pulseIn(echo, HIGH, 5767); //Echo 信号が HIGH である時間(μs)を計測
  distance = 340 * interval / 10000 / 2; //距離(cm)に変換
  if (0 < distance && distance < 10) {
    servo.write(90); //距離が 10cm 未満ならば、サーボモータを 90 度に回転
    } else {
    servo.write(0); //距離が 10cm 以上ならば、サーボモータを 0 度に回転
  }
  if (0 < distance && distance < 50) {
    Serial.write(distance); //距離 50cm 未満ならシリアルポートへ送信(Processing へ送信)
    } else {
    Serial.write(50);
    //距離 50cm 以上なら 50 をシリアルポートへ送信
  }
  delay(60);
   //Trig を再度 HIGH にするまでに 60ms 以上の間隔をあける(HC-SR04 の仕様)
   //この処理をしない場合、動作が不安定になる
}
