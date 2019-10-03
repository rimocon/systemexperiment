unsigned long timePrev = 0; //基準となる時間を格納

void flash() {
   static boolean output = HIGH;
   digitalWrite(13,output); //LEDをD13に出力設定
   output = !output; //HIGH->LOW,LOW->HIGH反転させる
}
void setup() {
  pinMode(13,OUTPUT); //13番ピンを出力ポートに設定
}

void loop() { //millis関数による時間計測
  unsigned long timeNow = millis(); //millis関数を用いて現在の時間情報を取得
  if(timeNow - timePrev >= 750){ //750ms以上経過
    flash(); //flash関数の処理を実行
    timePrev = timeNow; //時間情報の更新
  }
  else{}
}   
