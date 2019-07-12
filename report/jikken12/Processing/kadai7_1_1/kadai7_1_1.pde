import processing.serial.*;

Serial port;
int distance; //距離(cm)
int angle; //角度(°)
int x; //対象のx座標
int y; //対象のy座標
float d_bef; //対象との距離(前回)
float d_now; //対象との距離(今)
void setup() {
  frameRate(60); //draw()を1秒間に60回呼び出す
  size(800,400); //600*200pxのウィンドウを作成
  background(255,255,255); //背景を白で描画
  port = new Serial(this, "/dev/ttyACM0",9600); //Serialクラスのインスタンスを生成
  d_bef = 0; //初期化
  d_now = 0; //初期化
}

void draw() {
  translate(400,400); //座標軸を(400,400)に移動
  
  strokeWeight(5); //線の太さを5に
  stroke(0,0,0); //線の色を黒に
  noFill(); //塗りつぶさない
  arc(0,0,800,800,-PI,PI); //(0,0)中心,直径800の半円を描画
  arc(0,0,400,400,-PI,PI); //(0,0)中心,直径400の半円を描画
  line(0,0,0,-height);
  strokeWeight(1);
  stroke(0,0,255);
  line(0,0,400 * cos(radians(angle)),-400 * sin(radians(angle)));
  stroke(255,0,0);
  d_now = map(distance,0,60,0,400); //距離を0~60から0~400に変える
  println(d_now);
  //if( d_now > 90 ) {
    if ( d_bef != d_now){
      ellipse(d_now*cos(radians(angle)),-d_now *sin(radians(angle)),8,8);
    }
  //}
  d_bef = d_now; //現在の値を過去の値として格納
  if ( angle == 180 || angle == 0 ) {
    background(255,255,255); //180度か0度になったら画面を初期化
  }
}

//シリアルポートにデータが到着するたびに呼び出される関数

void serialEvent(Serial p) {
  if ( p.available() >= 3){
    if (p.read() == 'H' ) {
      distance = p.read();
      angle = p.read();
      p.clear();
    }
  }
}
