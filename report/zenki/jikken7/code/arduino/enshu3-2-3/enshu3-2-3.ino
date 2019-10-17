int sensorValue0;
unsigned long int timePrev, timeNow;
void setup()
{
	Serial.begin(9600); // シリアル通信を 9600bps で初期化
	timePrev = millis(); // 経過時間の初期値
}
void loop()
{
	timeNow = millis(); // 現在の経過時間 ( ms 単位)
	sensorValue0 = analogRead(0); // A0 ピンの AD 変換結果を取得 (0-1023)
	if ( timeNow - timePrev >= 50 ) { // 50ms ごとに実行
		Serial.write('H');
		Serial.write(timeNow >> 24); // 1byte 目
		Serial.write(timeNow >>16);
		// 2byte 目
		Serial.write(timeNow >> 8);
		// 3byte 目
		Serial.write(timeNow & 255); // 4byte 目
		Serial.write(sensorValue0 >> 8);
		// 上位 1byte
		Serial.write(sensorValue0 & 255);
		// 下位 1byte
		timePrev = timeNow; // 1 ステップ前の経過時間を更新
	}
}
