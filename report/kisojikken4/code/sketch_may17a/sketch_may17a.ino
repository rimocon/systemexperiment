const int LED1_PIN = 13; //13番ピンにLEDを接続
const int LED2_PIN = 9; //9番ピンにLEDを接続
int output = LOW;
int flag = 0;
unsigned long timePrev1 = 0; //基準となる時間を格納(10秒用)
unsigned long timePrev10 = 0; //基準となる時間を格納(10秒用)
unsigned long timePrev500 = 0; //基準となる時間を格納(500ms用)
unsigned long timePrev1000 = 0; //基準となる時間を格納(1000ms用)
void setup() {
  Serial.begin(9600); //シリアル通信を9600kbpsで初期化
  pinMode(LED1_PIN, OUTPUT); //13番ピンを出力ポートに設定
  pinMode(LED2_PIN,OUTPUT); //9番ピンを出力ポートに設定
}
void loop() { //ボーリング処理
  if((millis() - timePrev10) >= 10000){ //10秒経過
    timePrev10 = millis(); //時間情報の更新
    flag = 1; //10秒経過フラグ
  }
  if((millis() - timePrev500) >= 500){ //500ms経過
    output =!output;
    digitalWrite(LED1_PIN,output);
    timePrev500 = millis();
  }
  if((millis() - timePrev1000) >= 1000){ //1000ms経過
    int sensorvalue = analogRead(A0); //A0ピンのAD変換結果を取得
    float vo = sensorvalue*(5.0/1024.0);
    float L =222*vo; //照度値に変換
    Serial.println(L); //シリアルモニタに表示
    delay(1);
    timePrev1000 = millis();
    if ( flag == 1){ //10秒経過したら
      digitalWrite(LED2_PIN,HIGH); //LED2_PINを点灯させる
      flag = 0; //値を初期化
    }
    else { //そうでないなら
      digitalWrite(LED2_PIN,LOW); //LED2_PINは消灯
    }
  }
}
