close all;
clear all;
%%%%%%%%%%% Pre porcessing
% running gurls package
run('D:\Education\4rth Semester\Thesis Main Work\Gurls\GURLS-master\GURLS-master\gurls\utils\gurls_install.m');
disp('running gurls package .....');
% dataset = load('rand_icubdyn1.dat'); % loading data set


% Xte & yte are used for testing 
X_test = load('Xte_5psmall.txt');
y_test = load('yte_5psmall.txt');

[test_rows test_cols] = size(X_test);
% for training & validation
X_train_val = load('Xtr_5psmall.txt');
y_train_val = load('ytr_5psmall.txt');

%%%%%%%Normalizing data
normXtr = 1/normest( X_train_val );
X_train_val = X_train_val.*normXtr;
normXte = 1/normest( X_test );
X_test = X_test.*normXte;
% normytr = 1/normest( y_train_val );
% y_train_val = y_train_val.*normytr;
% normyte = 1/normest( y_test );
% y_test = y_test.*normyte;

%%%% Batch with randomfeats kernel     
ttrain = tic;
name = 'randomfeatstest';
opt = defopt(name);
opt.seq = {'split:ho','paramsel:horandfeats','rls:randfeats','pred:randfeats','perf:rmse','perf:macroavg'};
opt.process{1} = [2,2,2,0,0,0];
opt.process{2} = [3,3,3,2,2,2];
opt.hoproportion = 0.4;
%%%%%%%%%%%%%%%%% For changing cross folds and random features %%%%%%%%%%%%
% opt.randfeats.D = 750;
opt.nholdouts = 5;
%%%%%%%%%%%%%%%%% For changing cross folds and random features %%%%%%%%%%%%
opt.hoperf = @perf_rmse;
% opt.nlambda = 3;
% opt.nsigma = 3;
% for training
batch_randfeatures_training = gurls(X_train_val, y_train_val, opt, 1);
ttrain_stop = toc(ttrain);
ttest = tic;
% for testing
batch_randfeatures_test = gurls(X_test, y_test, opt, 2);
% computing error
error_rmse = (batch_randfeatures_test.perf.rmse)/test_rows;
error_macroavg = (batch_randfeatures_test.perf.forho);
ttest_stop = toc(ttest);
% mapping random features for approximating gaussian kernel of both training and testing for recursive
tchol_tr_start = tic;
X_train_val_map = rp_apply_real(X_train_val',batch_randfeatures_training.rls.proj)';
X_test_map = rp_apply_real(X_test',batch_randfeatures_test.rls.proj)';
% disp (' Enter choice --------->');
% disp (' 1 for Cholesky rank 1 update ');
% disp (' anykey for sherman morrison update ');
%choice = input(' 1 for cholesky....! Any key for sherman morrison ---> ');
choice =2;
switch (choice == 1)
    case 1 
disp(' recursive cholesky ..............!');
name = 'recursive_cholesky';
cholesky_rec = defopt(name);
% rcecursive cholesky update
cholesky_rec.seq = {'split:ho', 'paramsel:loocvprimal','rls:primalrecinitcholesky'};
cholesky_rec.process{1} = [2,2,2];
cholesky_rec.hoproportion = 0.4;
%%%%%%%%%%%%%%%%%%%% For changing cross folds and random features %%%%%%%%%
cholesky_rec.randfeats.D = 750;
cholesky_rec.nholdouts = 5;
%%%%%%%%%%%%%%%%%%% For changing cross folds and random features %%%%%%%%%%
% choosing 2500 sample for paramsel and training
n0 = 2500;
X_paramsel = X_train_val_map(1:n0,:);
y_paramsel = y_train_val(1:n0,:);
% parameter selection & training with 2500 samples
cholesky_rec = gurls(X_paramsel, y_paramsel, cholesky_rec,1);
cholesky_rec.hoperf = @perf_rmse;
% updating estimator recursively
nend = size(X_train_val,1);
for j = (n0+1):nend
    X_new = X_train_val_map(j,:);
    y_new = y_train_val(j,:);
    %j % just to know which iteration is running
    cholesky_rec.rls = rls_primalrecupdatecholesky(X_new,y_new, cholesky_rec);
end
tchol_tr_stop = toc(tchol_tr_start);
tchol_tst_start = tic;
RLS_Cholesky_pred = pred_primal(X_test_map, y_test, cholesky_rec); 
error_recrls_cholesky = sqrt(sum((RLS_Cholesky_pred-y_test).^2));
error_recrls_cholesky = error_recrls_cholesky/test_rows;
tchol_tst_stop = toc(tchol_tst_start);
    otherwise
 tsm_tr_start = tic;       
disp (' Shermon Morrison recursive rls ...........!');
name = 'recursive_smorrison';
smorrison_rec = defopt(name);
smorrison_rec.seq = {'split:ho', 'paramsel:loocvprimal','rls:primalrecinit'};
smorrison_rec.process{1} = [2,2,2];
smorrison_rec.hoproportion = 0.4;
%%%%%%%%%%%%%%%%%%% For changing cross folds and random features %%%%%%%%%%
smorrison_rec.randfeats.D = 750;
smorrison_rec.nholdouts = 5;
%%%%%%%%%%%%%%%%%% For changing cross folds and random features %%%%%%%%%%%
% choosing 2500 sample for paramsel and training
n0 = 2500;
X_paramsel = X_train_val_map(1:n0,:);
y_paramsel = y_train_val(1:n0,:);
nend = size(X_train_val,1);
% parameter selection & training with 2500 samples (initial batch)
smorrison_rec = gurls(X_paramsel, y_paramsel, smorrison_rec,1);
smorrison_rec.hoperf = @perf_rmse;
% updating estimator recursively
for j = (n0+1):nend
    X_new = X_train_val_map(j,:);
    y_new = y_train_val(j,:);
    %j % just to know which interation is runing
    smorrison_rec.rls = rls_primalrecupdate(X_new,y_new, smorrison_rec);
end
tsm_tr_stop = toc(tsm_tr_start);
tsm_tst_start = tic;
% Computing error
RLS_smorrison_pred = pred_primal(X_test_map, y_test, smorrison_rec); 
error_recrls_smorrison = sqrt(sum((RLS_smorrison_pred-y_test).^2));
error_recrls_smorrison = error_recrls_smorrison/test_rows;
tsm_tst_stop = toc(tsm_tst_start);
end
