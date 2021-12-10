/**
 * Tugas PSD Artikel
 * 10/12/2021
 * by Raden Dwitama Baliano
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

//
#define FILEPATH "data/MHSILKOM20.csv"

// Struct mahasiswa
struct mahasiswa_t {
	char nim[32];
	int no;
	char nama[256];
	char kelas;
	double ipk;
};


// Fungsi untuk mengambil data dari file .csv
void GET_data (struct mahasiswa_t *array) {
	FILE *fp =
		fopen(FILEPATH, "r");
	assert(fp && "Gagal membuka file !");


	fscanf(fp, "%*[^\n]\n");

	int i = 0;
	do {
		int row = fscanf(fp, "%[^,],%d,%[^,],%c,%lf\n", 
				array[i].nim, &array[i].no, array[i].nama, 
				&array[i].kelas, &array[i].ipk
				);

		if (row == 5) {
			i++;
		} else if (row != EOF) {
			assert(NULL && "Kesalahan saat membaca file");
		} else {
			fclose(fp);
			break;
		};
	} while (true);
};

// Prosedur untuk mencetak semua data
void PRINT_data (struct mahasiswa_t *array, int length) {
	printf("%13s%10s%50s%10s%20s\n", "NIM", "NO", "NAMA", "KELAS", "IPK");
	for (int i = 0; i < length; i++) {
		printf("%13s%10d%50s%10c%20.2lf\n",
			array[i].nim, array[i].no, array[i].nama,
			array[i].kelas, array[i].ipk);
	};
	printf("\n\nDone..\n\n");
	system("pause");
	system("cls");
};

// SORTING
/**
 * Metode sorting dibawah bervariasi mulai dari
 * yang termudah ke yang terkompleks
 * kunci untuk mensorting struct yaitu
 * comparasion dan swapping
 * 
 * Jika pada native array, value dari
 * array index ke-x yang di komparasi.
 * Maka pada array of struct, value dari properti 
 * object index ke-x yang di komparasi.
 * 
 * Jika pada native array, value dari
 * array index ke-x yang di swapping.
 * Maka pada array of struct, object index ke-x
 * yang di swapping 
 */

// 1. GCC qsort() (descending)
int sort_by_ipk (struct mahasiswa_t *mhs_a, struct mahasiswa_t *mhs_b) {
	if (mhs_a->ipk < mhs_b->ipk) return 1;
	if (mhs_a->ipk > mhs_b->ipk) return -1;
	return 0;
};

// 2. buble sort (ascending)
void bubble_sort_by_no (struct mahasiswa_t *array, int length) {
	struct mahasiswa_t tmp;
	for (int i = 0; i < length - 1; i++) {
		for (int j = 0; j < length - 1 - i; j++) {
			if (array[j].no > array[j + 1].no) {
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			};
		};
	};
};

// 3. insertion sort (descending)
void insertion_sort_by_kelas (struct mahasiswa_t *array, int length) {
	struct mahasiswa_t key_value;
	int i, j;
	i = 1;
	while (i < length) {
		key_value = array[i];
		j = i - 1;
		while (j >= 0 && array[j].kelas > key_value.kelas) {
			array[j + 1] = array[j];
			j--;
		};
		array[j + 1] = key_value;
		i++;
	};
};

// 4. quick_sort (ascending)
int partition (struct mahasiswa_t *array, int length, int lo, int hi) {
	struct mahasiswa_t tmp;
	int middle = (lo + hi)/2;
	struct mahasiswa_t pivot = array[middle];
	int i = lo;
	int j = hi;

	while (i <= j) {
		while (array[i].nama[0] < pivot.nama[0])
			i++;
		while (array[j].nama[0] > pivot.nama[0])
			j--;

		if (i <= j) {
			tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;
			i++;
			j--;
		};
	};
	return i;
};
void quick_sort_by_inisial (struct mahasiswa_t *array, int length, int lo, int hi) {
	int p = partition(array, length, lo, hi);
	if (lo < p - 1)
		quick_sort_by_inisial(array, length, lo, p - 1);
	if (p < hi)
		quick_sort_by_inisial(array, length, p, hi);
};


// MAIN FUNCTION
int main (void) {
	// ARRAY untuk diurutkan
	struct mahasiswa_t if_20[110];
	GET_data(if_20);

	printf("\n============== TERURUT BERDASARKAN IPK  ===============\n");
	qsort(&if_20, 110, sizeof(struct mahasiswa_t), (int (*) (const void *, const void *)) &sort_by_ipk);
	PRINT_data(if_20, 110);

	printf("\n============== TERURUT BERDASARKAN NO ABSEN / NIM  ==============\n");
	bubble_sort_by_no(if_20, 110);
	PRINT_data(if_20, 110);
	
	printf("\n============== TERURUT BERDASARKAN KELAS ==============\n");
	insertion_sort_by_kelas(if_20, 110);
	PRINT_data(if_20, 110);

	printf("\n============== TERURUT BERDASARKAN INISIAL ==============\n");
	quick_sort_by_inisial(if_20, 110, 0, 110 - 1);
	PRINT_data(if_20, 110);







	return 0;
};


