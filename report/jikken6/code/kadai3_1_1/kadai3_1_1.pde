int xn = 10;
int yn = 10;

int x,y;

size(600,600);
background(255); //背景白

stroke(0); //線の色黒
for(int i =0; i<=yn; i++){ //格子の横線
  y =  i*height/yn; //線のy座標
  line(0,y,width,y);
}

for(int i = 0; i<= xn; i++){ //格子の縦線
  x = i*width/xn; //線のx座標
  line(x,0,x,height);
}

stroke(255,0,0);
for(int i_c =0; i_c<xn; i_c++){ //i_cはマス目のインデックス
  for(int i_r = 0; i_r < yn; i_r++){
    x = width/(2*xn) + i_c*width/xn; //30 + 60*i_c
    y = height/(2*yn) + i_r*height/yn; //30 + 60*i_r
    ellipse(x,y,width/xn,height/yn);
  }
}
