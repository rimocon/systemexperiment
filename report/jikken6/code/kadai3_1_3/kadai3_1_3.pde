import processing.serial.*; // Serial ライブラリを取り込む
Serial port; // Serial クラスのオブジェクトを宣言
int val,count,x,y;
void setup()
{
  size(800,300); // サイズ 800 × 300 のウィンドウ生成
  port = new Serial(this, "/dev/ttyACM0", 9600);//Serial クラスのインスタンス生成
  val = 0;
  count = 0;
  x = 0;
  y = 0;
  background(255); // white
}
void draw()
{
  stroke(255,0,0);
  strokeWeight(5);
  x = count;
  y = (255 - val)*300/255;
  point(x,y);
  if( count == 800){
    count = 0;
    background(255); // white
  }
  println("R"); // 描画タイミング(確認用)
}
// シリアルポートにデータが到着するたびに呼び出される割り込み関数
void serialEvent(Serial p) { // p にはデータが到着したシリアルポートに対応するインスタンス(ここでは port )が代入される
  val = p.read(); // 受信バッファから 1 バイト読み込み
  println("<-");
  count++;
// データ受信タイミング(確認用)
}
