% A = [
%      a11 a12 a13 b1
%      a21 a22 a23 b2
%      a31 a32 a33 b3
%     ];
function [ x ] = gauss(A)
    n = length(A)-1;
    x = zeros(n, 1);
    for k=1:n-1
        max = A(k,k);
        nr_wiersz = k;
        for j=k:n
            if(A(j,k) > max)
                max = A(j, k);
                nr_wiersz = j;
            end
        end
        nr_teraz = k;
        if(nr_wiersz ~= nr_teraz)
            tmp = A(nr_wiersz, :);
            A(nr_wiersz, :) = A(nr_teraz, :);
            A(nr_teraz, :) = tmp;
        end
        for i=k+1:n
            for j=k+1:n+1
                A(i, j) = A(i, j) - (A(i,k)*A(k,j))/A(k,k);
            end
        end
        for g=k:n-1
            A(g+1,k)=0;
        end
    end
    x(n) = A(n ,n+1)/A(n,n);
    i=n-1;
    while(i~=0)
        sum=0;
        for j=i+1:n
            sum = sum + A(i,j)*x(j);
        end
        sum = A(i, n+1) - sum;
        x(i) = 1/A(i,i) * sum;
        i=i-1;
    end

end

