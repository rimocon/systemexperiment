unsigned long timePrev = 0; //基準となる時間を格納

void check() {
  static int sensorvalue = analogRead(A0); //A0ピンのAD変換結果を取得
  Serial.println(sensorvalue);
}
void setup() {
  Serial.begin(9600); //シリアル通信を9600kbpsで初期化
  pinMode(13,OUTPUT); //13番ピンを出力ポートに設定
}

void loop() { //millis関数による時間計測
  unsigned long timeNow = millis(); //millis関数を用いて現在の時間情報を取得
  if(timeNow - timePrev >= 500){ //500ms以上経過
    check(); //check関数の処理を実行
    timePrev = timeNow; //時間情報の更新
  }
  else{}
}   
