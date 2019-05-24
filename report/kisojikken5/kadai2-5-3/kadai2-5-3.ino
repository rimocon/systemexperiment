unsigned long timePrev = 0;
int count = 0;
double average = 0;
double sum = 0;
int output = 0;
const int LED_PIN = 9; //9番ポートをLEDに設定
void SendData(){
  Serial.println(average);
  count++;
}
void setup() {
  analogWrite(LED_PIN,OUTPUT);
  Serial.begin(9600);
  Serial.println("start!");
  timePrev = millis();
}

void loop() {
  if(count < 30){ //15秒経つまで(500ms×30)
    double sum = 0; //合計格納用変数
    long int i = 0; //合計測定回数格納用変数
    while (1){//500ms経つまで
      unsigned long timeNow = millis(); //現在時間を格納
      if(timeNow - timePrev <= 500){ //500ms経つまで
        int sensorValue = analogRead(A0); //A0の値を格納
        double vo = sensorValue*(5.0/1024.0);
        double L = 222*vo;
        sum += L;
        i++;
      }
      else{
        timePrev = timeNow;
        break;
      }
   }
   average = sum / i; 
   SendData();
   output = int(average*255);
   if(output > 255){
    output = 255;
   }
   analogWrite(LED_PIN,output); //照度1で255(MAX)出力
  }
}
