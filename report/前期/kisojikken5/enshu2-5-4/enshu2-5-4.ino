void setup() {
  Serial.begin(9600); //転送レート9600に設定
}

void loop() {
  int sensorValue = analogRead(A0);//A0ピンのAD変換結果を取得する.
  float vo = sensorValue*(5.0/1024.0);
  float Temp = (vo*1000.0 - 600.0)/10.0; //電圧を温度に変換
  Serial.print(sensorValue); //センサの値
  Serial.print(","); //,を表示
  Serial.print(vo); //電圧
  Serial.print(","); //,を表示
  Serial.println(Temp); //温度を表示
}
