X = csvRead('data190614152700.csv'); //データの読み込み
T = X(:,1)*0.04; //サンプリング周期0.04[sec]
U = X(:,3); //duty比
Y = X(:,2); //モータ回転速度[rpm]
Yf = X(:,4); //平滑化されたモータ回転速度[rpm]
N = size(U,1); //データ数
K = 34000; //ゲイン
Ts = 0.4; //時定数
uave = U'*ones(N,1)/N; //Uの平均(duty比の平均)
yave = Y'*ones(N,1)/N; //Yの平均(モータ回転速度の平均)
U1 = U - ones(N,1)*uave; //オフセット処理
s = poly(0,'s'); //sをラプラス変換のsとして使うおまじない
Gs = syslin('c',K,1+Ts*s); //伝達関数Gs = K(1+Ts*s)の定義
Yhat1 = csim(U1' / 100 , T', Gs); //線形システムのシミュレーション(時間応答)
Yhat = Yhat1' + ones(N,1)*yave; //オフセット処理
figure(1);
plot(T,Y,'b.');
plot(T,Yf,'r-');
plot(T,Yhat,'g:'); //描画
xs2eps(1,"kadai5-1-3-simu.eps");
