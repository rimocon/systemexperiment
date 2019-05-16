const int LED_PIN = 3;
void setup() {
  Serial.begin(9600);
  // シリアル通信を9600kbpsで初期化
  pinMode(LED_PIN,OUTPUT);
  //LED_PINを出力に設定
}
void loop() {
  int sensorValue = analogRead(A0);//A0ピンのAD変換結果を取得する.
  float vo = sensorValue*(5.0/1024.0);//sensorValueの値を電圧値に変換
  Serial.println(vo);//システムモニタにvoを表示
  delay(1);        // 安定用
  if(vo>2.50){//2.5V以上なら
    digitalWrite(LED_PIN,HIGH);//LED点灯
  }
  else{//2.5V以下なら
    digitalWrite(LED_PIN,LOW);//LED消灯
  } 
}
