#ifndef SORT_HPP
#define SORT_HPP

#include <ctime>
#include <vector>

/* It is up to function to count its swaps & comparisons number */
void insertion_sort(std::vector<int>& array, unsigned long* out_nb_swap, unsigned long* out_nb_cmp);
void merge_sort(std::vector<int>& array, unsigned long* out_nb_swap, unsigned long* out_nb_cmp);
void quick_sort(std::vector<int>& array, unsigned long* out_nb_swap, unsigned long* out_nb_cmp);

#endif // SORT_HPP
