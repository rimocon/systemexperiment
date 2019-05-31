import processing.serial.*; // Serial ライブラリを取り込む
Serial port; // Serial クラスのオブジェクトを宣言
int val1,val2; //縦幅と横幅
void setup()
{
  size(256, 256); // サイズ 256 × 256 のウィンドウ生成
  port = new Serial(this, "/dev/ttyACM0", 9600);//Serial クラスのインスタンス生成
}
void draw()
{
  background(0); // 背景を黒
  ellipse(125, 125, val1, val2); // 中心 (125,125) ,横幅val1,縦幅val2 の円(白塗り)を描画
  println("R"); // 描画タイミング(確認用)
}
// シリアルポートにデータが到着するたびに呼び出される割り込み関数
void serialEvent(Serial p) { // p にはデータが到着したシリアルポートに対応するインスタンス(ここでは port )が代入される
  if(p.available() >= 3){
    if(p.read() == 'A'){ //識別子Aを定義
      val1 = p.read(); //読み込み
      val2 = p.read(); //読み込み
      p.clear();
      println("<-");  // データ受信タイミング(確認用)
      println("val1=",val1); //確認用
      println("val2=",val2); //確認用
    }
  }
}
