//それぞれのポート番号を定義
const int LED_RED_PIN = 9;
const int LED_YEL_PIN = 11;
void setup() {
  Serial.begin(9600);
  // シリアル通信を9600kbpsで初期化
  pinMode(LED_RED_PIN,OUTPUT);
  pinMode(LED_YEL_PIN,OUTPUT);
  //LEDのポートをそれぞれ出力に設定
}
void loop() {
  for(int i = 0; i <= 256; i+=64){
    if(i==256){//256は引数にならないので
      i--;
    }
    analogWrite(LED_RED_PIN,i);//それぞれにiを出力
    analogWrite(LED_YEL_PIN,i);//それぞれにiを出力
    delay(1000);//1秒待つ
  }
}
