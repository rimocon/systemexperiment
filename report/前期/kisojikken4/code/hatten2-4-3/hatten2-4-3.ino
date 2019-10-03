const int LED_PIN = 13; //LEDをD13に定義
const int SW_PIN = 2; //SWITCHをD2に定義
volatile int swnow;
volatile int swprev;
unsigned long timePrev = 0; //基準となる時間を格納
volatile int output = LOW; //ディジタル出力の値を格納する変数:初期:LOW
/* 初期設定 */
void setup() {
  pinMode(LED_PIN,OUTPUT); //D13をディジタル出力に設定
  pinMode(SW_PIN,INPUT);
  /*外部割り込みの設定
    割り込みに使用するディジタルポートをD2に設定(1番目の引数="0")
    割り込みサービスルーチンblink関数を実行(2番目の引数=関数名)
    (例)割り込み要因としてスイッチの状態が"LOW"のときに発生(3番目の引数)
   */
   attachInterrupt(0,blink,FALLING);
}

void loop() {
  swnow = digitalRead(SW_PIN);
  swprev = digitalRead(SW_PIN);
  if(swprev == LOW || swnow == HIGH){
    timePrev = millis();
    while(millis() - timePrev >= 10){
      //10ms待つ
    }
  }
  digitalWrite(LED_PIN,output); //スイッチを押すたびに点灯・消灯を繰り返す
}

void blink() { //割り込みの条件にあわせLEDが点灯・消灯を繰り返す
  timePrev = millis();
  output = !output; //ディジタル出力を反転
  while(millis()-timePrev >= 10 ){
    //10ms待つ
  }
}
