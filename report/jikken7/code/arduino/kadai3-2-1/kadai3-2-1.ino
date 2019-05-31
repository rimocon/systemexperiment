int sensorValue0; //センサの読み込んだ値(0~1023)
unsigned long int timePrev, timeNow;
int count; //足しこんだ回数
long int sum; //足しこんだ合計
float average; //50ms間の平均値
int intaverage;
void setup()
{
	Serial.begin(9600); // シリアル通信を 9600bps で初期化
	timePrev = millis(); // 経過時間の初期値
}
void loop()
{
  count = 0; //初期化
  sum = 0; //初期化
  while(1){
    timeNow = millis(); //現在時間を格納
    if(timeNow - timePrev <= 50){ //50ms経つまで
       int sensorValue0 = analogRead(A0); //A0の値を格納
       //double vo = sensorValue*(5.0/1024.0);
       //double Temp = (vo*1000.0 - 600.0)/10.0;
       sum += sensorValue0;
       count++;
    }
    else{
      break;
    }
  }
  average = (float)sum / (float)count;
  intaverage = (int)(average * 100);
  Serial.println(intaverage);
	Serial.write('H');
	Serial.write(timeNow >> 24); 
	// 1byte 目
	Serial.write(timeNow >>16);
	// 2byte 目
	Serial.write(timeNow >> 8);
	// 3byte 目
	Serial.write(timeNow & 255);
	// 4byte 目
	Serial.write( intaverage >> 8 );
	// 上位 1byte
	Serial.write( intaverage & 255);
	// 下位 1byte
  timePrev = timeNow; //時間の更新
}
