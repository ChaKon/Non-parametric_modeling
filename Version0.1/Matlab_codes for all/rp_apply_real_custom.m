function G = rp_apply_real_custom(X,proj)
V = proj.W*X;

% Add offset b
% Suboptimal!!! Do preprocessing instead...
for i = 1:size(X,2)
    V(:,i) = V(:,i) + proj.b;
end

G = cos(V);
% G = X;
end
