X = csvRead('data523.csv');
T = X(:,1)*0.04;
Y = X(:,2);
U = X(:,3);
Yf = X(:,4);

figure(1);
plot(T,Y,'r.-');
xs2eps(1,"kadai5-2-3-1.eps");

figure(2);
plot(T,U,'b.-');
a = get("current_axes");
a.data_bounds = [0,0;40,50];
xs2eps(2,"kadai5-2-3-2.eps");

figure(3);
plot(T,Yf,'g.-');
//b = get("current_axes");
//b.data_bounds = [0,0;40,50];
xs2eps(3,"kadai5-2-3-3.eps");
