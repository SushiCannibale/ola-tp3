#include "sort.hpp"
#include <vector>

/* ---------------------------------------------- */
/*                 Insertion Sort                 */
/* ---------------------------------------------- */

void insertion_sort(std::vector<int>& array, unsigned long* out_nb_swap, unsigned long* out_nb_cmp) {
	int actuel;
	int taille = array.size();
	for (int i = 1; i < taille; i++) {
		(*out_nb_cmp)++;
		int j = i - 1;
		actuel = array[i];
		while (j >= 0 && actuel < array[j]) {
			(*out_nb_cmp)+=2;
			(*out_nb_swap)++;
			array[j + 1] = array[j];
			j--;
		}
		(*out_nb_cmp)++;// dernière comparaison de la boucle while
		array[j + 1] = actuel;
		(*out_nb_swap)++;
	}
	(*out_nb_cmp)++;// dernière comparaison de la boucle for
}

/* ---------------------------------------------- */
/*                   Merge Sort                   */
/* ---------------------------------------------- */

void merge(std::vector<int>& array, std::vector<int>& temp, int left, int mid, int right, unsigned long* out_nb_swap, unsigned long* out_nb_cmp) {
    int i = left, j = mid + 1, k = left;
    for (int index = left; index <= right; index++) {
        temp[index] = array[index];
		(*out_nb_cmp)++;(*out_nb_swap)++;
    }
	(*out_nb_cmp)++;// dernière comparaison du for

    while (i <= mid && j <= right) {
        if (temp[i] < temp[j]) {
            array[k++] = temp[i++];
        } else {
            array[k++] = temp[j++];
        }
		(*out_nb_cmp)+=3;
		(*out_nb_swap)++;
    }
	(*out_nb_cmp)++;// dernière comparaison du while

    while (i <= mid) {
        array[k++] = temp[i++];
		(*out_nb_cmp)++;
		(*out_nb_swap)++;
    }
	(*out_nb_cmp)++;
	// while (j <= right) {
    //     array[k++] = temp[i++];
	// 	(*out_nb_cmp)++;
	// 	(*out_nb_swap)++;
    // }
}

void merge_sort_rec(std::vector<int>& array, std::vector<int>& temp, int left, int right, unsigned long* out_nb_swap, unsigned long* out_nb_cmp){
	if (left >= right) 
		return;
	int mid = (left + right) / 2;
	(*out_nb_cmp)++;
	merge_sort_rec(array, temp, left, mid, out_nb_swap, out_nb_cmp);
	merge_sort_rec(array, temp, mid + 1, right, out_nb_swap, out_nb_cmp);
	merge(array, temp, left, mid, right, out_nb_swap, out_nb_cmp);
}

void merge_sort(std::vector<int>& array, unsigned long* out_nb_swap, unsigned long* out_nb_cmp) {
	std::vector<int> temp(array.size());
	merge_sort_rec(array, temp, 0, array.size()-1, out_nb_swap, out_nb_cmp);
}


/* ---------------------------------------------- */
/*                   Quick Sort                   */
/* ---------------------------------------------- */


int partitionner(std::vector<int>& vecteur, int debut, int fin,unsigned long* out_nb_swap, unsigned long* out_nb_cmp) {
    int i = debut - 1;
    for (int j = debut; j < fin; j++) {
		(*out_nb_cmp)++;
        if (vecteur[j] <= vecteur[fin]) {
            i++;
            std::swap(vecteur[i], vecteur[j]);
			(*out_nb_swap)++;
        }
		(*out_nb_cmp)++;
    }
	(*out_nb_cmp)++;// fin de la boucle for
	(*out_nb_swap)++;
    std::swap(vecteur[i + 1], vecteur[fin]);
    return i + 1;
}

void quick_sort_rec(std::vector<int>& vecteur, int debut, int fin, unsigned long* out_nb_swap, unsigned long* out_nb_cmp){
	(*out_nb_cmp)++;
	if (debut < fin) {
		int pivot = partitionner(vecteur, debut, fin, out_nb_swap, out_nb_cmp);
		quick_sort_rec(vecteur, debut, pivot - 1, out_nb_swap, out_nb_cmp);
		quick_sort_rec(vecteur, pivot + 1, fin, out_nb_swap, out_nb_cmp);
	}
}

void quick_sort(std::vector<int>& array, unsigned long* out_nb_swap, unsigned long* out_nb_cmp) {
	quick_sort_rec(array, 0, array.size()-1, out_nb_swap, out_nb_cmp);
}

/* ---------------------------------------------- */
