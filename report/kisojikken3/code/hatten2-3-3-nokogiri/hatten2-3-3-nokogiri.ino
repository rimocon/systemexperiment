//値を定義
const int LED_PIN = 9;
void setup() {
  Serial.begin(9600);
  // シリアル通信を9600kbpsで初期化
  pinMode(LED_PIN,OUTPUT);
  //LED_PINを出力に設定 
}
void loop() {
  for(int i = 0; i < 256 ; i++){
    analogWrite(LED_PIN,i);//LED_PINにiを出力
    delay(1000/255);//255回で1秒待つ
  }
}
