import processing.serial.*;
Serial port;
int state;
void setup() {
  size(400, 200);
  //幅 400px, 高さ 200px のウインドウを生成
  port = new Serial(this, "/dev/ttyACM0", 9600); //Serial クラスのインスタンスを生成
}
void draw() {
  background(0);
  textSize(100);
  textAlign(CENTER, CENTER);
  if (state == 0) {
    text("GO", 200, 100);
  } else {
  text("BACK", 200, 100);
  }
}
void serialEvent(Serial p) {
  state = p.read();
}
