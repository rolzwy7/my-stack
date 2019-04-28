% Dwuwymiarowa zmienna losowa
close all; clear; clc;

kor_col = [2, 3, 3.5, 4, 5];
kor_row = [2, 3, 3.5, 4, 5];
kor = [%2     3      3.5    4      5 
        3/35  2/35   1/35   0      0    ; % 2
        1/35  10/35  2/35   1/35   0    ; % 3
        0     1/35   5/35   1/35   1/35 ; % 3.5
        0     0      0      3/35   2/35 ; % 4
        0     0      0      1/35   1/35 ; % 5
];
kor_size = size(kor);
ost_w = kor_size(1) + 1;
ost_k = kor_size(2) + 1;

kor(ost_w, :) = sum(kor, 1);
kor(:, ost_k) = sum(kor, 2);

%%%% P(Y | X=4) =  P(X=4, Y) / P(X=4)
P_X_eq_4 = kor(ost_w, 4);
P_X_eq_4_Y = 0;
for it=1:ost_w-1
    fprintf('P(Y=%.2f | X=4) = %.4f\n', kor_col(it), kor(it, 4)/P_X_eq_4);
end

%%%% E(X)
E_X = sum(kor(ost_w, 1:ost_k-1) .* kor_col, 2);
fprintf('E(X) = %.4f\n', E_X);

%%%% E(X|Y=4)
%E(X|Y=4) =  E(X,Y=4) / E(Y=4) ????
E_X_Y_eq_4 = (kor(4, end-1) .* kor_col) ./ (kor(4,end-1)*kor_row(4));
E_X_Y_eq_4 = sum(E_X_Y_eq_4, 2);
fprintf('E(X|Y=4) = %.4f\n', E_X_Y_eq_4);

%%%% D(X|Y=4)
% E(X^2)
E_X2 = sum(kor(ost_w, 1:ost_k-1) .* (kor_col .* kor_col), 2);
D_XY_eq_4 = E_X2 - E_X*E_X;

fprintf('D(X|Y=4) = %.4f\n', D_XY_eq_4);


