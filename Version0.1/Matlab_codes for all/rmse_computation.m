% Open files

yte = dlmread('yte_100psmall.txt', ',');
yte = yte( : , 1:6);
[row col] = size(yte);

% pred_RecRLS = dlmread('pred_RecRLS.txt', ' ');
% pred_RecRLS = pred_RecRLS( : , 1:6);

pred_RecRLS_Loocv = dlmread('kernel.txt', ' ');
pred_RecRLS_Loocv = pred_RecRLS_Loocv( : , 1:6);

pred_RecRLS_siglamHO = dlmread('kernel1.txt', ' ');
pred_RecRLS_siglamHO = pred_RecRLS_siglamHO( : , 1:6);

% Compute RMSE

%1
%rmse_RecRLS = sqrt(sum((pred_RecRLS-yte).^2)./size(yte, 1));

%2
rmse_RecRLS_Loocv = sqrt(sum((pred_RecRLS_Loocv-yte).^2)./size(yte, 1));

%3
rmse_RecRLS_siglamHO = sqrt(sum((pred_RecRLS_siglamHO-yte).^2)./size(yte, 1));

% Text files save

%dlmwrite('rmse_RecRLS.txt',rmse_RecRLS)
dlmwrite('rmse_RecRLS_Loocv.txt',rmse_RecRLS_Loocv)
dlmwrite('rmse_RecRLS_siglamHO.txt',rmse_RecRLS_siglamHO)