const int LED_PIN = 3;
void setup() {
  // シリアル通信を9600kbpsで初期化
  Serial.begin(9600);
  pinMode(LED_PIN,OUTPUT);
}
void loop() {
  int sensorValue = analogRead(A0);//A0ピンのAD変換結果を取得する.
  float vo = sensorValue*(5.0/1024.0);
  float L =222*vo;
  Serial.println(L);
  delay(1);        // delay in between reads for stability
}
