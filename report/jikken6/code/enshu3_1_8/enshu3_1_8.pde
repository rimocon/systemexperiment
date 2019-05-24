import processing.serial.*; // Serial ライブラリを取り込む
Serial port; //Serial クラスのオブジェクトを宣言
int val;
void setup()
{
  size(256, 256);
  port = new Serial(this, "/dev/ttyACM1", 9600);
}
void draw()
{
  background(0);
  ellipse(125, 125, val, val);
  port.write('A'); // 次のデータ送信要求(任意の 1 バイト)を送信
  println("R");
  // 描画タイミング(確認用)
}
// シリアルポートにデータが到着するたびに呼び出される割り込み関数
void serialEvent(Serial p) {
  val = p.read();
  println("<-");
  // データ受信タイミング(確認用)
}
