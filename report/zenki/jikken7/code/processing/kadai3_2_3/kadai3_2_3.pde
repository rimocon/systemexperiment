import processing.serial.*;
Serial port;
int val; //Arduinoからの値格納用変数
int x, y; //円の中心値
int high, low; //Arduinoからの値用(上位8ビットと下位8ビット)
int byte1, byte2, byte3, byte4; //time用の4バイトの値格納用変数
int time, time_min, time_max; //現在時刻と最小値,最大値格納用変数
int t_min,t_max; //温度の最小値,最大値格納用変数
int period; //x軸の範囲設定用
float f; //valをfloat型に変換する用
int count; //y軸表示用(段階的にy軸の値を変える用)
int x_min,x_max,y_min,y_max;
void setup()
{
	size(1200, 500); //1200*500のウィンドウを生成
	port = new Serial(this, "/dev/ttyACM0", 9600);
	period = 20000; // 横軸の範囲は 20,000ms 間隔
	time_min = 0; // 横軸の範囲の初期値
	time_max = period; // 横軸の範囲の初期値
  t_min = 20; //温度の最低値
  t_max = 31; //温度の最大値
	x = 0; y = 0; //x,yの初期値
	time = 0; //timeの初期値
  count = 0; //countの初期値
  x_min = 100; //ウィンドウの一部に表示用
  x_max = 600; //ウィンドウの一部に表示用
  y_min = 100; //ウィンドウの一部に表示用
  y_max = 250; //ウィンドウの一部に表示用
	background(255); //背景を白
	frameRate(60); //フレームレート60に設定
}
void draw()
{
	if ( time > time_max ) { // グラフの再描画
		background(255); //背景を白にクリア
    
    count = 0;
    while ( count < (t_max - t_min + 1)){
      textSize(13); //テキストサイズを'15'に設定
      fill(0); //文字の色を黒に設定
      text("T=",110,150 - 150/(t_max - t_min)*count + 100); //"T="を表示
      text(t_min+count,130,150 - 150/(t_max - t_min)*count +100); //20度から31度まで表示
      noFill(); //終了用
      stroke(0, 0, 255); //文字の色を青に設定
      line(x_min, 150 - 150/(t_max - t_min)*count + 100, x_max,150 - 150/(t_max - t_min)*count+ 100); //y軸の線を描画
      count++;
    }
    stroke(0,0,0);
    rect(x_min,y_min,(x_max - x_min) ,(y_max - y_min));
    time_min += period; // 横軸の範囲の更新
    time_max += period; // 横軸の範囲の更新
	}
	x = (int)map( time, time_min, time_max, x_min, x_max ); // x 座標値
	y = (int)map( f, t_min, t_max, y_max, y_min ); // y 座標値
  /***************y軸の表示部分********************/
  
  textSize(13); //テキストサイズを'15'に設定
  fill(0); //文字の色を黒に設定
  text("T=",110,150 - (150/(t_max - t_min)*count )+ 100); //"T="を表示
  text(t_min+count,130,150 - 150/(t_max - t_min)*count +100); //20度から31度まで表示
  noFill(); //終了用
  stroke(0, 0, 255); //文字の色を青に設定
  line(x_min, 150 - 150/(t_max - t_min)*count + 100, x_max,150 - 150/(t_max - t_min)*count+ 100); //y軸の線を描画
  if ( count < (t_max - t_min)){ //31度まで表示していないなら
    count ++; //カウントを1増やす
  }
  
  /*******************円を表示********************/
  stroke(0,0,0);
  noFill();
  rect(x_min,y_min,(x_max - x_min),(y_max - y_min));
  stroke(255, 0, 0);
	ellipse(x, y, 5, 5);
}
void serialEvent(Serial p) {
	if ( p.available() >= 7 ) {
		if ( p.read() == 'H' ) {
			byte1 = p.read(); //それぞれ1byteずつ読み込んでいく
			byte2 = p.read(); //それぞれ1byteずつ読み込んでいく
			byte3 = p.read(); //それぞれ1byteずつ読み込んでいく
			byte4 = p.read(); //それぞれ1byteずつ読み込んでいく
			time = (byte1 << 24 ) + (byte2 << 16 ) + (byte3 << 8 ) + byte4; // 4 バイトデータ
			high = p.read(); //上位8ビットを格納
			low = p.read();  //下位8ビットを格納
			val = (high << 8 ) + low; // 2 バイトデータ
      f = (float)val /100.0; //float型に直す
      println("val=",val); //値確認用
      println("f=",f); //値確認用
			p.clear();
		}
	}
}
