import processing.serial.*;

Serial port1;                                                       // 1台目のZumoのシリアル通信用


String myString1 = null;


int LF = 10;                                                        // LF（Linefeed）のアスキーコード
int zumo1_state;

int zumo_id = 1;

int graph_width =100;                                               // グラフの幅を定義
String str_end = "end";

void setup() {
  size(1200, 800);                                                  // 幅 1200px, 高さ 800px のウインドウを生成
  port1 = new Serial(this, "/dev/ttyUSB0", 9600);     // Serial クラスのインスタンスを生成
  port1.clear();
  port1.bufferUntil(0x0d);                                          // LF = 0x0d までバッファ
  background(0);                                                    // 背景色を黒に
  zumo1_state = 1; //1台目を回転させる
  sendData();
}

void draw() { 
  if(zumo_id == 1){                                                 // データを受信したときだけ書き換える（1番目のZumo）
    fill(0, 0, 0); rect(0,0, width,height);                     // 対象画面の初期化（黒く塗りつぶす）

    textSize(100);
    textAlign(CENTER, CENTER);
    if (zumo1_state == 1) {
      fill(255,255,255);
      text("zumo1 run", 400, 200);
    }
    if (zumo1_state ==0) {
      text("zumo1 stop",400,200);
    }
  }
}

// シリアルポートにデータが到着するたびに呼び出される割り込み関数
void serialEvent(Serial p) {
  if ((p == port1 ) && (p.available() > 0)) {          // 割り込みシリアル通信が，port1か，port2で，なおかつデータが入っている時
    zumo_id = 1;                                                    // データをやり取りしたロボットのIDを記憶
   
    myString1 = port1.readStringUntil(LF);                          //文字データの最後まで読み込み
    if(myString1 != null){                                          //文字が入ってたら
      myString1 = trim(myString1);   
      //行末の改行 '¥n' を削除
      if(myString1.equals(str_end)){
         println("recieve end");
         zumo1_state = 0;
         sendData();
      }
    }
  }
}

void sendData() {
  if(zumo1_state == 1) {
    port1.write('H');
  }
}
