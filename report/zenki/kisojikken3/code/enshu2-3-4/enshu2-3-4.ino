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
    analogWrite(LED_RED_PIN,64);//赤色に25％出力
    analogWrite(LED_YEL_PIN,192);//黄色に75％出力
    delay(10);//安定用
  }
}
