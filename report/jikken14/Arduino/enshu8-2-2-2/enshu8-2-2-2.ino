#include<Wire.h>
#define COLOR_SENSOR_ADDR 0x39
#define REG_BLOCK_READ 0xCF
unsigned int readingdata[20];
unsigned int i, green, red, blue;
////////////////////////////////////////////////////////////////////////////////////////////////
//初期値：RGB の最小・最大を決定
//手動キャリブレーション後、コメントアウト
//unsigned int r_min = 30000, g_min = 30000, b_min = 30000;
//unsigned int r_max = 0, g_max = 0, b_max = 0;
//map()関数のパラメータ
//手動キャリブレーション後、 min,max を適切な値に変更
//①manual_calib()関数をコメントアウトし、②map()関数を使える様にする。
unsigned int r_min = 7680, g_min = 16648, b_min = 11520;
unsigned int r_max = 40705, g_max = 56072, b_max = 50944;
// min = 7680,16648,11520
// max =  40705,56072,50944


////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600); //シリアル通信の初期化
  Wire.begin(); //I2C バスに接続
  Wire.beginTransmission(COLOR_SENSOR_ADDR); //カラーセンサの AD 変換開始
  Wire.write(0x80); //REG_CTL
  Wire.write(0x03); //CTL_DAT_INIITIATE
  Wire.endTransmission();
}

void loop() {
  readRGB();
  //Serial.println("RGB values = ");
  Serial.print(red); Serial.print(",");
  Serial.print(green); Serial.print(",");
  Serial.println(blue);
  //manual_calib(); //①手動キャリブレーション後、コメントアウト
}
void manual_calib() {
//Manual Calibration for red
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
  delay(1000);
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
  //②map()関数によるキャリブレーション
  red = map(red, r_min, r_max, 0, 255);
  green = map(green, g_min, g_max, 0, 255);
  blue = map(blue, b_min, b_max, 0, 255);

  //白　234,230,226
  //黒　12,10,3

}
