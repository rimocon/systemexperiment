import processing.serial.*; // Serial ライブラリを取り込む
Serial port; // Serial クラスのオブジェクトを宣言
int val;
void setup()
{
  size(256, 256); // サイズ 256 × 256 のウィンドウ生成
  port = new Serial(this, "/dev/ttyACM0", 9600);//Serial クラスのインスタンス生成
}
void draw()
{
  background(0); // 背景を黒
  ellipse(125, 125, val, val); // 中心 (125,125) ,直径 val の円(白塗り)を描画
  println("R"); // 描画タイミング(確認用)
}
// シリアルポートにデータが到着するたびに呼び出される割り込み関数
void serialEvent(Serial p) { // p にはデータが到着したシリアルポートに対応するインスタンス(ここでは port )が代入される
  val = p.read(); // 受信バッファから 1 バイト読み込み
  println("<-");
  // データ受信タイミング(確認用)
}
