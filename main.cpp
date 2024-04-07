#include <random>
#include <iostream>

#include "sort.hpp"

template <class T>
void show_array(int nb_vals, int nb_funcs, std::string func_names[], T* data) {
    /* Front padding (8-spaces format of nb_vals) */
    std::cout << "        | ";
    for (int i = 0; i < nb_funcs-1; i++) {
        std::cout << func_names[i] << " | ";
    }

    std::cout << func_names[nb_funcs-1] << std::endl;
    fprintf(stdout, "%8d", nb_vals);

    /* Prints function names */
    for (int i = 0; i < nb_funcs-1; i++) {
        for (int j = 0; j < func_names[i].length(); j++) {
            std::cout << " ";
        }
        std::cout << " | ";
    }
    for (int j = 0; j < func_names[nb_funcs-1].length(); j++) {
        std::cout << " ";
    }

    /* Print stats */
    for (int i = 0; i < nb_funcs; i++) {
        for (int j = 0; j < func_names[i].length()/2; j++) {
            std::cout << " ";
        }
        std::cout << data[i];
        for (int j = 0; j < func_names[i].length()/2; j++) {
            std::cout << " ";
        }
    }
}

int main(int argc, char** argv) {
    /* Functions to compare */
    int nb_funcs = 3;
    void (*funcs[nb_funcs])(std::vector<int>, int*, int*) = { insertion_sort, merge_sort, quick_sort };
    std::string func_names[nb_funcs] = { "Insertion Sort", "Merge Sort", "Quick Sort" };

    /* Stats */
    time_t start, end;
    double timediffs[nb_funcs];
    int nb_swaps[nb_funcs];
    int nb_cmps[nb_funcs];

    //          fn1       fn2        fn3       ...
    //   500     X         X          X
    //   ...

    int user_nb_vals; // TODO: fills the user input 'user_nb_vals'

    for (int i = 0; i < nb_funcs; i++) {
        std::vector<int> array;
        
        /* Fills the array */
        for (int k = 0; k < user_nb_vals; k++) {
            array.push_back(rand());
        }

        /* Runs the function & store the stats */
        time(&start);
        funcs[i](array, &nb_swaps[i], &nb_cmps[i]);
        time(&end);

        timediffs[i] = difftime(end, start);
    }

    /* Display the arrays */
    std::cout << "Timestamps" << std::endl;
    show_array<double>(user_nb_vals, nb_funcs, func_names, timediffs);
    std::cout << "Number of swaps" << std::endl;
    show_array<int>(user_nb_vals, nb_funcs, func_names, nb_swaps);
    std::cout << "Number of comparisons" << std::endl;
    show_array<int>(user_nb_vals, nb_funcs, func_names, nb_cmps);
}