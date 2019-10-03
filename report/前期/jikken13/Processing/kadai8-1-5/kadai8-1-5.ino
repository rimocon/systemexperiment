#include <Wire.h>
#define COLOR_SENSOR_ADDR 0x39
#define REG_BLOCK_READ 0xCF
unsigned int readingdata[20];
unsigned int i, green, red, blue,clr;
double X, Y, Z, x, y, z; //演習 8.1.6 で使用
float Red, Green, Blue;
int dataR, dataG, dataB;
int dataR_min, dataG_min, dataB_min;
int dataR_max, dataG_max, dataB_max;
unsigned long timenow,timeprev;

void setup(){
  pinMode(9, OUTPUT) ; // RED 9 番ピン
  analogWrite(9, 0); // PWM duty 比
  timeprev = millis();
  Serial.begin(9600); //シリアル通信の初期化
  Wire.begin(); //I2C バスに接続
  Wire.beginTransmission(COLOR_SENSOR_ADDR); //カラーセンサの AD 変換開始
  Wire.write(0x80); //REG_CTL
  Wire.write(0x03); //CTL_DAT_INIITIATE
  Wire.endTransmission();
  delay(1000);
  //Autocalibration
  CalibrationColorSensor();
  }
void loop(){
  timeprev = millis();
  readRGB();
 
  Serial.print(dataR_min);Serial.print(",--> ");Serial.println(dataR_max);
  Serial.print(dataG_min);Serial.print(",--> ");Serial.println(dataG_max);
  Serial.print(dataB_min);Serial.print(",--> ");Serial.println(dataB_max);
  
  //Autoキャリブレーションあり
  red = map(red, dataR_min, dataR_max, 0, 255); //下線部をシリアルモニタの最大値に変更
  green =  map(green, dataG_min, dataG_max, 0, 255);; //ここに Green の処理を入れる
  blue =   map(blue, dataB_min, dataB_max, 0, 255);; //ここに Blue の処理を入れる

 //manual calibration
  //red = map(red, 0, 1792, 0, 255); //下線部をシリアルモニタの最大値に変更
  //green =  map(green, 0, 2568, 0, 255);; //ここに Green の処理を入れる
  //blue =   map(blue, 0, 1792, 0, 255);; //ここに Blue の処理を入れる
  
  Serial.print(red); Serial.print(","); //DEC: ascii code で 10 進表記
  Serial.print(green); Serial.print(",");
  Serial.println(blue);
  timenow = millis();
  Serial.println(timenow - timeprev);
  
  
  calculateCoordinate(); //演習 8.1.6 で使用
  
  analogWrite(9, 255); // PWM duty 比
  delay(200); //点滅周期は各自で調整
  analogWrite(9, 0);
  delay(200); //点滅周期は各自で調整
  
  }
void readRGB(){
  Wire.beginTransmission(COLOR_SENSOR_ADDR);
  Wire.write(REG_BLOCK_READ);
  Wire.endTransmission(); //送信完了
  Wire.beginTransmission(COLOR_SENSOR_ADDR); //送受信開始
  Wire.requestFrom(COLOR_SENSOR_ADDR, 8); //カラーセンサにデータ要求
  delay(200);
  if(Wire.available() >= 8){ //8byte 以上受信したと き
    for(i =0; i < 8; i++){
      readingdata[i]=Wire.read(); //データの受信
    }
  }
  green = readingdata[1]*256 + readingdata[0]; //受信データ の配列と色情報の順番固定
  red = readingdata[3]*256 + readingdata[2]; //2byte の RGB 値にデータ復元
  blue = readingdata[5]*256 + readingdata[4];
  clr =  readingdata[7]*256 + readingdata[6];
  /*
  Serial.println("RGB values = ");
  Serial.print(red, DEC); Serial.print(","); //DEC: ascii code で 10 進表記
  Serial.print(green, DEC); Serial.print(",");
  Serial.println(blue, DEC);//Serial.print(",");
  Serial.println(clr, DEC);
  */
}
void calculateCoordinate(){
  X=(-0.142)*red+(1.549)*green+(-0.956)*blue;
  Y=(-0.324)*red+(1.578)*green+(-0.731)*blue;
  Z=(-0.682)*red+(0.770)*green+(0.563)*blue;
  
  x=X/(X+Y+Z); 
  y=Y/(X+Y+Z);
  
  if( (X>0) && (Y>0) && (Z>0) ){
    //Serial.println("x, y = ");
    Serial.print(x, 2); Serial.print(","); Serial.println(y, 2);
  }
  else Serial.println("Error!");
}

void  CalibrationColorSensor()
{
  unsigned long timeInit;

  dataR_min = 30000;
  dataG_min = 30000;
  dataB_min = 30000;
  dataR_max = 0;
  dataG_max = 0;
  dataB_max = 0;

  timeInit = millis();
  while ( 1 ) {
    readRGB();
    if ( red < dataR_min ) dataR_min = red;
    if ( green < dataG_min ) dataG_min = green;
    if ( blue < dataB_min ) dataB_min = blue;
    if ( red > dataR_max ) dataR_max = red;
    if ( green > dataG_max ) dataG_max = green;
    if ( blue > dataB_max ) dataB_max = blue;

    if ( millis() - timeInit > 5000 )
      break;
  }

}
