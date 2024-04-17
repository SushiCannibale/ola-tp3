#include "histogram.hpp"

int map(float n, float n_max, int max) {
    return (int)((n / n_max) * max);
}

void display_histogram(std::vector<int> array, int max_val, int max_n_bars, int max_bar_len, FILE* fp) {
    int n_bars = array.size();
    int margin_left = log10(n_bars) + 1;
    
    /* 1st row */
    fprintf(fp, "%*d | ", margin_left, 0);
    for (int i = 0; i < map(array[0], max_val, max_bar_len); i++) {
        fprintf(fp, CHAR);
    }
    fprintf(fp, "\n");

    /* Print bars */
    int bar_step = n_bars / max_n_bars;
    for (int i = 1; i < n_bars-1; i += bar_step) {
        fprintf(fp, "%*s | ", margin_left, "");
        for (int j = 0; j < map(array[i], max_val, max_bar_len); j++) {
            fprintf(fp, CHAR);
        }
        fprintf(fp, "\n");
    }

    /* last row */
    fprintf(fp, "%*d | ", margin_left, n_bars);
    for (int i = 0; i < map(array[n_bars-1], max_val, max_bar_len); i++) {
        fprintf(fp, CHAR);
    }
    fprintf(fp, "\n");

    /* bottom line */
    fprintf(fp, "%*s", margin_left+2, " ");
    for (int i = 0; i < max_bar_len+2; i++) {
        fprintf(fp, "-");
    }
    fprintf(fp, "\n");

    fprintf(fp, "%*d", margin_left+3, 0);
    fprintf(fp, "%*d", max_bar_len+2 - (int)log10(max_val), max_val);

    fprintf(fp, "\n");
}
