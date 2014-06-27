function [rls] = rls_primalrecupdatecholesky (X, y, opt)

% rls_primalrecupdate(X,y,opt)
% computes a classifier for the primal formulation of RLS, using a
% recursive update, starting from an initial estimator found in OPT.RLS.
%
% INPUTS:
% -X: input data matrix
% -y: labels matrix
% -OPT: struct of options with the following fields:
%   fields that need to be set through previous gurls tasks:
%		- rls.W (set by the rls_primalrecinit)
%       - rls.Cinv (set by rls_primalrecinit)
% 
%   For more information on standard OPT fields
%   see also defopt
% 
% OUTPUT: struct with the following fields:
% -W: matrix of coefficient vectors of rls estimator for each class
% -Cinv: inverse of the regularized kernel matrix in the primal space
% -C: empty matrix
% -X: empty matrix

W = opt.rls.W;
R = opt.rls.R;
b = opt.rls.b;

% Sequence of rank-1 updates by application of Cholesky rank-1 updates
for i = 1:size(X,1);
    
    % Update b
    b = b + X(i,:)'*y(i,:);
    
    % Update Cholesky factor R
    R = cholupdate(R,X(i,:)');
    
    % TEMP: rewrite for efficiency...
    %s = mldivide(R,b)';
    W = mldivide(R,(mldivide(R',b)));
end

rls.b = b
rls.W = W;
rls.C = [];
rls.X = [];
rls.R = R;


