int Luxsensor, Tempsensor;
long int Luxsum,Tempsum,count;
float Luxaverage,Tempaverage;
int intLuxaverage,intTempaverage;
unsigned long int timeNow,timePrev;
int byte1,byte2,byte3,byte4;
int inByte; // Processing から の送信要求を 受け 取る 変数
void setup(){
  Serial.begin(9600);
}
void loop(){
  if (Serial.available() > 0) {
    count = 0;
    Luxsum = 0;
    Tempsum = 0;
    while(1) {
      timeNow = millis();
      if ( timeNow - timePrev >= 50 ) { //50ms経つまで
      Luxsensor = analogRead(0);
      Tempsensor = analogRead(1);
      Luxsum += Luxsensor;
      Tempsum += Tempsensor;
      count ++;
      }
      else{
        break;
      }
    }
    Luxaverage = Luxsum / count;
    Tempaverage = Tempsum / count;
    intLuxaverage = (int)(Luxaverage * 100);
    intTempaverage = (int)(Tempaverage * 100);
    inByte = Serial.read(); // 受信済みの信号を 読み込む ( 受信バッ フ ァ が空に な る )
    Serial.write(252); //はじめの位置確認
    Serial.write(intLuxaverage / 0x20);
    Serial.write(intLuxaverage % 0x20);
    Serial.write(intTempaverage / 0x20);
    Serial.write(intTempaverage % 0x20);
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
  }
}
