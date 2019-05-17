const int LED_PIN = 9; //LEDをD9に定義
volatile int flag = LOW; //フェードイン,フェードアウト判定用の変数を用意
int i = 0;
unsigned long timePrev = 0;//時間を格納
/* 初期設定 */
void setup() {
  pinMode(LED_PIN,OUTPUT); //D9を出力に設定
  /*外部割り込みの設定
    割り込みに使用するディジタルポートをD2に設定(1番目の引数="0")
    割り込みサービスルーチンblink関数を実行(2番目の引数=関数名)
    (例)割り込み要因としてスイッチの状態が"LOW"のときに発生(3番目の引数)
   */
   attachInterrupt(0,blink,FALLING);
}

void loop() {
  if ( flag == LOW ){
    if( i == 255 ){
      i = 0;
    }
    analogWrite(LED_PIN,i);
    i++;
	 timePrev = millis();
	 while(millis() - timePrev <= 3000/255){
		 //3000/255秒待つ
	 }
  }
   else{
    if( i == 0 ){
      i = 255;
    }
    analogWrite(LED_PIN,i);
    i--;
	 timePrev = millis();
	 while(millis() - timePrev <= 3000/255){
		 //3000/255秒待つ
	 }
  }
}
void blink() { //割り込みの条件にあわせLEDがフェードイン・フェードアウトを繰り返す
  flag = !flag;
} 
