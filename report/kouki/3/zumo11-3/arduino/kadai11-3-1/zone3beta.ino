//
// Zone 3 Beta
//

float avex = 0;

float turnTo(float dir) {
  float heading, diff;

  heading = direction_G;
  if (heading>180) heading -= 360; //-180 < heading < 180 , E=90,W=-90,N=180,S=-180
  heading -= dir; //常に90引いてる
  if (heading>180) heading -= 360; //200とかなら-160、つまり一周したらその分もどして-180<heading<180にする
  if (heading<-180) heading += 360;
  diff = -heading*5;            // P-制御 
  if (diff>200) diff = 200;     // 飽和 -200<diff<200に正規化
  if (diff<-200) diff = -200;   // 飽和
  return diff;
}
void zone3beta()
{
  static int countTurn = 0;
  int done = 0;
  float speed0, diff;

  avex = 0.9*avex + 0.1*compass.a.x;

  switch ( mode_G ) {
    case 0: // setupはここ
      countTurn = 0;
      mode_G = 1;
    case 1: // 山探し(ここでは直進)
      if (avex>4000) { // 登り始めたら
        mode_G=2;
      }
      speed0 = 150;
      diff = -0.02*compass.a.y; // P-制御
      break;
    case 2: // 山登り中
      if ((avex<1500)&&(avex>-1500)) {  // 登頂したら頂上の中心部まで進む
        done = waitfor(150);        // 200ms は要調整
      }
      if (done == 1) {  // 頂上の中心部まで来たら停止
        speed0=0;
        diff =0;
        mode_G = 3;
      } else {
        speed0 = 150;
        diff = -0.02*compass.a.y; // P-制御
      }
      break;
    case 3: // 500ms停止
      speed0 = 0;
      diff = 0;
      done = waitfor(500);
      if ( done == 1 )
        mode_G = 4;
      break;
    case 4: // その場回転で東を向く
      speed0 = 0;
      diff = turnTo(90);        // P-制御
      if (abs(diff)<=25) { //80-100
        diff = 0;
        done = waitfor(500);
        if ( done == 1)
        mode_G = 5;
      }
    case 5: //南
      diff = turnTo(0);        // P-制御
      if (abs(diff)<=25) { //80-100
        diff = 0;
        done = waitfor(500);
        if ( done == 1)
        mode_G = 6;
      }
      break;
    case 6: //にし
      diff = turnTo(-90);        // P-制御
      if (abs(diff)<=25) { //80-100
        diff = 0;
        done = waitfor(500);
        if ( done == 1)
        mode_G = 7;
      }
      break;
    case 7: //北
      diff = turnTo(180);        // P-制御
      if (abs(diff)<=25) { //80-100
        diff = 0;
        done = waitfor(500);
        if ( done == 1)
        mode_G = 8;
      }
    case 8: // その場回転で東を向く
      speed0 = 0;
      diff = turnTo(90);        // P-制御
      if (abs(diff)<=25) { //80-100
        diff = 0;
        done = waitfor(500);
        if ( done == 1)
        mode_G = 9;
      }
      break;
   case 9: //下る
       ;
      //下るまで直進
      speed0 = 150;
      diff = -0.02*compass.a.y; // P-制御
    case 10:
        speed0 = 150;
        diff = 0.02*compass.a.y; // P-制御
        if((avex<1500)&&(avex>-1500)){
          mode_G = 99;
        }
      break;
    case 99: // 停止
      speed0 = 0;
      diff = 0;
      break;
    default:
      break;
  }
  motorL_G = speed0 + diff;
  motorR_G = speed0 - diff;
}


int waitfor( unsigned long period )
{
  static int flagStart = 0; // 0:待ち状態，1:現在計測中
  static unsigned long startTime = 0;

  if ( flagStart == 0 ) { 
    startTime = timeNow_G;
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
