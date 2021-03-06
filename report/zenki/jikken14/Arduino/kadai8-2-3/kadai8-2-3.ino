#include <Wire.h>
#define cal_time 10000
#define COLOR_SENSOR_ADDR 0x39
#define REG_BLOCK_READ 0xCF
unsigned int readingdata[20];
unsigned int i, red, green, blue;
int flg = 0;
/////////////////////////////////////////////////////////////
//map()関数のパラメータ：キャリブレーション後、適切な値に変更
//初期値：RGB の最小・最大を決定
unsigned int r_min = 30000, g_min = 30000, b_min = 30000;
unsigned int r_max = 0, g_max = 0, b_max = 0;
/////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600); //シリアル通信の初期化
  Wire.begin(); //I2C バスに接続
  Wire.beginTransmission(COLOR_SENSOR_ADDR); //カラーセンサの AD 変換開始
  Wire.write(0x80); //REG_CTL
  Wire.write(0x03); //CTL_DAT_INIITIATE
  Wire.endTransmission();
  //auto calibration
  Serial.println("Start Auto Calibration for 5 s");
  auto_calib(); //loop に入る前の最初の 5 秒間で自動キャリブレーション
  Serial.println("End Auto Calibration");
}
void loop() {
  readRGB();
  Serial.println("RGB values = ");
  Serial.print(red); Serial.print(",");
  Serial.print(green); Serial.print(",");
  Serial.println(blue);
  delay(100);
  if (red > 240 && green > 240 && blue > 240) {
    Serial.println("White"); //白の閾値
  }
  else if (red < 20 && green < 20 && blue < 20 ) {
    Serial.println("Black"); //黒の閾値
  }
  else if (red > 120 && green < 50 && blue < 50 ) {
    Serial.println("Red"); //赤の閾値
  }
  else if (red < 80 && green >150  && blue < 80 ) {
    Serial.println("Green"); //緑の閾値
  }
  else if (red < 50 && green < 50 && blue > 110 ) {
    Serial.println("Blue"); //青の閾値
  }
  else if (red < 70 && green > 80 && blue > 70 ) {
    Serial.println("Syan"); //シアンの閾値
  }
  else if (red > 120 && green < 80 && blue > 90 ) {
    Serial.println("Magenta"); //マゼンタの閾値
  }
  else if (red >120 && green > 120 && blue < 80 ) {
    Serial.println("Yellow"); //イエローの閾値
  }
  else Serial.println("Unknown");
}

void auto_calib() {
  unsigned long timeInit;
  timeInit = millis();
  while (1) {
    readRGB();
    if (red > r_max) r_max = red;
    if (red < r_min) r_min = red;
    if (green > g_max) g_max = green;
    if (green < g_min) g_min = green;
    if (blue > b_max) b_max = blue;
    if (blue < b_min) b_min = blue;
    Serial.print("min = ");
    Serial.print(r_min); Serial.print(",");
    Serial.print(g_min); Serial.print(",");
    Serial.println(b_min);
    Serial.print("max = ");
    Serial.print(r_max); Serial.print(",");
    Serial.print(g_max); Serial.print(",");
    Serial.println(b_max);
  
    delay(100);
    if (millis() - timeInit > cal_time){
      flg = 1; 
      break;
    }
  }
}

void readRGB(){
  Wire.beginTransmission(COLOR_SENSOR_ADDR);
  Wire.write(REG_BLOCK_READ);
  Wire.endTransmission(); //送信完了
  Wire.beginTransmission(COLOR_SENSOR_ADDR); //送受信開始
  Wire.requestFrom(COLOR_SENSOR_ADDR, 8); //カラーセンサにデータ要求
  delay(500);
  if(Wire.available() >= 8){ //8byte 以上受信したと き
    for(i =0; i < 8; i++){
      readingdata[i]=Wire.read(); //データの受信
    }
  }
  green = readingdata[1] * 256 + readingdata[0];
  red = readingdata[3] * 256 + readingdata[2];
  blue = readingdata[5] * 256 + readingdata[4];
  if (flg == 1){ //自動キャリブレーション終了後
  //map()関数によるキャリブレーション
    red = map(red, r_min, r_max, 0, 255);
    green = map(green, g_min, g_max, 0, 255);
    blue = map(blue, b_min, b_max, 0, 255);
  }
}
