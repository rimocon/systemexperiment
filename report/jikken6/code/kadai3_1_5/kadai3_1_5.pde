import processing.serial.*; // Serial ライブラリを取り込む
Serial port; // Serial クラスのオブジェクトを宣言
float rad,x,y; //ラジアン,x,yをそれぞれ定義
int val; //Arduinoから送られてくるデータ格納用

void setup()
{
  size(500,500); // サイズ 500 × 500 のウィンドウ生成
  port = new Serial(this, "/dev/ttyACM0", 9600);//Serial クラスのインスタンス生成

}
void draw()
{
  background(255); //背景を白に設定
  stroke(0,0,0); //線を黒に設定
  ellipse(200,200,200,200); //円を描画
  stroke(255,0,0); //線を赤に設定
  strokeWeight(5); //線の太さを"5"に設定
  rad = 2*PI*val/255; //受信したデータをラジアンに変換(255で2π,0で0)
  x = 200 + 100*cos(rad - PI/2); //x座標の値(中心200から距離cos(rad - π/2)
  y = 200 + 100*sin(rad - PI/2); //y座標の値(中心200から距離sin(rad - π/2)
  line(200,200,x,y); //メータの線を描画
  println("R"); // 描画タイミング(確認用)
}
// シリアルポートにデータが到着するたびに呼び出される割り込み関数
void serialEvent(Serial p) { // p にはデータが到着したシリアルポートに対応するインスタンス(ここでは port )が代入される
  val = p.read(); // 受信バッファから 1 バイト読み込み
  println("<-"); // データ受信タイミング(確認用)
}
