function [ mat, vec ] = mKrylowa(A, y_vec)
    [r, c] = size(A);
    % Allocate A_tmp
    A_tmp = zeros(r, c+1);
    A_tmp(:, 1) = y_vec;
    y_prev = y_vec;
    for it=1:c
        y_prev = A*y_prev;
        A_tmp(:, it+1) = y_prev;
    end
    vec = -(A_tmp(:, end));
    mat = A_tmp(:, 1:end-1);
    mat = mat(:, end:-1:1);
end