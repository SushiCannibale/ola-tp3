#include <random>
#include <iostream>
#include <cmath>
#include <string>

#include "sort.hpp"
#include "histogram.hpp"

// void show_elts(const std::vector<int> array) {
//     std::cout << "[ " << array[0];
//     for (int i = 1; i < array.size(); i++) {
//         std::cout << ", " << array[i];
//     }
//     std::cout << " ]" << std::endl;
// }

int randi(int a, int b) {
    return rand() % (b - a) + a;
}

void show_array(int nb_vals, int nb_funcs, std::string func_names[], double* data, FILE* fp) {
    int padding = log10(nb_vals)+1;
    /* Front padding (8-spaces format of nb_vals) */
    fprintf(fp, "%*s", padding+3, " | ");
    /* Prints function names */
    for (int i = 0; i < nb_funcs; i++) {
        fprintf(fp, "%s | ", func_names[i].c_str());
    }

    fprintf(fp, "\n");
    fprintf(fp, "%-*d", padding, nb_vals);
    fprintf(fp, " | ");

    /* Print stats */
    for (int i = 0; i < nb_funcs; i++) {
        fprintf(fp, "%*f", (int)func_names[i].length(), data[i]);
        fprintf(fp, " | ");
    }

    fprintf(fp, "\n");
}

void show_array(int nb_vals, int nb_funcs, std::string func_names[], unsigned long* data, FILE* fp) {
    int padding = log10(nb_vals)+1;
    /* Front padding (8-spaces format of nb_vals) */
    fprintf(fp, "%*s", padding+3, " | ");
    /* Prints function names */
    for (int i = 0; i < nb_funcs; i++) {
        fprintf(fp, "%s | ", func_names[i].c_str());
    }

    fprintf(fp, "\n");
    fprintf(fp, "%-*d", padding, nb_vals);
    fprintf(fp, " | ");

    /* Print stats */
    for (int i = 0; i < nb_funcs; i++) {
        fprintf(fp, "%*ld", (int)func_names[i].length(), data[i]);
        fprintf(fp, " | ");
    }

    fprintf(fp, "\n");
}

void sperator(){
	std::cout<<"-----------------------------------------------------------\n";
}
void space(){
	std::cout<<"|                                                         |\n";
}


void callUI(){

	int nb_funcs = 3;
    void (*funcs[nb_funcs])(std::vector<int>&, unsigned long*, unsigned long*) = { insertion_sort, merge_sort, quick_sort };
    std::string func_names[nb_funcs] = { "Insertion Sort", "Merge Sort", "Quick Sort" };

    /* Stats */
    double timediffs[nb_funcs] = { 0.0 };
    unsigned long nb_swaps[nb_funcs] = { 0 };
    unsigned long nb_cmps[nb_funcs] = { 0 };

    /* Save */
    FILE* fp = fopen("Sortie.txt", "w");

    //          fn1       fn2        fn3       ...
    //   500     X         X          X
    //   ...

    int user_nb_vals;
    int max_n_bars;
    // affichage de l'ui:
	do{
        max_n_bars=20;
	sperator();		
	std::cout<<"| Voici comment utiliser le programme ;                   |\n";
	space();
	std::cout<<"| => vous pouvez lancer un appel sur tous les tri         |\n| en rentrant une valeur numérique                        |\n";
	space();
	std::cout<<"| => vous pouvez quitter le programme en envoyant         |\n| 0 ou une chaine ne contenant pas de valeur numérique    |\n";
	space();
	std::cout<<"| =>(vous pouvez quitter de façon non conventionnel       |\n|  à l'aide de Ctrl-C)                                    |\n";
	sperator();
    std::cout << "Merci de rentrer la valeur voulu : ";
	std::cin  >> user_nb_vals;
	if(user_nb_vals<=0)
		break;
    if(max_n_bars>user_nb_vals)
        max_n_bars=user_nb_vals;
	for (int i = 0; i < nb_funcs; i++) {
        /* Stats */
        timediffs[i] = 0.0;
        nb_swaps[i] = 0;
        nb_cmps[i] = 0;
        double start, end;

        std::vector<int> array = std::vector<int>();
        
        /* Fills the array */
        for (int k = 0; k < user_nb_vals; k++) {
            array.push_back(randi(0, 101));
        }

        fprintf(stdout, "Unsorted: \x1b[0;31m[ %s ]\x1b[0m\n", func_names[i].c_str());
        display_histogram(array, 100, max_n_bars, max_n_bars*2, stdout);
        display_histogram(array, 100, max_n_bars, max_n_bars*2, fp);
        fprintf(stdout, "\n");

        /* Runs the function & store the stats */
        start = clock();
        funcs[i](array, &nb_swaps[i], &nb_cmps[i]);
        end = clock();

        timediffs[i] = (end - start) / CLOCKS_PER_SEC;

        fprintf(stdout, "Sorted:   \x1b[0;32m[ %s ]\x1b[0m\n", func_names[i].c_str());
        display_histogram(array, 100, max_n_bars, max_n_bars*2, stdout);
        display_histogram(array, 100, max_n_bars, max_n_bars*2, fp);
        fprintf(stdout, "\n");
    }

    fprintf(stdout, "\n");
    fprintf(fp, "\n");

    /* Display the arrays */
    fprintf(stdout, "Timestamps :\n");
    show_array(user_nb_vals, nb_funcs, func_names, timediffs, stdout);
    fprintf(stdout, "\n");
    fprintf(fp, "Timestamps :\n");
    show_array(user_nb_vals, nb_funcs, func_names, timediffs, fp);
    fprintf(fp, "\n");

    fprintf(stdout, "Number of swaps :\n");
    show_array(user_nb_vals, nb_funcs, func_names, nb_swaps, stdout);
    fprintf(stdout, "\n");
    fprintf(fp, "Number of swaps :\n");
    show_array(user_nb_vals, nb_funcs, func_names, nb_swaps, fp);
    fprintf(fp, "\n");

    fprintf(stdout, "Number of comparisons :\n");
    show_array(user_nb_vals, nb_funcs, func_names, nb_cmps, stdout);
    fprintf(stdout, "\n");
    fprintf(fp, "Number of comparisons :\n");
    show_array(user_nb_vals, nb_funcs, func_names, nb_cmps, fp);
    fprintf(fp, "\n");

	sperator();
	}while(user_nb_vals>=1);

	fclose(fp);
}

int main(int argc, char** argv) {
    /* Functions to compare */
	callUI();



    return 0;
}
