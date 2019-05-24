int xn = 10; //分割数
int yn = 10; //分割数
int i_c; //楕円を描くマス目番号
int i_r; //楕円を描くマス目番号
int flag_upper_right = 0;
int flag_upper_left = 0;
int flag_down_right =0;
int flag_down_left = 0;
void setup(){
  size(600,600);
  frameRate(20);
  i_c = 0;
  i_r = 0;
}
void draw()
{
  int x,y;
  background(255); //背景白
  stroke(0); //線の色黒
  for(int i = 0; i<= yn; i++){
    y =  i*height/yn; //線のy座標
    line(0,y,width,y);
  }
  for(int i = 0; i<= xn; i++){ //格子の縦線
    x = i*width/xn; //線のx座標
    line(x,0,x,height);
  }
  stroke(255,0,0);
  x = width/(2*xn) + i_c*width/xn; //30 + 60*i_c
  y = height/(2*yn) + i_r*height/yn; //30 + 60*i_r
  ellipse(x,y,width/xn,height/yn);
  //楕円を描くマス目番号の更新
  if ( i_c == 0 && i_r == 0){ //
    flag_upper_left = 1;
    flag_upper_right = 0;
    flag_down_left = 0 ;
    flag_down_right = 0;
    println("upperleftnow");
  }
  if ( i_c == xn-1 && i_r == 0){
    flag_upper_left = 0;
    flag_upper_right = 1;
    flag_down_left = 0 ;
    flag_down_right = 0;
    println("upperrightnow");
  }
  if ( i_c == 0 && i_r == yn-1){
    flag_upper_left = 0;
    flag_upper_right = 0;
    flag_down_left = 1 ;
    flag_down_right = 0;
    println("downleftnow");
  }
  if ( i_c == xn-1 && i_r == yn-1){
    flag_upper_left = 0;
    flag_upper_right = 0;
    flag_down_left = 0 ;
    flag_down_right = 1;
    println("downrightnow");
  }
  if(flag_upper_left == 1){
    i_c++;
  }
  if(flag_upper_right == 1){
    i_c--;
    i_r++;
  }
  if(flag_down_left == 1){
    i_c++;
  }
  if(flag_down_right == 1){
    i_c--;
    i_r--;
  }
  
}
