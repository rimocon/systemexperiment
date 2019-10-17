#include <Wire.h>

#define COLOR_SENSOR_ADDR 0x39
#define REG_BLOCK_READ 0xCF
#define ledred 9
#define ledgreen 11
#define ledblue 10
unsigned int readingdata[20];
unsigned int i, green, red, blue;
unsigned long Timenow,Timeprev; 
int change;
int period; //間隔
double X, Y, Z, x, y, z; //演習 8.1.6 で使用
void setup(){
  Serial.begin(9600); //シリアル通信の初期化
  Wire.begin(); //I2C バスに接続
  Wire.beginTransmission(COLOR_SENSOR_ADDR); //カラーセンサの AD 変換開始
  Wire.write(0x80); //REG_CTL
  Wire.write(0x03); //CTL_DAT_INIITIATE
  Wire.endTransmission();

  pinMode(ledred, OUTPUT) ; // RED 9 番ピン
  pinMode(ledgreen, OUTPUT) ; // GREEN 10 番ピン
  pinMode(ledblue, OUTPUT) ; // BLUE 9 番ピン
  analogWrite(ledred, 0); // PWM duty 比
  analogWrite(ledgreen,0);
  analogWrite(ledblue,0);
  change = 0;
  Timeprev = millis();
 }
void lightled() {
  if(change == 0){
    analogWrite(ledred, 255); // PWM duty 比
    analogWrite(ledgreen, 0);
    analogWrite(ledblue, 0);
    change++;
  }
  else if(change == 1){
    analogWrite(ledred, 0); // PWM duty 比
    analogWrite(ledgreen, 255);
    analogWrite(ledblue, 0);
    change++;
  }
  else if(change == 2){
    analogWrite(ledred, 0); // PWM duty 比
    analogWrite(ledgreen, 0);
    analogWrite(ledblue, 255);
    change = 0;
  }
}
void loop(){
  readRGB();
  Timenow =millis();
  if (Timenow - Timeprev >= period){
    lightled();
  }
  calculateCoordinate(); //演習 8.1.6 で使用
  Serial.println(change);
  delay(500);
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
  green = readingdata[1]*256 + readingdata[0]; //受信データ の配列と色情報の順番固定
  red = readingdata[3]*256 + readingdata[2]; //2byte の RGB 値にデータ復元
  blue = readingdata[5]*256 + readingdata[4];
  Serial.println("RGB values = ");
  Serial.print(red, DEC); Serial.print(","); //DEC: ascii code で 10 進表記
  Serial.print(green, DEC); Serial.print(",");
  Serial.println(blue, DEC);
}
void calculateCoordinate() {
  X=(-0.142)*red+(1.549)*green+(-0.956)*blue;
  Y=(-0.324)*red+(1.578)*green+(-0.731)*blue;
  Z=(-0.682)*red+(0.770)*green+(0.563)*blue;
  x=X/(X+Y+Z); y=Y/(X+Y+Z);
  if( (X>0) && (Y>0) && (Z>0) ){
  Serial.println("x, y = ");
    Serial.print(x, 2); Serial.print(","); Serial.println(y, 2);
  }
  else Serial.println("Error!");
}
