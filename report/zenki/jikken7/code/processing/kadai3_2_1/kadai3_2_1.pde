import processing.serial.*;
Serial port;
int val;
int x, y;
int high, low;
int byte1, byte2, byte3, byte4;
int time, time_min, time_max;
int period;
float f;
void setup()
{
	size(1200, 500);
	port = new Serial(this, "/dev/ttyACM0", 9600);
	period = 20000;
	// 横軸の範囲は 20,000ms 間隔
	time_min = 0;
	// 横軸の範囲の初期値
	time_max = period;// 横軸の範囲の初期値
	x = 0; y = 0;
	time = 0;
	background(255);
	frameRate(60);
}
void draw()
{
	if ( time > time_max ) { // グラフの再描画
		time_min += period; // 横軸の範囲の更新
		time_max += period; // 横軸の範囲の更新
		background(255);
	}
	x = (int)map( time, time_min, time_max, 0, width ); // x 座標値
	y = (int)map( f, 174, 184, height*0.7, 0 );
	// y 座標値
	stroke(255, 0, 0);
	ellipse(x, y, 5, 5);
}
void serialEvent(Serial p) {
	if ( p.available() >= 7 ) {
		if ( p.read() == 'H' ) {
			byte1 = p.read();
			byte2 = p.read();
			byte3 = p.read();
			byte4 = p.read();
			time = (byte1 << 24 ) + (byte2 << 16 ) + (byte3 << 8 ) + byte4; // 4 バイトデータ
			high = p.read();
			low = p.read();
			val = (high << 8 ) + low; // 2 バイトデータ
      f = (float)val /100.0; 
      println("val=",val);
      println("f=",f);
			p.clear();
		}
	}
}
