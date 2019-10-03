import processing.serial.*; // Serial ライブラリを取り込む
Serial port; // Serial クラスのオブジェクトを宣言
int val,count,x,y; //変数宣言
void setup()
{
  size(800,300); // サイズ 800 × 300 のウィンドウ生成
  port = new Serial(this, "/dev/ttyACM0", 9600);//Serial クラスのインスタンス生成
  val = 0;
  count = 0;
  x = 0;
  y = 0;
  background(255); //背景白 
}
void draw()
{
  stroke(255,0,0); //赤色
  strokeWeight(5); //太さを5
  x = count; //countを代入
  y = (255 - val)*300/255; //val=0で300,val=255で0
  point(x,y); //点を描画
  if( count == 800){ //右端についたら
    count = 0; //初期化
    background(255); //背景をクリア 
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
