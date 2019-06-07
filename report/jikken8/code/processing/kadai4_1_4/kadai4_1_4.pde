import processing.serial.*;
Serial port;
PrintWriter output; //PrintWriterクラスのオブジェクトを宣言
int lux,temp;
int x,y1,y2;
int time,time_min,time_max;
int period;
int byte1,byte2,byte3,byte4,byte5;
void setup(){
  size(1200, 500);
  port = new Serial(this, "/dev/ttyUSB0", 9600);
  period = 20000;
  time_min = 0;
  time_max = period;
  x = 0; y1= 0; y2 = 0;
  background(255);
  frameRate(60);
  output = createWriter("kadai4-1-3.csv");
 }
void draw(){
  if ( time > time_max ) {
    time_min += period;
    time_max += period;
    background(255);
  }
  x = (int)map(time,time_min,time_max,0,width);
  y1 = (int)map(lux,0,1023,height,0);
  y2 = (int)map(temp,170,200,height,0);
  stroke(255,0,0);
  ellipse(x,y1,5,5);
  stroke(0,0,255);
  ellipse(x,y2,5,5);
}
void serialEvent(Serial p){
  if (p.available() >= 10) {
    if (p.read() == 252) {
      lux = (p.read() * 0x20 + p.read())/100;
      temp = (p.read() * 0x20 + p.read())/100;
      byte1 = p.read();
      byte2 = p.read();
      byte3 = p.read();
      byte4 = p.read();
      byte5 = p.read();
      time = (byte1 << 28 )+ (byte2 << 21) + (byte3 << 14 ) + (byte4 << 7 ) + byte5 ; //5バイト
      println("y1=",y1);
      println("temp=",temp);
      println("y2=",y2);
      println("time=",time);
      port.write(0xff); // 次のデータ 送信要求 ( 任意の 1 バイ ト ) を 送信
    }
  }
}
void mousePressed(){ //マウスボタンが押されたら割り込み
  port.write(0xff);
}
void keyPressed() {
  if( key == 'q' ) {
    output.flush();
    output.close();
    exit();
  }
}
