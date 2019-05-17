int thisByte = 65; //送信するデータ
int i; //データを1回だけ送信するためのカウンタ
void setup() {
  Serial.begin(9600); //転送レート9600に設定
  i = 0; //カウンタの初期設定
}

void loop() {
  if( i >= 1){}else{ //1回だけデータを送信
    Serial.write(thisByte); //ASCIIコード
    Serial.println(); //改行
    Serial.println(thisByte); //10進数
    Serial.println(thisByte,HEX); //16進数
    Serial.println(thisByte,BIN); //2進数
    i++; //カウントアップ
  }
}
