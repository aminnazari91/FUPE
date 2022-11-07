function [Security, Utility] = CreateMemberFunction()

Security = newfis('Security');

%% Input membership function; Credit
Security = addvar(Security,'input','Credit',[0 1]);
Security = addmf(Security,'input',1,'Low','trimf',[0 .25 .5]);
Security = addmf(Security,'input',1,'Medium','trimf',[.1 .5 .9]);
Security = addmf(Security,'input',1,'High','trimf',[.5 .75 1 ]);

%% Input membership function; Rate
Security = addvar(Security,'input','Rate',[0 1]);
Security = addmf(Security,'input',2,'Low','trimf',[0 .25 .5]);
Security = addmf(Security,'input',2,'Medium','trimf',[.1 .5 .9]);
Security = addmf(Security,'input',2,'High','trimf',[.5 .75 1 ]);

%% Output membership function; Result
Security = addvar(Security,'output','Result',[0 1]);
Security = addmf(Security,'output',1,'Low','trimf',[0 .25 .5]);
Security = addmf(Security,'output',1,'Medium','trimf',[.1 .5 .9]);
Security = addmf(Security,'output',1,'High','trimf',[.5 .75 1 ]);

%% Show membership function
figure(1);
plotmf(Security,'input',1);
figure(2);
plotmf(Security,'input',2);
figure(3);
plotmf(Security,'output',1);
figure(4);
Utility = newfis('Utility');

%% Input membership function; Processing Capacity
Utility = addvar(Utility,'input','CPU',[10000 40000]);
Utility = addmf(Utility,'input',1,'Low','trimf',[10000 17500 25000]);
Utility = addmf(Utility,'input',1,'Medium','trimf',[13000 25000 37000]);
Utility = addmf(Utility,'input',1,'High','trimf',[25000 32500 40000 ]);

%% Input membership function; Memory
Utility = addvar(Utility,'input','Memory',[8192 16*1024]);
Utility = addmf(Utility,'input',2,'Low','trimf',[8192 10240 12288]);
Utility = addmf(Utility,'input',2,'Medium','trimf',[9011 12288 15564]);
Utility = addmf(Utility,'input',2,'High','trimf',[12288 14336 16*1024 ]);

%% Input membership function; BW
Utility = addvar(Utility,'input','Bandwidth',[10000 20000]);
Utility = addmf(Utility,'input',3,'Low','trimf',[ 10000 12500 15000]);
Utility = addmf(Utility,'input',3,'Medium','trimf',[12500 15000 17500]);
Utility = addmf(Utility,'input',3,'High','trimf',[15000 17500 20000 ]);

%% Input membership function; TaskLength
Utility = addvar(Utility,'input','TaskLength',[500 5000]);
Utility = addmf(Utility,'input',4,'Low','trimf',[500 1525 2750]);
Utility = addmf(Utility,'input',4,'Medium','trimf',[950 2750 4550]);
Utility = addmf(Utility,'input',4,'High','trimf',[2750 3875 5000]);

%% Output membership function; Result
Utility = addvar(Utility,'output','Result',[0 1]);
Utility = addmf(Utility,'output',1,'Low','trimf',[0 .25 .5]);
Utility = addmf(Utility,'output',1,'Medium','trimf',[.1 .5 .9]);
Utility = addmf(Utility,'output',1,'High','trimf',[.5 .75 1 ]);

figure(5);
plotmf(Utility,'input',1);
figure(6);
plotmf(Utility,'input',2);
figure(7);
plotmf(Utility,'input',3)
figure(8);
plotmf(Utility,'input',4)
figure(9);
plotmf(Utility,'output',1)
end