//値を定義
const int LED_PIN = 9;
void setup() {
  Serial.begin(9600);
  // シリアル通信を9600kbpsで初期化
  pinMode(LED_PIN,OUTPUT);
  //LEDを出力に設定
}
void loop() {
  int sensorValue = analogRead(A0);//A0ピンのAD変換結果を取得する.
  float vo = sensorValue*(5.0/1024.0);//デジタル値を電圧値に変換
  float L =222*vo;//電圧を照度値に変換
  Serial.println(L);//照度値をシステムモニタに表示
  analogWrite(LED_PIN,convert(L,0.0,2.17));//LED_PINポートにconvertの戻り値を出力
  delay(1);   //安定用
}

int convert(float lux,float lux_min,float lux_max){
  float out = lux/(lux_min - lux_max) *255;
  //照度値をPWMの出力に変換
  return out;//outを返す
}
