import processing.serial.*; // Serial ライブラリを取り込む
Serial port; // Serial クラスのオブジェクトを宣言
int val,count,new_x,new_y,old_x,old_y; //それぞれ値を定義
void setup()
{
  size(800,300); // サイズ 800 × 300 のウィンドウ生成
  port = new Serial(this, "/dev/ttyACM0", 9600);//Serial クラスのインスタンス生成
  val = 0; //Arduinoから送られてきたデータを格納する
  count = 0; //受信した回数(x座標)
  old_x = 0; //折れ線グラフ用の前回のxの値
  old_y = 0; //折れ線グラフ用の前回のyの値
  new_x = 0; //折れ線グラフ用の今のxの値
  new_y = 0; //折れ線グラフ用の今のyの値
  background(255); //　背景を白に設定
}
void draw()
{
  stroke(255,0,0); //線の色を赤に設定
  strokeWeight(5); //線の太さを"5"に設定
  new_x = count; //x座標の値はcountそのもの
  new_y = (255 - val)*300/255; //y座標の値はval=255のときy=0(一番上),val=0のときy=300(一番下)
  point(new_x,new_y); //点を描画
  strokeWeight(3); //線の太さを"3"に設定
  line(old_x,old_y,new_x,new_y); //折れ線用に線を描画
  old_x = new_x; //今のxの値を前回の値として格納
  old_y = new_y; //今のyの値を前回の値として格納
  if( count == 800){ //もし右端まできたら
    count = 0; //count初期化
    background(255); //背景を白に(クリア)
  }
  println("R"); // 描画タイミング(確認用)
}
// シリアルポートにデータが到着するたびに呼び出される割り込み関数
void serialEvent(Serial p) { // p にはデータが到着したシリアルポートに対応するインスタンス(ここでは port )が代入される
  val = p.read(); // 受信バッファから 1 バイト読み込み
  println("<-"); // データ受信タイミング(確認用)
  count++; //countを1増やす(x座標を1つ右にずらす)
}
