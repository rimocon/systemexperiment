const int trig = 7; //Trigピンをデジタル7番に接続
const int echo = 8; //Echoピンをデジタル8番に接続
const int buzzer = 9; //圧電ブザーピンをデジタル9番に接続
const int led = 4; //ledピンをデジタル4番に接続
unsigned long interval; //Echoのパルス幅
unsigned long velocity; //音の速度
unsigned long distance; //対象までの距離
unsigned long frequency; //出力する周波数
void setup() {
  Serial.begin(9600); //シリアルポートを9600kbpsに設定
  velocity = (0.61 * 25 + 331.5) *100; //音の速度(cm/s)を計算
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}

void loop() {
  //10μsのパルスをTrigピンに出力
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  //Echo信号がHIGHである時間(μs)をpulseIn関数で計測
  //10000μs以上経過したら,超音波が反射して帰ってこないとみなして0を返す
  //距離が100cm以上の時は0を返す
  //0.61 * 25 + 331.5 = 346.75
  //346.75 * x*100/2 = 100.0
  //x = 5768 
  interval = pulseIn(echo,HIGH,10000); 
  //
  distance = (velocity * interval / 1000000 ) / 2 ; //距離を計算(cm)
  //Serial.println(interval); //超音波の往復時間をシリアルモニタに表示
  Serial.println(distance); //距離をシリアルモニタに出力
  if (distance <= 10) {
    digitalWrite(led,HIGH); //10cm以内ならled点灯
  }
  else {
    digitalWrite(led,LOW); //10cm以上ならled消灯
  }
  //距離が30を超えてたら30にする
  if( distance >= 30) distance = 30;
  //距離が0cmの時1000Hz,30cmの時100
  frequency = 1000 - (distance * 30); 
  tone (buzzer, frequency);
  delay(60); //次のTrig信号の出力まで60ms待機
}
