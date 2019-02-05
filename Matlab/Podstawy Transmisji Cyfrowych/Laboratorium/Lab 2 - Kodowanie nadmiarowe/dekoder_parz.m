function [y, success] = dekoder_parz(vec, n, success_cp)
    vec = reshape(vec', n, numel(vec)/n)';
    [r,c] = size(vec);
    success = zeros(r,c+1); % stworz
    success(1:r, 1:n) = vec(1:r, 1:c); % wsadz vec
    a = mod(sum(success(1:r, 1:n-1), 2), 2);
    b = success(1:r, c);
    success(1:r, c+1) = or(success(1:r, c+1),(a == b)); % ostatnia kolumna
    
    success = or(success(1:r, c+1), success_cp);
    
    y = vec;
end

