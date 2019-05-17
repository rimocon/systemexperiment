const int LED_RED_PIN = 13; //LED(赤)を13番ポートに定義
const int LED_YEL_PIN = 9; //LED(黄)を9番ポートに定義
int output_red = LOW; //赤色LEDへの出力用
int output_yel = LOW;
void setup() {
  pinMode(LED_RED_PIN,OUTPUT); //赤色LEDを出力として設定
  pinMode(LED_YEL_PIN,OUTPUT); //黄色LEDを出力として設定
  Serial.begin(9600); //シリアル通信開始:転送レート9600
}

void loop() {
  if(Serial.available()>0){ //パソコンからデータを受信
    int recv = Serial.read();
    recv -= 48; //数字に変換
    Serial.println(recv);
    if(recv == 0){ //'0'の場合
      output_red = HIGH;
      output_yel = LOW;
    }
    else if(recv == 1){ //'1'の場合
      output_red = LOW;
      output_yel = HIGH;
    }
    else if(recv == -38){ //改行コードが来た時
      //何もしない
    }
    else{
      output_red = HIGH;
      output_yel = HIGH;
    }
    //Serial.println("I received!"); //パソコンへ応答を返す(送信)
    Serial.print("LED1:");
    Serial.println(output_red);
    Serial.print("LED2:");
    Serial.println(output_yel);
    digitalWrite(LED_RED_PIN,output_red); //赤色LEDの点灯・消灯
    digitalWrite(LED_YEL_PIN,output_yel); //赤色LEDの点灯・消灯
  }
}
