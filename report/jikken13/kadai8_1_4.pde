PImage img;  // Declare variable "a" of type PImage

float x, y, xx,yy;


void setup() {
  size(525, 575);
   // The image file must be in the data folder of the current sketch 
  // to load successfully
  img = loadImage("xymapF.png");  // Load the image into the program  

}
void draw() { //受信した値で描画
 
  image(img, 0, 0);
  //Figure drawn in rect TL =(25,55), BR =(470,560)
 /*
  xx =  ??;
  yy =  ??;
  
  
  fill(255);  
  ellipse(xx,yy,15,15);
*/  
  //red point
  ellipse(405,358,10,10);
  //green point
  ellipse(203,193,10,10);
  //blue point
  ellipse(114,523,10,10);
 
  strokeWeight(5);
  line(405,358,203,193); //R-G
  line(405,358,114,523); //R-G
  line(203,193,114,523); //G-B
  
}
