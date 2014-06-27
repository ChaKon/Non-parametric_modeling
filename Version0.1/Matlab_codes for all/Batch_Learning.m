close all;
clear all;
run('D:\Education\4rth Semester\Thesis Main Work\Gurls\GURLS-master\GURLS-master\gurls\utils\gurls_install.m');
disp('running gurls package .....');
name = 'Batch_Learning';
opt=defopt(name);
% Data = load('icubdyn.dat');
% [dr dc] = size(Data);
% tr = 15000;
% te = 5000;
% Xtr = Data(1:tr,1:12);
% Xte = Data(tr:tr+te,1:12);
% ytr = Data(1:tr,13:18);
% yte = Data(tr:tr+te,13:18);
a= load('Sarcos/Sarcos_data.mat');
Xtr = a.X_train;
Xte = a.X_test;
ytr = a.Y_train;
yte = a.Y_test;
% Xtr = load('Xtr_2psmall.txt');
% Xte = load('Xte_2psmall.txt');
% ytr = load('ytr_2psmall.txt');
% yte = load('yte_2psmall.txt');
% normXtr = 1/normest( Xtr );
% Xtr = Xtr.*normXtr;
% normXte = 1/normest( Xte );
% Xte = Xte.*normXte;

[rows cols] = size(yte);
disp('1 --> for linear case');
disp('2 --> for kernel case');
choice = input ('Enter choice -- >');
if (choice == 1)
    option1 = 'split:ho';
    disp('1 --> for loocvprimal');
    disp('2 --> for hoprimal');
    disp('default --> for fixlambda');
    select1 = input('Enter choice for selecting paramsel -->');
    switch(select1)
        case 1 
            option2 = 'paramsel:loocvprimal';
        case 2
            option2 = 'paramsel:hoprimal';
        otherwise
            option2 = 'paramsel:fixsiglam';
    end
    disp(' 1 --> for rlsprimal');
    disp(' default --> rlsauto');
    select2 = input('Enter input for optimizer -->');
    switch(select2)
        case 1 
            option3 = 'rls:primal';
        otherwise
            option3 = 'rls:auto';
    end
    option4 = 'pred:primal';
    disp(' 1 --> for rmse measure');
    disp(' 2 --> for macroavg');
    disp('default --> rmse');
    select3 = input('Enter input for performance measure -->');
    switch(select3)
        case 1 
            option5 = 'perf:rmse';
        case 2
            option5 = 'perf:macroavg';
        otherwise
            option5 = 'perf:rmse';
    end     
elseif (choice ==2)
option1 = 'split:ho';
disp('1 --> paramsel:fixsiglam : for kernel case');
disp('2 --> paramsel:hodual : for kernel case');
disp('3 --> paramsel:siglam : for kernel case');
disp('4 --> paramsel:siglamho : for kernel case');
disp('Default --> Any key (paramsel:loocvprimal)');
select1 = input('Enter option for parameter selection -->');
switch(select1)
    case 1
        option2 = 'paramsel:fixsiglam';
    case 2
        option2 = 'paramsel:hodual';
    case 3
        option2 = 'paramsel:siglam';
    case 4
        option2 = 'paramsel:siglamho';
    otherwise
        option2 = 'paramsel:loocvprimal';
end
disp('for kernel selection');
disp(' 1 --> for rbf');
disp(' 2 --> for chisqurredkernel');
select2 = input('Enter option for kernel selection -->');
switch(select2)
    case 1
        option3 = 'kernel:rbf';
    case 2 
        option3 = 'kernel:chisquarred';
end
disp(' 1 --> for rlsprimal');
disp(' 2 --> for rlsdual');
disp(' default --> rlsauto');
select3 = input('Enter input for optimizer -->');
switch(select3)
    case 1 
        option4 = 'rls:primal';
    case 2
        option4 = 'rls:dual';
    otherwise
        option4 = 'rls:auto';
end
option5 = 'predkernel:traintest';
disp(' 1 --> for primal ');
disp(' 2 --> for dual ');
disp(' default --> for primal');
select4 = input('Enter input for predicting output -->');
switch(select4)
    case 1 
        option6 = 'pred:primal';
    case 2 
        option6 = 'pred:dual';
    otherwise
        option6 = 'pred:primal';
end
disp(' 1 --> for rmse measure');
disp(' 2 --> for macroavg');
disp('default --> rmse');
select5 = input('Enter input for performance measure -->');
switch(select5)
    case 1 
        option7 = 'perf:rmse';
    case 2
        option7 = 'perf:macroavg';
    otherwise
        option5 = 'perf:rmse';
end
else 
    % For linear kernel because its task implementation is different from
    % RBF
    option1 = 'split:ho';
    option2 = 'kernel:linear';
    option3 = 'paramsel:siglamho';
    option4 = 'rls:dual';
    option5 = 'pred:dual';
    option6 = 'perf:rmse';
    option7 = 'perf:macroavg';
end

if(choice == 1)
    opt.seq = {option1,option2,option3,option4,option5};
    opt.process{1} = [2,2,2,0,0];
    opt.process{2} = [3,3,3,2,2];
else
    opt.seq = {option1,option2,option3,option4,option5,option6,option7};
    opt.process{1} = [2,2,2,2,0,0,0];
    opt.process{2} = [3,3,3,3,2,2,2];
end
train_start = tic;
opt.hoproportions = 0.4;
opt.hoperf = @perf_rmse;
% opt.nholdouts = 5;
% % opt.nlambda = 3;
% % opt.nsigma = 3;
gurls(Xtr,ytr,opt,1);
train_stop = toc(train_start);
test_start = tic;
gurls(Xte,yte,opt,2);
rmse_error = ans.perf.rmse/rows;
test_stop = toc(test_start);