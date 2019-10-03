int sensorValue0, sensorValue1;
unsigned long int timeNow,timePrev;
int inByte; // Processingからの送信要求を受け取る変数
const int LED = 13;
int byte1,byte2,byte3,byte4;
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
      byte1 = timeNow >> 28;
      byte2 = timeNow >> 21;
      byte3 = timeNow >> 14;
      byte4 = timeNow >> 7;
      Serial.write(byte1 & 0x7F); //1byte目
      Serial.write(byte2 & 0x7F); //2byte目
      Serial.write(byte3 & 0x7F); //3byte目
      Serial.write(byte4 & 0x7F);  //4byte目
      Serial.write(timeNow & 0x7F); //5byte目
      timePrev = timeNow;
      digitalWrite(LED,HIGH);
    }
  }
  if ( Serial.available() == 0) {
    digitalWrite(LED,LOW);
    if ( timeNow - timePrev >= 1000 ){  
      inByte = Serial.read(); // 受信済みの信号を 読み込む ( 受信バッ フ ァ が空に な る )
      Serial.write(252); //はじめの位置確認
      Serial.write(sensorValue0 / 0x20);
      Serial.write(sensorValue0 % 0x20);
      byte1 = timeNow >> 28;
      byte2 = timeNow >> 21;
      byte3 = timeNow >> 14;
      byte4 = timeNow >> 7;
      Serial.write(byte1 & 0x7F); //1byte目
      Serial.write(byte2 & 0x7F); //2byte目
      Serial.write(byte3 & 0x7F); //3byte目
      Serial.write(byte4 & 0x7F);  //4byte目
      Serial.write(timeNow & 0x7F); //5byte目
      timePrev = timeNow;
      digitalWrite(LED,HIGH);
    }
  }
}
