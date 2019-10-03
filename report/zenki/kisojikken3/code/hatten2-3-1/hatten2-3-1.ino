//値を定義
const int buzzer = 9;
void setup() {
  Serial.begin(9600);
  // シリアル通信を9600kbpsで初期化
  pinMode(buzzer,OUTPUT);
  //buzzerを出力に設定
}
void loop() {
  for(int i = 0; i <= 256; i+=64){
    if(i==256){//256は引数にならないので
      i--;
    }
    analogWrite(buzzer,i);//buzzerに出力
    delay(1000);//1秒待つ
  }
}
