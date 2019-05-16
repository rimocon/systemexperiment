const int LED_RED_PIN = 3;//LED_RED_PINを3に定義
const int LED_YEL_PIN = 13;//LED_YEL_PINを13に定義
const int SW_PIN = 4; //SW_PINを4に定義
int sw1;//スイッチの入力保存用
void setup() {
  pinMode(LED_RED_PIN,OUTPUT);//LED_RED_PINを出力に設定
  pinMode(LED_YEL_PIN,OUTPUT);//LED_YEL_PINを出力に設定
  pinMode(SW_PIN,INPUT);//SW_PINを入力に設定
}
void loop() {
  sw1=digitalRead(SW_PIN);//sw1にSW_PINの値を保存
  if(sw1==LOW){//スイッチがONなら
    digitalWrite(LED_RED_PIN,HIGH);//赤をHIGH
    digitalWrite(LED_YEL_PIN,LOW);//黄色をLOW
  }
  else{
    digitalWrite(LED_RED_PIN,LOW);//赤をLOW
    digitalWrite(LED_YEL_PIN,HIGH);//黄色HIGH
  }
}
