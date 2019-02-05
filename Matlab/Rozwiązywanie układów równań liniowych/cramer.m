% M = [
%      a11 a12 a13 b1
%      a21 a22 a23 b2
%      a31 a32 a33 b3
%     ];
function [ y ] = cramer(M)
    A = M(:, 1:end-1);
    Adet = det(A);
    B = M(:, end);
    n = length(A);
    y = zeros(1, n);
    for it=1:n
        temp = A;
        temp(:, it) = B;
        y(it) = det(temp)/Adet;
    end
    y = y';
end

