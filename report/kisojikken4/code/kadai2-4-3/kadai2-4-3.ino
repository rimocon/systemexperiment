const int LED_PIN = 13; //LEDをD13に接続
volatile int output = LOW; //ディジタル出力の値を格納する変数:初期:LOW
/* 初期設定 */
void setup() {
  pinMode(LED_PIN,OUTPUT); //D13をディジタル出力に設定
  /*外部割り込みの設定
    割り込みに使用するディジタルポートをD2に設定(1番目の引数="0")
    割り込みサービスルーチンblink関数を実行(2番目の引数=関数名)
    (例)割り込み要因としてスイッチの状態が"LOW"のときに発生(3番目の引数)
   */
   attachInterrupt(0,blink,LOW);
}

void loop() {
  digitalWrite(LED_PIN,output); //スイッチを押すたびに点灯・消灯を繰り返す
}

void blink() { //割り込みの条件にあわせLEDが点灯・消灯を繰り返す
  output = !output; //ディジタル出力を反転
}
