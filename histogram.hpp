#ifndef HISTOGRAM_HPP
#define HISTOGRAM_HPP

#include <vector>
#include <iostream>
#include <cmath>

#define CHAR "\u25a0"

/* Beware, max_bar_len should be x2 as character width is ~1/2 its height */
void display_histogram(std::vector<int> array, int max_val, int n_bars, int max_n_bars, int max_bar_len);

#endif // HISTOGRAM_HPP