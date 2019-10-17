unsigned long timePrev = 0;
int count = 0;
double average = 0;
double sum= 0;
void SendData(){
  Serial.println(average);
  count++;
}
void setup() {
  Serial.begin(9600);
  Serial.println("start!");
  timePrev = millis();
}

void loop() {
  if(count < 100){
    double sum = 0; //合計格納用変数
    long int i = 0; //合計測定回数格納用変数
    while (1){//100ms経つまで
      unsigned long timeNow = millis(); //現在時間を格納
      if(timeNow - timePrev <= 100){ //100ms経つまで
        int sensorValue = analogRead(A0); //A0の値を格納
        double vo = sensorValue*(5.0/1024.0);
        double Temp = (vo*1000.0 - 600.0)/10.0;
        sum += Temp;
        i++;
      }
      else{
        timePrev = timeNow;
        break;
      }
   }
   average = sum / i;
   SendData();
  }
}
