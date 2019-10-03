import processing.serial.*;
Serial port;
int distance;
void setup() {
  size(400, 300);
  //幅 400px, 高さ 200px のウインドウを生成
  port = new Serial(this, "/dev/ttyACM0", 9600); //Serial クラスのインスタンスを生成
}
void draw() {
  background(0); //背景黒
  fill(255,255,255); //白に設定
  textSize(80); //テキストサイズを設定
  text(distance,0, 60); //距離を描画
  text("cm",100,60); //"cm"を描画
  fill(0,0,255); //色を青に設定
  noStroke();
  rect(0,100,float(distance *20),100); //長方形で距離を描画
  stroke(255,0,0); //色を赤に設定
  line(200,80,200,220);
}
void serialEvent(Serial p) {
  distance = p.read();
}
