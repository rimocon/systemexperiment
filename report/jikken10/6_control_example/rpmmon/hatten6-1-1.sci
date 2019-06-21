colordef('white');
X = csvRead('datahatten6-1-1-u00.csv');
T = X(:,1)*0.04;
Y = X(:,2);
U = X(:,3);
Ref = X(:,4);

X1 = csvRead('datahatten6-1-1-y00.csv');
T1 = X1(:,1)*0.04;
Y1 = X1(:,2);
U1 = X1(:,3);
Ref1 = X1(:,4);

X2 = csvRead('datahatten6-1-1-u00y00.csv');
T2 = X2(:,1)*0.04;
Y2 = X2(:,2);
U2 = X2(:,3);
Ref2 = X2(:,4);


figure(1);
//fig1
subplot(2,3,1);
plot(T,Y,'r-');
plot(T,Ref,'g-');
xtitle("U0 = 0");
//fig4
subplot(2,3,4);
plot(T,U,'b-');
a = get("current_axes");
a.data_bounds = [0,40;40,60];
xtitle("U0 = 0");

//fig2
subplot(2,3,2);
plot(T1,Y1,'r-');
plot(T1,Ref1,'g-');
xtitle("Y0 = 0");
//fig5
subplot(2,3,5);
plot(T1,U1,'b-');
a = get("current_axes");
a.data_bounds = [0,40;40,60];
xtitle("Y0 = 0");
//fig3
subplot(2,3,3);
plot(T2,Y2,'r-');
plot(T2,Ref2,'g-');
xtitle("U0=0,Y0=0");
//fig6
subplot(2,3,6);
plot(T2,U2,'b-');
a = get("current_axes");
a.data_bounds = [0,40;40,60];
xtitle("U0=0,Y0=0");

xs2eps(1,"hatten6-1-1.eps");
