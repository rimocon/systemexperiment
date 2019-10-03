int sensorValue0, sensorValue1;
unsigned long int timeNow,timePrev;
int inByte; // Processing から の送信要求を 受け 取る 変数
void setup(){
  Serial.begin(9600);
}
void loop(){
  timeNow = millis();
  sensorValue0 = analogRead(0);
  if (Serial.available() > 0) {
    if ( timeNow - timePrev >= 50 ) {// 送信要求を 受け 取っ た ( 受信バッ フ ァ に データ あり )
      inByte = Serial.read(); // 受信済みの信号を 読み込む ( 受信バッ フ ァ が空に な る )
      Serial.write(252); //はじめの位置確認
      Serial.write(sensorValue0 / 0x20);
      Serial.write(sensorValue0 % 0x20);

      Serial.write(timeNow >> 28); //1byte目
      Serial.write(timeNow >> 21); //2byte目
      Serial.write(timeNow >> 14); //3byte目
      Serial.write(timeNow >> 7);  //4byte目
      Serial.write(timeNow && 127); //5byte目
      timePrev = timeNow;
    }
  }
  
}
