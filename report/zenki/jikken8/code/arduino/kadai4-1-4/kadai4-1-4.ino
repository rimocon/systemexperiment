int Luxsensor, Tempsensor;
long int Luxsum,Tempsum,count;
float Luxaverage,Tempaverage;
unsigned int intLuxaverage,intTempaverage;
unsigned long int timeNow,timePrev;
int byte1,byte2,byte3,byte4;
int inByte; // Processing から の送信要求を 受け 取る 変数
void setup(){
  Serial.begin(9600);
  timePrev = millis();
  Luxsum = 0;
  Tempsum = 0;
  count = 0;
}
void loop(){
    timeNow = millis();
    Luxsensor = analogRead(0);
    Tempsensor = analogRead(1);
    if ( (timeNow - timePrev) <= 50 ) { //50ms経つまで
        Luxsum += Luxsensor;
        Tempsum += Tempsensor;
        count ++;
    }
    else {
    Luxaverage = (float)Luxsum / (float)count *100;
    Tempaverage = (float)Tempsum / (float)count *100;
    intLuxaverage = (int)(Luxaverage);
    intTempaverage = (int)(Tempaverage);
    inByte = Serial.read();
    Serial.write(0x20); //はじめの位置確認
    Serial.write(intLuxaverage / 0x50);
    Serial.write(intLuxaverage % 0x50);
    Serial.write(intTempaverage / 0x50);
    Serial.write(intTempaverage % 0x50);
    /*
    Serial.println(Tempaverage);
    Serial.println(Luxaverage);
    Serial.println(intTempaverage);
    Serial.println(intLuxaverage);
    */
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
    count = 0;
    Luxsum = 0;
    Tempsum = 0; 
    }
}
