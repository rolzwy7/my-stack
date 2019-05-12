function [ y ] = wsp_korelacji( X, Y )
    X = X - mean(X);
    Y = Y - mean(Y);
    Z = X .* Y;
    Xs = sum(X .* X);
    Ys = sum(Y .* Y);
    y = sum(Z) / sqrt(Xs * Ys); 
end

