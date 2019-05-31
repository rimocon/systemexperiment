int sensorValue1,sensorValue2,sendValue1,sendValue2;
unsigned long int timePrev, timeNow;
void setup()
{
  Serial.begin(9600); // シリアル通信を 9600bps で初期化
  timePrev = millis(); // 経過時間の初期値
}
void loop()
{
  timeNow = millis(); // 現在の経過時間
  sensorValue1 = analogRead(0); // A0 ピンの AD 変換結果を取得 (0-1023)
  sensorValue2 = analogRead(1); // A1 ピンの AD 変換結果を取得 (0-1023)
  if ( timeNow - timePrev >= 50 ) { // 50ms ごとに実行
    sendValue1 = sensorValue1 /4; // 0-255 の値に変換
    sendValue2 = sensorValue2 /4; // 0-255 の値に変換
    Serial.write('A');
    Serial.write(sendValue1); // 1 バイトのバイナリデータとして値を送信
    Serial.write(sendValue2); // 1 バイトのバイナリデータとして値を送信
    timePrev = timeNow; // 1 ステップ前の経過時間を更新
  }
}
