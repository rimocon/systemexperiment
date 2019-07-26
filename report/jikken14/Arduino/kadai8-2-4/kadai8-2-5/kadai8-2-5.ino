#include <Wire.h>
#define cal_time 10000
#define COLOR_SENSOR_ADDR 0x39
#define REG_BLOCK_READ 0xCF
unsigned int readingdata[20];
unsigned int i, red, green, blue;
int flg = 0;
unsigned int r_min = 30000, g_min = 30000, b_min = 30000;
unsigned int r_max = 0, g_max = 0, b_max = 0;

#define max_colors 10//NN: 識別したい色の数
unsigned int ave_colors[max_colors][3] = {
  {263, 365, 263}, //白識別：red, green, blue 値
  { 3, 3, 3}, //黒識別：red, green, blue 値
  { 64, 64, 64}, //Other1：中間色 1
  {192, 192, 192},//Other2：中間色 2
  {153, 75, 14},//赤
  {48, 176, 49},//緑
  {55, 78, 181},//青
  {43, 92, 78},//シアン
  {129, 78, 103},//マゼンタ
  {190, 266, 78}//イエロー
};
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
  Serial.print(blue); Serial.print(",");
  delay(100);
  
  //NN 関数の呼び出し
  Nearest_Neighbor();
  delay(500);
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
    /*
    Serial.print("min = ");
    Serial.print(r_min); Serial.print(",");
    Serial.print(g_min); Serial.print(",");
    Serial.println(b_min);
    //Serial.print("max = ");
    Serial.print(r_max); Serial.print(",");
    Serial.print(g_max); Serial.print(",");
    Serial.println(b_max);
  */
    delay(100);
    if (millis() - timeInit > cal_time) {
      flg = 1;
      break;
    }
  }
}

void readRGB() {
  Wire.beginTransmission(COLOR_SENSOR_ADDR);
  Wire.write(REG_BLOCK_READ);
  Wire.endTransmission(); //送信完了
  Wire.beginTransmission(COLOR_SENSOR_ADDR); //送受信開始
  Wire.requestFrom(COLOR_SENSOR_ADDR, 8); //カラーセンサにデータ要求
  delay(500);
  if (Wire.available() >= 8) { //8byte 以上受信したと き
    for (i = 0; i < 8; i++) {
      readingdata[i] = Wire.read(); //データの受信
    }
  }
  green = readingdata[1] * 256 + readingdata[0];
  red = readingdata[3] * 256 + readingdata[2];
  blue = readingdata[5] * 256 + readingdata[4];
  if (flg == 1) { //自動キャリブレーション終了後
    //map()関数によるキャリブレーション
    red = map(red, r_min, r_max, 0, 255);
    green = map(green, g_min, g_max, 0, 255);
    blue = map(blue, b_min, b_max, 0, 255);
  }
}

int Nearest_Neighbor() {
  int count = 0;
  int color = -1;
  float minDistance = 9999999;
  float distance;
  for (int i = 0; i < max_colors; i++) { // i は設定したカラーのラベル
    distance = sqrt( (red - ave_colors[i][0]) * (red - ave_colors[i][0])
                     + (green - ave_colors[i][1]) * (green - ave_colors[i][1])
                     + (blue - ave_colors[i][2]) * (blue - ave_colors[i][2]));
    if ( distance < minDistance ) { //最短距離の判定
      minDistance = distance;
      color = i;
    }
  }
  if (color == 0) Serial.println("White");
  else if (color == 1) Serial.println("Black");
  else if (color == 2 || color == 3) Serial.println("Others");
  else if (color == 4) Serial.println("Red");
  else if (color == 5) Serial.println("Green");
  else if (color == 6) Serial.println("Blue");
  else if (color == 7) Serial.println("Syan");
  else if (color == 8) Serial.println("Magenta");
  else if (color == 9) Serial.println("Yellow");
  else Serial.println("Not detected!"); //例外処理：未検出の場合
}
