#include <random>
#include <iostream>
#include <cmath>

#include "sort.hpp"

void show_elts(const std::vector<int> array) {
    std::cout << "[ " << array[0];
    for (int i = 1; i < array.size(); i++) {
        std::cout << ", " << array[i];
    }
    std::cout << " ]" << std::endl;
}

int randi(int a, int b) {
    return rand() % (b - a) + a;
}

void show_array(int nb_vals, int nb_funcs, std::string func_names[], double* data) {
    int padding = log10(nb_vals)+1;
    /* Front padding (8-spaces format of nb_vals) */
    fprintf(stdout, "%*s", padding+3, " | ");
    /* Prints function names */
    for (int i = 0; i < nb_funcs; i++) {
        std::cout << func_names[i] << " | ";
    }

    std::cout << std::endl;
    fprintf(stdout, "%-*d", padding, nb_vals);
    std::cout << " | ";

    /* Print stats */
    for (int i = 0; i < nb_funcs; i++) {
        fprintf(stdout, "%*f", (int)func_names[i].length(), data[i]);
        std::cout << " | ";
    }

    std::cout << std::endl;
}

void show_array(int nb_vals, int nb_funcs, std::string func_names[], unsigned long* data) {
    int padding = log10(nb_vals)+1;
    /* Front padding (8-spaces format of nb_vals) */
    fprintf(stdout, "%*s", padding+3, " | ");
    /* Prints function names */
    for (int i = 0; i < nb_funcs; i++) {
        std::cout << func_names[i] << " | ";
    }

    std::cout << std::endl;
    fprintf(stdout, "%-*d", padding, nb_vals);
    std::cout << " | ";

    /* Print stats */
    for (int i = 0; i < nb_funcs; i++) {
        fprintf(stdout, "%*ld", (int)func_names[i].length(), data[i]);
        std::cout << " | ";
    }

    std::cout << std::endl;
}

int main(int argc, char** argv) {
    /* Functions to compare */
    int nb_funcs = 3;
    void (*funcs[nb_funcs])(std::vector<int>&, unsigned long*, unsigned long*) = { insertion_sort, merge_sort, quick_sort };
    std::string func_names[nb_funcs] = { "Insertion Sort", "Merge Sort", "Quick Sort" };

    /* Stats */
    double timediffs[nb_funcs] = { 0.0 };
    unsigned long nb_swaps[nb_funcs] = { 0 };
    unsigned long nb_cmps[nb_funcs] = { 0 };

    //          fn1       fn2        fn3       ...
    //   500     X         X          X
    //   ...

    int user_nb_vals = 10000; // TODO: fills the user input 'user_nb_vals'

    for (int i = 0; i < nb_funcs; i++) {
        double start, end;

        std::vector<int> array = std::vector<int>();
        
        /* Fills the array */
        for (int k = 0; k < user_nb_vals; k++) {
            array.push_back(randi(0, 99));
        }

        // fprintf(stdout, "Unsorted: ");
        // show_elts(array);

        /* Runs the function & store the stats */
        start = clock();
        funcs[i](array, &nb_swaps[i], &nb_cmps[i]);
        end = clock();

        timediffs[i] = (end - start) / CLOCKS_PER_SEC;

        // fprintf(stdout, "Sorted:   ");
        // show_elts(array);
    }

    std::cout << std::endl;

    /* Display the arrays */
    std::cout << "Timestamps :" << std::endl;
    show_array(user_nb_vals, nb_funcs, func_names, timediffs);
    std::cout << std::endl;

    std::cout << "Number of swaps :" << std::endl;
    show_array(user_nb_vals, nb_funcs, func_names, nb_swaps);
    std::cout << std::endl;

    std::cout << "Number of comparisons :" << std::endl;
    show_array(user_nb_vals, nb_funcs, func_names, nb_cmps);
    std::cout << std::endl;

    return 0;
}