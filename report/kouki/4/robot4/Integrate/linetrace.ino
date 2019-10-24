void linetrace_bang_bang()
{
  static float lightMin = 0; // 各自で設定
  static float lightMax = 255; // 各自で設定
  static float speed = 100; // パラメーター
  static float Kp = 2.0; // パラメーター
  float lightNow;
  float speedDiff;

  lightNow = (red_G + green_G + blue_G ) / 3.0;
  if ( lightNow < (lightMin + lightMax) / 2.0 ) // 右回転
    speedDiff = -Kp * speed;
  else // 左回転
    speedDiff = Kp * speed;
  motorL_G = speed - speedDiff;
  motorR_G = speed + speedDiff;
}

void linetrace_P(){
 // 各自で作成
}

void task_A()
{
  static int stop_period; // static変数であることに注意
  static unsigned long startTime; // static変数，時間計測ははunsigned long
  char color;

  switch ( mode_G ) {
    case 0:
      mode_G = 1;
      break;  // break文を忘れない（忘れるとその下も実行される）

    case 1:
      linetrace_P(); // ライントレース（各自で作成）
      color = identify_RGB(); // ラインの色を推定(R:赤，G:緑，B:青，-:それ以外）
      if ( color == 'R' ) { // red
        stop_period = 1000; // 後で停止する期間
        mode_G = 2;
      }
      else if ( color == 'G' ) { // green
        stop_period = 500; // 後で停止する期間
        mode_G = 2;
      }
      break;

    case 2:
      linetrace_P(); // ライントレース
      if ( identify_RGB() == 'B' ) { // brue
        startTime = timeNow_G; // mode_G=3に遷移した時刻を記録
        mode_G = 3;
      }
      break;

    case 3:
      motorL_G = 0; // 停止
      motorR_G = 0;
      if ( timeNow_G - startTime > stop_period ) // 指定時間経過したら
        mode_G = 1;
      break;
  }
}

// lineの色の推定
char identify_RGB()
{
  float alpha = 1.2; // パラメーター

  if ( blue_G > alpha * red_G && blue_G > alpha * green_G ) // _*_Gはグローバル変数
    return 'B';
  else if ( red_G > alpha * blue_G && red_G > alpha * green_G )
    return 'R';
  else if ( green_G > alpha * red_G && green_G > alpha * blue_G )
    return 'G';
  else
    return '-';
}

int identify_color( int red, int green, int blue )
{
  float d2;
  float d2_max = 50; // パラメーター（適宜調整）

  d2 = pow(red - red_G, 2) + pow(green - green_G, 2) + pow(blue - blue_G, 2);
  if ( d2 < d2_max * d2_max )
    return 1;
  else
    return 0;
}

int maintainState( unsigned long period )
{
  static int flagStart = 0; // 0:待ち状態，1:現在計測中
  static unsigned long startTime = 0;

  if ( flagStart == 0 ) {
    startTime = timeNow_G; // 計測を開始したtimeNow_Gの値を覚えておく
    flagStart = 1; // 現在計測中にしておく
  }

  if ( timeNow_G - startTime > period ) { // 計測開始からの経過時間が指定時間を越えた
    flagStart = 0; // 待ち状態に戻しておく
    startTime = 0; // なくても良いが，形式的に初期化
    return 1;
  }
  else
    return 0;
}
