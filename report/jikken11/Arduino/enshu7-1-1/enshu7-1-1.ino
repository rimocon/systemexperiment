const int trig = 7; //Trigピンをデジタル7番に接続
const int echo = 8; //Echoピンをデジタル8番に接続
unsigned long interval; //Echoのパルス幅
void setup() {
  Serial.begin(9600); //シリアルポートを9600kbpsに設定
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
  interval = pulseIn(echo,HIGH,10000); 
  Serial.println(interval); //超音波の往復時間をシリアルモニタに表示
  delay(60); //次のTrig信号の出力まで60ms待機
}
