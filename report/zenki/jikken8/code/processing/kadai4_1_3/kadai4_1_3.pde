import processing.serial.*;
Serial port;
int val;
int x,y;
int time,time_min,time_max;
int period;
int byte1,byte2,byte3,byte4,byte5;
void setup(){
  size(1200, 500);
  port = new Serial(this, "/dev/ttyUSB0", 9600);
  period = 20000;
  time_min = 0;
  time_max = period;
  x = 0; y= 0;
  background(255);
  frameRate(60);
 }
void draw(){
  if ( time > time_max ) {
    time_min += period;
    time_max += period;
    background(255);
  }
  x = (int)map(time,time_min,time_max,0,width);
  y = (int)map(val,0,1023,height,0);
  stroke(255,0,0);
  ellipse(x,y,5,5);
}
void serialEvent(Serial p){
  if (p.available() >= 8) {
    if (p.read() == 252) {
      val = p.read() * 0x20 + p.read();
      byte1 = p.read();
      byte2 = p.read();
      byte3 = p.read();
      byte4 = p.read();
      byte5 = p.read();
      time = (byte1 << 28 )+ (byte2 << 21) + (byte3 << 14 ) + (byte4 << 7 ) + byte5 ; //5バイト
      println(val);
      println("time=",time);
      port.write(0xff); // 次のデータ 送信要求 ( 任意の 1 バイ ト ) を 送信
    }
  }
}
void mousePressed(){ //マウスボタンが押されたら割り込み
  port.write(0xff);
}
