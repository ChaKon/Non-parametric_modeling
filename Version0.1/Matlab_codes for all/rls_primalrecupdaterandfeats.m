function [rls] = rls_primalrecupdaterandfeats (X, y, opt)

% rls_primalrecupdate(X,y,opt)
% computes a classifier for the primal formulation of RLS, using a
% recursive update and a random features mapping, starting from an initial 
% estimator found in OPT.RLS.
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


% Random features mapping
% (using the fixed projections contained in opt.rls.proj, previously drawn
%  by rls_primalrecinitrandfeats)
G = rp_apply_real_custom(X',opt.rls.proj)';    % RF mapping

W = opt.rls.W;
Cinv = opt.rls.Cinv;

% Sequence of rank-1 updates by application of the Sherman-Morrison formula
for i = 1:size(G,1);
    Cx = Cinv*G(i,:)';
    xCx = G(i,:)*Cx;
    Cinv = Cinv - Cx*Cx'./(1+xCx);
    W = W +(Cx*(y(i,:)-G(i,:)*W))./(1+xCx);
end

rls.W = W;
rls.C = [];
rls.X = [];
rls.Cinv = Cinv;
rls.proj = opt.rls.proj;
