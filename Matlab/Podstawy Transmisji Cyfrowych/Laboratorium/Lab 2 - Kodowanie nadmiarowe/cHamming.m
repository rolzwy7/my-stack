function [ G, H, R_ret, k] = cHamming( R )
%R = 3;         % 3 dla Hamminga(7, 4)
n = 2^R - 1;   % d³ugoœæ bloku
k = n - R;     % s³owo informacyjne (data bits)
m = n - k;     % bity parzystosci (parity bits)
fprintf('Hamming(%d, %d)\n', n, k);

%%% Generator matrix (G) - start %%%
G = zeros(k,k+m);
I = eye(k);
G(:, 1:k) = I;
c = 1;
for it=1:n
    flag = 0;
    for i=0:m
        if(2^i == it)
            flag = 1;
        end
    end
    if flag == 1
       continue;
    end
    G(c, k+1:k+m) = de2bi(it, m);
    c = c + 1;
end
A = abs(-G(:, k+1:k+m)');

%%% G - przenies kolumny na wlasciwe pozycje
G_cp = G;
R_ret = G;
pc = 0;
dc = 1;
[~, c] = size(G);
R_c = 0;
for i=1:c
    flag = 0;
    for j=0:m
        if 2^j == i
            flag = 1;
        end
    end
    if flag == 1
        G_cp(:, i) = G(:, (c+1)-m+pc);
        R_ret(:, i) = zeros(k, 1);
        pc = pc + 1;
    else
        G_cp(:, i) = G(:, dc);
        R_ret(:, i) = de2bi(2^R_c, k)';
        dc = dc + 1;
        R_c = R_c + 1;
    end
end
G = G_cp;
G = G';
[R,c] = size(A);

%%% Generator matrix (G) - stop %%%

%%% Parity check matrix (H) - start %%%
H = zeros(n-k, n);
H(1:R,1:c) = A;
H(1:R,c+1:n) = eye(m);
%%% H - przenies kolumny na wlasciwe pozycje
H_cp = H;
pc = 0;
dc = 1;
[~, c] = size(H);
for i=1:c
    flag = 0;
    for j=0:m
        if 2^j == i
            flag = 1;
        end
    end
    if flag == 1
        H_cp(:, i) = H(:, (c+1)-m+pc);
        pc = pc + 1;
    else
        H_cp(:, i) = H(:, dc);
        dc = dc + 1;
    end
end
H = H_cp;
%%% Parity check matrix (H) - stop %%%
end

