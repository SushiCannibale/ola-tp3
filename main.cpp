#include <random>
#include <iostream>

#include "sort.hpp"

int main(int argc, char** argv) {
    /* Sizes of arrays to sort */
    int nb_samp = 3;
    int samples[] = { 500, 5000, 50000 };

    /* Functions to compare ! */
    int nb_funcs = 3;
    void (*funcs[])(std::vector<int>, int*, int*) = { insertion_sort, merge_sort, quick_sort };

    time_t start, end;
    double timediffs[nb_samp * nb_funcs];
    int nb_swaps[nb_samp * nb_funcs];
    int nb_cmps[nb_samp * nb_funcs];

    /* For each stats, (timediff, nb_swaps, nb_comps) : */
    //          fn1       fn2        fn3       ...
    //   500     X         X          X
    //  5000     X         X          X
    // 50000     X         X          X
    //   ...

    for (int j = 0; j < nb_samp; j++) {
        for (int i = 0; i < nb_funcs; i++) {
            std::vector<int> array;
            
            /* Fills the array */
            for (int k = 0; k < samples[j]; k++) {
                array.push_back(rand());
            }

            /* Runs the function & store the stats */
            time(&start);
            funcs[i](array, &nb_swaps[j*nb_funcs + i], &nb_cmps[j*nb_funcs + i]);
            time(&end);

            timediffs[j*nb_funcs + i] = difftime(end, start);
        }
    }

    /* Display the arrays */
    for (int i = 0; )
}