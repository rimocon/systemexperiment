void setup() {
  pinMode(9, OUTPUT) ; // RED 9 番ピン
  pinMode(11, OUTPUT) ; // RED 9 番ピン
  pinMode(10, OUTPUT) ; // RED 9 番ピン
  analogWrite(9, 0); // PWM duty 比
  analogWrite(10,0);
  analogWrite(11,0);
}
void loop() {
  analogWrite(9, 255); // PWM duty 比
  delay(500); //点滅周期は各自で調整
  analogWrite(9, 0);
  delay(500); //点滅周期は各自で調整
  analogWrite(11, 255); // PWM duty 比
  delay(500); //点滅周期は各自で調整
  analogWrite(11, 0);
  delay(500); //点滅周期は各自で調整
  analogWrite(10, 255); // PWM duty 比
  delay(500); //点滅周期は各自で調整
  analogWrite(10, 0);
  delay(500); //点滅周期は各自で調整

}
