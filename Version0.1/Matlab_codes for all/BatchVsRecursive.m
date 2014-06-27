close all;
clear all;
tic;
% running gurls package
run('D:\Education\4rth Semester\Thesis Main Work\Gurls\GURLS-master\GURLS-master\gurls\utils\gurls_install.m');
disp('running gurls package .....');
dataset = load('icubdyn.dat'); % loading data set
exp_dataset = dataset(:,:);
[rows cols] = size (exp_dataset);
X_cols = 12;
train_rows = round (0.80*rows); % spliting data set into 80% for training & remaining dataset for testing
X = exp_dataset(:, 1:X_cols); % input data set 
y = exp_dataset(:,X_cols+1:end); % output dataset
% normalising input data
normlisedX=1/normest(X);
norm_X = X .* normlisedX;
% Xte & yte are used for testing 

X_test = X(train_rows+1:end,:);
y_test = y(train_rows+1:end,:);
[test_rows test_cols] = size(X_test);
iterations = 4;
batch_error_randfeats = [];
error_cholesky = [];
error_smorrison = [];
%for i =1:iterations
    %new_trsize = train_rows/(iterations+1-i);
    new_trsize = train_rows;
    new_split_size = new_trsize/2; 
    % for training
    X_train = exp_dataset(1:new_split_size,1:X_cols);
    y_train = exp_dataset(1:new_split_size,X_cols+1:end);
    % validation
    X_validation = exp_dataset(new_split_size+1:new_trsize,1:X_cols);
    y_validation = exp_dataset(new_split_size+1:new_trsize,X_cols+1:end);
    
name = 'randomfeatstest';
opt = defopt(name);
opt.seq = {'split:ho','paramsel:horandfeats','rls:randfeats','pred:randfeats','perf:rmse','perf:macroavg'};
opt.process{1} = [2,2,2,0,0,0];
opt.process{2} = [3,3,3,2,2,2];

batch_randfeatures_training = gurls(X_train, y_train, opt, 1);
batch_randfeatures_validation = gurls(X_validation, y_validation, opt, 2);
batch_randfeatures_test = gurls(X_test, y_test, opt, 2);
% computing error
error_rmse = (batch_randfeatures_test.perf.rmse)/test_rows;
error_macroavg = (batch_randfeatures_test.perf.forho);
X_train_map = rp_apply_real(X_train',batch_randfeatures_training.rls.proj)';
X_validation_map = rp_apply_real(X_validation',batch_randfeatures_validation.rls.proj)';
X_test_map = rp_apply_real(X_test',batch_randfeatures_test.rls.proj)';
disp(' recursive cholesky ..............!');
name = 'recursive_cholesky';
cholesky_rec = defopt(name);
cholesky_rec.seq = {'split:ho', 'paramsel:hoprimal','rls:primalrecinitcholesky'};
cholesky_rec.process{1} = [2,2,0];
cholesky_rec.process{2} = [3,3,2];
% training
cholesky_rec = gurls(X_train_map, y_train, cholesky_rec,1);
% updating estimator recursively
n0 = size(X_train_map,1);
nend = size(X_validation_map,1);
cholesky_rec = gurls(X_validation_map(1, :), y_validation(1, :), cholesky_rec, 2); 
for j = 2:nend
    X_new = X_validation_map(j,:);
    y_new = y_validation(j,:);
    opt.rls = rls_primalrecupdatecholesky(X_new,y_new, cholesky_rec);
end
%opt.rls = rls_primalrecupdatecholesky(X_validation_map(2:new_split_size,:),y_validation(2:new_split_size,:), cholesky_rec);
RLS_Cholesky_pred = pred_primal(X_test_map, y_test, cholesky_rec); 
error_recrls_cholesky = sqrt(sum((RLS_Cholesky_pred-y_test).^2));
error_recrls_cholesky = error_recrls_cholesky/test_rows;

%end
disp (' Shermon Morrison recursive rls ...........!');
name = 'recursive_smorrison';
smorrison_rec = defopt(name);
smorrison_rec.seq = {'split:ho', 'paramsel:hoprimal','rls:primalrecinit'};
smorrison_rec.process{1} = [2,2,0];
smorrison_rec.process{2} = [3,3,2];
% training
smorrison_rec = gurls(X_train_map, y_train, smorrison_rec,1);
% updating estimator recursively
n0 = size(X_train_map,1);
nend = size(X_validation_map,1);
smorrison_rec = gurls(X_validation_map(1, :), y_validation(1, :), smorrison_rec, 2); 
% for k = 1:nend
%     X_new = X_validation(k,:);
%     y_new = y_validation(k,:);
%     opt.rls = rls_primalrecupdate(X_new,y_new, smorrison_rec);
% end
opt.rls = rls_primalrecupdate(X_validation_map(2:new_split_size,:),y_validation(2:new_split_size,:), smorrison_rec);
RLS_smorrison_pred = pred_primal(X_test_map, y_test, smorrison_rec); 
error_recrls_smorrison = sqrt(sum((RLS_smorrison_pred-y_test).^2));
error_recrls_smorrison = error_recrls_smorrison/test_rows;
toc