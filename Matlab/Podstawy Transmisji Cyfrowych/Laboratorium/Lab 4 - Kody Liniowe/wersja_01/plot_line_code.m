function [] = plot_line_code( line_code_data, t, c_title, color)
    plot(t, line_code_data, color);
    axis([
        0 t(end) min(line_code_data)-.5 max(line_code_data)+.5
        ]);
    title(c_title);
    xlabel('Time');
    ylabel('Amplitude');
    grid;
end

