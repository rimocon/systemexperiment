const int LED_PIN = 3; //LED_PINを3と定義
void setup() {
  Serial.begin(9600);
  // シリアル通信を9600kbpsで初期化
  pinMode(LED_PIN,OUTPUT);
  //LED_PINを出力に設定
}
void loop() {
  int sensorValue = analogRead(A0);//A0ピンのAD変換結果を取得する.
  float vo = sensorValue*(5.0/1024.0);//デジタル値を電圧値に変換
  float L =222*vo; //電圧を照度値に変換
  Serial.println(L); //照度値をシステムモニタに表示
  digitalWrite(LED_PIN,lux_threshold(L)); //LED_PINポートにthresholdの戻り値を出力
  delay(1);      //安定用 
}

int lux_threshold(float lux){ //中間値用
  int th_val = 0;
  if(lux > 1.08){//中間値(1.08)より大きいなら
    th_val = HIGH; //LED点灯
  }
  else{ //そうでないなら
    th_val = LOW; //LED消灯
  }
  return th_val; //th_valを返す
}
