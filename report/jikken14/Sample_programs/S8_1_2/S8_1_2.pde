import processing.serial.*;
Serial myPort;
float Red, Green, Blue;
void setup() {
  size(640, 480);
  //myPort = new Serial(this, "/dev/ttyACM0", 9600);
  myPort = new Serial(this, "COM10", 9600);
  myPort.bufferUntil('\n'); //改行までメッセージ受信
}
void draw() { //受信した値で描画
  background(0);
  fill(Red,0,0); rect(10,470,100,-Red);
  fill(0,Green,0); rect(120,470,100,-Green);
  fill(0,0,Blue); rect(230,470,100,-Blue);
  fill(Red, Green, Blue); rect(360,110,260,260);
  print("R="+Red+", "); print("G="+Green+", "); println("B="+Blue);
  fill(255);
  text("Red=",10,10); text(int(Red),40,10);
  text("Green=",120,10); text(int(Green),160,10);
  text("Blue=",230,10); text(int(Blue),265,10);
}
void serialEvent(Serial myPort) {
  String myString = myPort.readStringUntil('\n'); //シリアルバッファー読込み
  if (myString != null){
    myString = trim(myString); //空白文字など消去
    float data[] = float(split(myString, ',')); //カンマ区切りで複数の情報を読込む
    if (data.length >1){
      
      // キャリブレーションなし
      Red = data[0];
      //Green = ???; //ここに Green の処理を入れる
      //Blue = ???; //ここに Blue の処理を入れる
      
      // キャリブレーションあり
     // Red = map(data[0], 0, 1000, 0, 255); //下線部をシリアルモニタの最大値に変更
     // Green = ???; //ここに Green の処理を入れる
     // Blue = ???; //ここに Blue の処理を入れる
     
      myPort.clear();
    }
  }
}