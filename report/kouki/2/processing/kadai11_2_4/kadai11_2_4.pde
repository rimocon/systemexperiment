import processing.serial.*;

Serial port1;                                                       // 1台目のZumoのシリアル通信用
Serial port2;                                                       // 2台目のZumoのシリアル通信用
Serial port3;

String myString1 = null;
String myString2 = null;

int LF = 10;                                                        // LF（Linefeed）のアスキーコード
int zumo1_state;
int zumo2_state;
int zumo3_state;

int zumo_id = 0;

int graph_width =100;                                               // グラフの幅を定義

void setup() {
  size(1200, 800);                                                  // 幅 1200px, 高さ 800px のウインドウを生成
  port1 = new Serial(this, "/dev/ttyUSB1", 9600);     // Serial クラスのインスタンスを生成
  port1.clear();
  port1.bufferUntil(0x0d);                                          // LF = 0x0d までバッファ

  // ＊＊＊　ヒント：ここでport2の「ポート指定，クリア，LFまでバッファ」を行う　＊＊＊//
  /* 
  port2 = new Serial(this, "/dev/ttyUSB1", 9600);     // Serial クラスのインスタンスを生成
  port2.clear();
  port2.bufferUntil(0x0d);
  
  port3 = new Serial(this, "/dev/ttyUSB2", 9600);     // Serial クラスのインスタンスを生成
  port3.clear();
  port3.bufferUntil(0x0d);
  */
  
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
      fill(255,0,0);
      rect(0,0,width,height);
      text("zumo1回転中", 400, 200);
    }
    if (zumo1_state ==0) {
      text("zumo1停止中",400,200);
    }
  }
  /*
  
    // ＊＊＊　ヒント：ここに2番目のZumo用の処理を書く　＊＊＊//
  if(zumo_id == 2){                                                 // データを受信したときだけ書き換える（1番目のZumo）
    fill(0, 0, 0); rect(width/2,0, width/2,height/2);                     // 対象画面の初期化（黒く塗りつぶす）

    // グラフなどの描画
    fill(red,0,0); rect(10+width/2, height/2, 100, -red2);
    fill(0,green,0); rect(120+width/2, height/2, 100,-green2);
    fill(0,0,blue); rect(230+width/2,height/2, 100,-blue2);
   
    fill(red, green, blue); rect(350+width/2,30,200,200);

    if(myString2 != null){
      text(myString2, 10+width/2, 10);                                      // シリアル通信で受信したテキストの表示
    }
  }
  */

}

// シリアルポートにデータが到着するたびに呼び出される割り込み関数
void serialEvent(Serial p) {
  if ((p == port1 || p == port2 || p == port3) && (p.available() > 0)) {          // 割り込みシリアル通信が，port1か，port2で，なおかつデータが入っている時
    zumo_id = 1;                                                    // データをやり取りしたロボットのIDを記憶

    if(p == port1)  zumo_id = 1;                                    // データをやり取りしたロボットのIDを記憶
    else if(p == port2) zumo_id = 2; 
    else if(p == port3) zumo_id = 3;
    
    myString1 = port1.readStringUntil(LF);                          //文字データの最後まで読み込み
    if(myString1 != null){                                          //文字が入ってたら
      myString1 = trim(myString1);   
      println(myString1);
      //行末の改行 '¥n' を削除
      if(myString1 == "end"){
        zumo1_state = 0;
        zumo2_state = 1;
        zumo3_state = 0;
      }
    }
    sendData();
    /*
    myString2 = port2.readStringUntil(LF);                          //文字データの最後まで読み込み
    if(myString2 != null){                                          //文字が入ってたら
      myString2 = trim(myString2);                                  //行末の改行 '¥n' を削除
 
      float data[] = float(split(myString2, ','));                  // カンマで区切られた値を分割

      // 受信した数値の数が３つで，NaN (Not a Number) ではない時
      if (data.length == 3 && data[0] != Float.NaN && data[1] != Float.NaN && data[2] != Float.NaN){
        // キャリブレーションあり
        red2 = map(data[0], -5000, 1000, 0, 255);                    // 値を0〜255にマッピング
        green2 = map(data[1], -5000, 1000, 0, 255);                  // 値を0〜255にマッピング
        blue2 = map(data[2], -5000, 1000, 0, 255);                   // 値を0〜255にマッピング
      }
    }
    */
  }
}

void sendData() {
  if(zumo1_state == 1) {
    port1.write('H');
    println("zumo1_state=1");
  }
  if(zumo2_state == 1) {
    port2.write('H');
    println("zumo2_state=1");
  }
  if(zumo3_state == 1) {
    port3.write('H');
    println("zumo3_state=1");
  }
}
