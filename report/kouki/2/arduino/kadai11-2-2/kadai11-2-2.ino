#include <ZumoMotors.h>           // Zumo用モータ制御ライブラリの読み込み
#include <Pushbutton.h>           // Zumo用ユーザボタンライブラリの読み込み
#include <Wire.h>                 // I2C/TWI 通信デバイスの制御用ライブラリの読み込み

unsigned long int timeStart = 0;  // 時間計測用変数
unsigned long int timeEnd = 0;    // 時間計測用変数

int cnt = 0;                      // 送信回数の確認用カウンタ

Pushbutton button(ZUMO_BUTTON);

void setup()
{
  Serial.begin(9600);             // シリアル通信の初期化
  Wire.begin();                   // Wireライブラリの初期化と，I2Cバスとの接続
  
  button.waitForButton();         // ユーザボタンが押されるまで待つ
  Serial.println("START");        // 文字列をシリアル送信
}

void loop()
{
  button.waitForButton();         // ユーザボタンが押されるまで待つ
  //millis
  /*
  timeStart = millis();           // 現在の時間取得
  Serial.write("a");
  timeEnd = millis();             // 現在の時間取得
  
  delay(50); // 50ms待つ
  Serial.print("write millis =");
  Serial.println(timeEnd-timeStart);    // 経過時間をシリアル送信
  
  timeStart = millis();           // 現在の時間取得
  Serial.println("a");
  timeEnd = millis();             // 現在の時間取得
  
  delay(50);
  Serial.print("println millis =");// 150ms待つ
  Serial.println(timeEnd-timeStart);    // 経過時間をシリアル送信
  */
  timeStart = micros();           // 現在の時間取得
  Serial.write("a");
  timeEnd = micros();             // 現在の時間取得
  
  delay(50); // 50ms待つ
  Serial.print("write micros =");
  Serial.println(timeEnd-timeStart);    // 経過時間をシリアル送信
  
  timeStart = micros();           // 現在の時間取得
  Serial.println("a");
  timeEnd = micros();             // 現在の時間取得
  
  delay(50);
  Serial.print("println micros =");// 150ms待つ
  Serial.println(timeEnd-timeStart);
}
