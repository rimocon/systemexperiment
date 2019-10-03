import processing.serial.*; // Serial ライブラリを取り込む
Serial port; // Serial クラスのオブジェクトを宣言
int val1,val2; //縦幅と横幅
int high1,high2,low1,low2;
void setup()
{
  size(500, 500); // サイズ 500 × 500 のウィンドウ生成
  port = new Serial(this, "/dev/ttyUSB0", 9600);//Serial クラスのインスタンス生成
}
void draw()
{
  background(0); // 背景を黒
  ellipse(250, 250, val1, val2); // 中心 (512,512) ,横幅val1,縦幅val2 の円(白塗り)を描画
  println("R"); // 描画タイミング(確認用)
}
// シリアルポートにデータが到着するたびに呼び出される割り込み関数
void serialEvent(Serial p) { // p にはデータが到着したシリアルポートに対応するインスタンス(ここでは port )が代入される
  if(p.available() >= 5){
    if(p.read() == 'A'){ //識別子Aを定義
      high1 = p.read(); //読み込み
      low1 = p.read(); //読み込み
      high2 = p.read();
      low2 = p.read();
      val1 = (high1 << 8) + low1;
      val2 = (high2 << 8) + low2;
      p.clear();
      println("<-");  // データ受信タイミング(確認用)
      println("val1=",val1); //確認用
      println("val2=",val2); //確認用
    }
  }
}
