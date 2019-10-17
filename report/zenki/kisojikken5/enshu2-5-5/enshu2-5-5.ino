int output = LOW; //LEDへの出力用
void setup() {
  pinMode(13,OUTPUT); //13ピンにLEDを出力として設定
  Serial.begin(9600); //シリアル通信開始:転送レート9600
}

void loop() {
  if(Serial.available()>0){ //パソコンからデータを受信
    int recv = Serial.read();
    output = !output; //outputの反転
    Serial.println("I received!"); //パソコンへ応答を返す(送信)
  }
  digitalWrite(13,output); //LEDの点灯・消灯
}
