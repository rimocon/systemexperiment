X = csvRead('data6-1-1.csv');
T = X(:,1)*0.04;
Y = X(:,2);
U = X(:,3);
Ref = X(:,4);

figure(1);
plot(T,Y,'r.-');
plot(T,Ref,'g.-');
xs2eps(1,"kadai6-1-1-1.eps");
figure(2);
plot(T,U,'b.-');
a = get("current_axes");
a.data_bounds = [0,35;40,60];
xs2eps(2,"kadai6-1-1-2.eps");
