import processing.serial.*;
Serial port;

int ax = 0, ay = 0, az = 0;
int mx = 0, my = 0, mz = 0;
int CX=250, CY=250;
int mode_G = 0;
int red_G = 0, green_G = 0, blue_G = 0;
int motorL_G = 0, motorR_G = 0;

void setup() {
   size(1000,500);
   //port = new Serial(this, "/dev/cu.usbmodem1411",9600);
   port = new Serial(this, "/dev/cu.usbserial-A90177EP",9600);
   port.clear();
}

void line3D(float x0, float y0,float z0,float x1,float y1,float z1) {
  float X0 = CX+y0-0.5*x0, Y0 = CY + 1.7320508*x0/2-z0;
  float X1 = CX+y1-0.5*x1, Y1 = CY + 1.7320508*x1/2-z1;
  line(X0,Y0,X1,Y1);
}

void drawVec(float x, float y, float z) {
  stroke(128);
  line3D(0,0,0,250,0,0);  line3D(0,0,0,0,250,0);  line3D(0,0,0,0,0,250);
  stroke(0);
  line3D(0,0,0,x,y,0);
  line3D(x,y,0,x,y,z);
  line3D(0,0,0,x,0,0);
  line3D(x,0,0,x,y,0);
  line3D(x,y,0,0,y,0);
  line3D(0,y,0,0,0,0);
  stroke(255,0,0);  line3D(0,0,0,x,y,z);
  fill(0);  text(x,CX-80,490);  text(y,CX,490);  text(z,CX+80,490);
}


void draw() {
  noStroke();  fill(255);  rect(0,0,1000,500);
  // Draw Acceleration vector
  CX = 250;
  drawVec(ax/100,ay/100,az/100);
  // Draw Magnetic flux vector
  CX = 750;
  drawVec(mx,my,mz);
  // Draw Heading direction
  CX = 600;
  float scale = 0.5;
  line(CX-scale*my,100+scale*mx,CX+scale*my,100-scale*mx);
  line(CX+scale*my,100-scale*mx,CX+0.6*scale*my+0.2*scale*mx,100-0.6*scale*mx+0.2*scale*my);
  line(CX+scale*my,100-scale*mx,CX+0.6*scale*my-0.2*scale*mx,100-0.6*scale*mx-0.2*scale*my);
}

int read2byte(Serial p) {
  int x = p.read();  x <<= 8;   x |=p.read();
  if (x>32757) x -= 65536;
  return x;
}

void serialEvent(Serial p) {
  if (p.available() >=13 ) {
    if (p.read() == 'H') {
      mode_G = p.read();
      red_G = p.read();  green_G = p.read();  blue_G = p.read();
      ax = p.read()-128;      ay = p.read()-128;      az = p.read()-128;
      mx = p.read()-128;      my = p.read()-128;      mz = p.read()-128;
      motorL_G = (p.read() - 128) * 2;
      motorR_G = (p.read() - 128) * 2;
    }
  }
}
