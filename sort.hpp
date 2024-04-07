#ifndef SORT_HPP
#define SORT_HPP

#include <ctime>
#include <vector>

/* out_* -> can be NULL if unwanted */
/* It is up to function to count its swaps & comparisons number */
void insertion_sort(std::vector<int> array, int* out_nb_swap, int* out_nb_cmp);
void merge_sort(std::vector<int> array, int* out_nb_swap, int* out_nb_cmp);
void quick_sort(std::vector<int> array, int* out_nb_swap, int* out_nb_cmp);

#endif // SORT_HPP