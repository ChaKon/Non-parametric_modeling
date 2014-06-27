close all;
clear all;
tic;
% running gurls package
run('D:\Education\4rth Semester\Thesis Main Work\Gurls\GURLS-master\GURLS-master\gurls\utils\gurls_install.m');
disp('running gurls package .....');
dataset = load('icubdyn.dat'); % loading data set
exp_dataset = dataset(:,:);
[rows cols] = size (exp_dataset);
train_rows = round (0.70*rows);
Xtr = exp_dataset(1:train_rows, 1:12);
ytr = exp_dataset(1:train_rows,13:18);
Xte = exp_dataset(train_rows+1:rows, 1:12);
yte = exp_dataset(train_rows+1:rows, 13:18);
name = 'randomfeatstest';
opt = defopt(name);
opt.seq = {'split:ho','paramsel:horandfeats','rls:randfeats','pred:randfeats','perf:rmse','perf:macroavg'};
opt.process{1} = [2,2,2,0,0,0];
opt.process{2} = [3,3,3,2,2,2];
normXtr=1/normest(Xtr);
Xtr = Xtr .* normXtr;
normXte = 1/normest(Xte);
Xte = Xte .* normXte;
gurls(Xtr, ytr, opt, 1)
gurls(Xte, yte, opt, 2)
% computing error
error_rmse = (ans.perf.rmse)/rows;
error_macroavg = (ans.perf.forho);

toc