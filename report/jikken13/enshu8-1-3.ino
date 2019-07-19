#include <Wire.h>
#define COLOR_SENSOR_ADDR 0x39
#define REG_BLOCK_READ 0xCF
unsigned int readingdata[20];
unsigned int i, green, red, blue;
//double X, Y, Z, x, y, z; //演習 8.1.6 で使用

void setup(){
  Serial.begin(9600); //シリアル通信の初期化
  Wire.begin(); //I2C バスに接続
  Wire.beginTransmission(COLOR_SENSOR_ADDR); //カラーセンサの AD 変換開始
  Wire.write(0x80); //REG_CTL
  Wire.write(0x03); //CTL_DAT_INIITIATE
  Wire.endTransmission();
  }
  
void loop(){
  readRGB();
  //calculateCoordinate(); //演習 8.1.6 で使用
  delay(500);
}

void readRGB(){
  Wire.beginTransmission(COLOR_SENSOR_ADDR);
  Wire.write(REG_BLOCK_READ);
  Wire.endTransmission(); //送信完了
  Wire.beginTransmission(COLOR_SENSOR_ADDR); //送受信開始
  Wire.requestFrom(COLOR_SENSOR_ADDR, 8); //カラーセンサにデータ要求
  delay(500);
  if(Wire.available() >= 8){ //8byte以上受信したとき
    for(i =0; i < 8; i++){
      readingdata[i]=Wire.read(); //データの受信
    }
  }
  green = readingdata[1]*256 + readingdata[0]; //受信データ の配列と色情報の順番固定
  red = readingdata[3]*256 + readingdata[2]; //2byte の RGB 値にデータ復元
  blue = readingdata[5]*256 + readingdata[4];
  Serial.println("RGB values = ");
  Serial.print(red, DEC); Serial.print(","); //DEC: ascii code で 10 進表記
  Serial.print(green, DEC); Serial.print(",");
  Serial.println(blue, DEC);
}
