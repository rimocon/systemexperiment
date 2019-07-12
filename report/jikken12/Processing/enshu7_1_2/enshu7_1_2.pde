import processing.serial.*;

Serial port;
int dsitance; //距離(cm)

void setup() {
  frameRate(60); //draw()を1秒間に60回呼び出す
  size(600,200); //600*200pxのウィンドウを作成
  port = new Serial(this, "dev/ttyACM0",9600); //Serialクラスのインスタンスを生成
}

void draw() {
  if (distance < 10) {
    background(255,0,0); //距離が10cm未満なら背景を赤で描画
  }
  else {
    background(255,255,255); //距離が10cm以上ならば背景を白で描画
  }
  
  translate(0,100); //座標軸を右に0px,下に100px移動
  
  stroke(0,0,255); //枠線を青に
  fill(0,0,255); //内側を青に
  rect(200,-20,distance*6,40); //幅distance*6,高さ40pxの長方形を描画
  
  fill(0); //テキストの色を黒に
  textSize(40); //サイズを40ptに
  text(distance,100,20); //distanceを(100,20)に描画
}

//シリアルポートにデータが到着するたびに呼び出される関数

void serialEvent(Serial p) {
  distance = p.read();
}
