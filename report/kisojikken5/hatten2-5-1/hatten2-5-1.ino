void setup() {
  Serial.begin(9600); //転送レート9600に設定
}

void loop() {
  if(Serial.available() > 0){ //パソコンからデータを受信
    int receive = 0; //受信データ
    int birthday[4] = {0}; //表示用配列
    int kekka = 0;
    int i = 0; //配列の要素カウント用
    while(1){
      if(Serial.available() > 0){ //受信したら
        receive = Serial.read();
        if( 47 < receive && receive <58){ //受信データが数字のASCIIコードの時
          receive -= 48; //数字に変換
          birthday[i] = receive; //配列に入れる
          i++; //配列の要素をずらす
        }
        if( receive == 10){ //改行が来たら
          break; //ループを抜ける
        }
      }
    }
    birthday[2] += birthday[0]; //誕生日の2桁目に誕生月の2桁目を足す
    if (birthday[3] + birthday[1] >= 10){//もし誕生日の1桁目と誕生月の1桁目の和が10以上なら
      birthday[2]++; //繰り上げで誕生日の2桁目に1足す
      birthday[3] += birthday[1] -10; //誕生日の1桁目は足した数-10
    }
    else{ //誕生日の1桁目と誕生月の1桁目の和が10未満なら
      birthday[3] += birthday[1]; //誕生日の1桁目に誕生月の1桁目を足す
    }
    for ( i = 0; i < 4 ; i++){
      Serial.print(birthday[i]); //シリアルモニタに配列の要素を表示
    }
    Serial.println(); //改行
  }
}
