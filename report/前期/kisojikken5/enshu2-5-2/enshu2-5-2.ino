int val; //送信するデータ
int i; //データを1回だけ送信するためのカウンタ
void setup() {
  Serial.begin(9600); //転送レート9600に設定
  val = 32; //valの初期設定
}

void loop() {
  if(val <= 127){ //32から127までのデータを送信
    Serial.write(val); //ASCIIコード
    Serial.print(","); //,を送信
    Serial.println(val); //valの値を文字に変換した結果+改行
    val++; //valのカウントアップ
  }else{}
}
