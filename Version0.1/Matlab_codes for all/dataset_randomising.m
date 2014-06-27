close all;
clear all;
Dataset = load('icubdyn.dat');
[rows cols] = size(Dataset);
rand_icubdyn = Dataset(randperm(rows),:);
save('rand_icubdyn4.txt','rand_icubdyn', '-double')

% test
% ex = [1,2,3;4,5,6;7,8,9;10,11,12];
% [r c] = size(ex);
% rand_ex = ex(randperm(r),:);



