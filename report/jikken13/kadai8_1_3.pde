PImage img;  // Declare variable "a" of type PImage
import processing.serial.*;
Serial myPort;
float x,y,xx,yy;


void setup() {
  size(525, 575);
   // The image file must be in the data folder of the current sketch 
  // to load successfully
  img = loadImage("xymapF.png");  // Load the image into the program  
  myPort = new Serial(this,"/dev/ttyACM0",9600);
  myPort.bufferUntil('\n');
}
void draw() { //受信した値で描画
 
  image(img, 0, 0);
  //Figure drawn in rect TL =(25,55), BR =(470,560)

  println("x="+x);
  println("y="+y);
  
  xx = map(x, 0, 0.8, 25, 470);
  yy = map(y, 0, 0.9, 560, 55); 
  println("xx="+xx);
  println("yy="+yy);
  
  fill(255);  
  ellipse(xx,yy,15,15);  
  //red point
  ellipse(405,358,10,10);
  //green point
  ellipse(203,193,10,10);
  //blue point
  ellipse(114,523,10,10);
 
  strokeWeight(5);
  line(405,358,203,193); //R-G
  line(405,358,114,523); //R-G
  line(203,193,114,523); //G-B
}

void serialEvent(Serial myPort) {
  String myString = myPort.readStringUntil('\n'); //シリアルバッファー読込み
  if (myString != null){
    myString = trim(myString); //空白文字など消去
    float data[] = float(split(myString, ',')); //カンマ区切りで複数の情報を読込む
    if (data.length > 1) {
      x = data[0];
      y = data[1];
      myPort.clear();
    }
  }
}
