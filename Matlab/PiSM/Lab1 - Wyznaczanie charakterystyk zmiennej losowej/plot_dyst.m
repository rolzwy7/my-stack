% xi
function [ ret_xi, ret_pi ] = plot_dyst( x_i, p_i )
    step = 0.01;
    xi_0 = x_i(1);
    xi_N = x_i(end);
    
    wdth = abs(xi_N-xi_0) * 0.1;
    loc_range = xi_0-wdth:step:xi_N+wdth;
    
    ret_xi = loc_range;
    ret_pi = zeros(1, length(ret_xi));
    
    prev_val = 0;
    xi_it = 1;
    
    x_i = [x_i, max(loc_range)+1];
    p_i = [p_i, 0];
    
    for i=1:length(loc_range)
        if loc_range(i) >= x_i(xi_it)
            ret_pi(i) = prev_val;
            prev_val = prev_val + p_i(xi_it);
            xi_it = xi_it + 1;
        else
            ret_pi(i) = prev_val;
        end
    end
    
end

