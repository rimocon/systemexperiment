//値を定義
const int LED_PIN = 9;
void setup() {
  Serial.begin(9600);
  // シリアル通信を9600kbpsで初期化
  pinMode(LED_PIN,OUTPUT);
  //LED_PINを出力に設定 
}
void loop() {
  for(int i = 0; i <=204 ; i++){//80パーセントは204
     analogWrite(LED_PIN,i);//iをLED_PINに出力
     delay(1000/204);//204回で1秒
  }
  for(int j = 204; j>0 ; j--){
    analogWrite(LED_PIN,j);//iをLED_PINに出力
    delay(1000/204);//204回で1秒待つ
  }
}
