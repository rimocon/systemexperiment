#include <Wire.h>
#include <LSM303.h>

LSM303 compass;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  compass.init();
  compass.enableDefault();

  compass.read();
  compass.m_min.x = compass.m.x; compass.m_max.x = compass.m_min.x+1;
  compass.m_min.y = compass.m.y; compass.m_max.y = compass.m_min.y+1;
  compass.m_min.z = compass.m.z; compass.m_max.z = compass.m_min.z+1;
}

void write2byte(int x) {
  Serial.write(x>>8);
  Serial.write(x&255);
}

void loop() {
  float mx,my,mz;

  compass.read();
 
  Serial.write('H');
  write2byte(compass.a.x);  write2byte(compass.a.y);  write2byte(compass.a.z);

  mx = compass.m.x;  my = compass.m.y;  mz = compass.m.z;

  /* Calibration */
  compass.m_min.x=min(compass.m_min.x,mx); compass.m_max.x=max(compass.m_max.x,mx);
  compass.m_min.y=min(compass.m_min.y,my); compass.m_max.y=max(compass.m_max.y,my);
  compass.m_min.z=min(compass.m_min.z,mz); compass.m_max.z=max(compass.m_max.z,mz);
      
  mx = map(mx,compass.m_min.x,compass.m_max.x,-128,127);
  my = map(my,compass.m_min.y,compass.m_max.y,-128,127);
  mz = map(mz,compass.m_min.z,compass.m_max.z,-128,127);  
 /* end of Calibration */

  write2byte((int)mx);  write2byte((int)my);  write2byte((int)mz);

  delay(100);
}
