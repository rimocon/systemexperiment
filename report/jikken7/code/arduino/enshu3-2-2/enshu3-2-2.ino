int high1,high2,low1,low2;
int sensorValue1,sensorValue2;
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
  high1 = sensorValue1 >> 8; //high1にsensorValue1の上位8ビットを代入
  low1 = sensorValue1 & 255; //low1にsensorValue1の下位8ビットを代入
  high2 = sensorValue2 >> 8; //high2にsensorValue2の上位8ビットを代入
  low2 = sensorValue2 & 255; //low2にsensorValue2の下位8ビットを代入
  if ( timeNow - timePrev >= 50 ) { // 50ms ごとに実行
    Serial.write('A');
    Serial.write(high1);
    Serial.write(low1);
    Serial.write(high2);
    Serial.write(low2);
    timePrev = timeNow; // 1 ステップ前の経過時間を更新
  }
}
