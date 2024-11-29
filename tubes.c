#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

typedef struct {
    char warna[10];
    int angka;
} KartuUNO;

// Fungsi untuk membandingkan dua kartu
int bandingkan(KartuUNO a, KartuUNO b) {
    int cmp = strcmp(a.warna, b.warna);
    if (cmp == 0)
        return a.angka - b.angka;
    return cmp;
}

// ----------------- Insertion Sort -----------------
void insertionSort(KartuUNO arr[], int n) {
    for (int i = 1; i < n; i++) {
        KartuUNO key = arr[i];
        int j = i - 1;

        while (j >= 0 && bandingkan(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// ----------------- Merge Sort -----------------
void merge(KartuUNO arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    KartuUNO kiri[n1], kanan[n2];

    for (int i = 0; i < n1; i++)
        kiri[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        kanan[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (bandingkan(kiri[i], kanan[j]) <= 0) {
            arr[k] = kiri[i];
            i++;
        } else {
            arr[k] = kanan[j];
            j++;
        }
        k++;
    }

    while (i < n1) arr[k++] = kiri[i++];
    while (j < n2) arr[k++] = kanan[j++];
}

void mergeSort(KartuUNO arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// ----------------- Fungsi Utilitas -----------------
void copyArray(KartuUNO src[], KartuUNO dest[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

void printKartu(KartuUNO arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("(%s, %d) ", arr[i].warna, arr[i].angka);
    }
    printf("\n");
}

void generateRandomKartu(KartuUNO arr[], int n) {
    const char* warna[] = {"merah", "hijau", "biru", "kuning"};
    int warnaCount = sizeof(warna) / sizeof(warna[0]);

    for (int i = 0; i < n; i++) {
        strcpy(arr[i].warna, warna[rand() % warnaCount]);
        arr[i].angka = rand() % 10;
    }
}

// ----------------- Main Program -----------------
int main() {
    srand(time(NULL));

    int jumlahKartu;
    printf("Masukkan jumlah kartu: ");
    scanf("%d", &jumlahKartu);

    KartuUNO kartu[jumlahKartu];
    generateRandomKartu(kartu, jumlahKartu);

    // Tampilkan kartu sebelum diurutkan
    printf("\nKartu sebelum diurutkan:\n");
    printKartu(kartu, jumlahKartu);
    printf("\n");

    // Buat salinan array agar kedua algoritma bekerja pada data yang sama
    KartuUNO kartu1[jumlahKartu], kartu2[jumlahKartu];
    copyArray(kartu, kartu1, jumlahKartu);
    copyArray(kartu, kartu2, jumlahKartu);

    // Pengukuran waktu untuk Insertion Sort
    clock_t start = clock();
    insertionSort(kartu1, jumlahKartu);
    clock_t end = clock();
    double waktuInsertion = (double)(end - start) / CLOCKS_PER_SEC;

    // Pengukuran waktu untuk Merge Sort
    start = clock();
    mergeSort(kartu2, 0, jumlahKartu - 1);
    end = clock();
    double waktuMerge = (double)(end - start) / CLOCKS_PER_SEC;

    // Tampilkan hasil dan waktu eksekusi
    printf("Setelah Insertion Sort:\n");
    printKartu(kartu1, jumlahKartu);
    printf("Waktu Insertion Sort: %f detik\n\n", waktuInsertion);

    printf("Setelah Merge Sort:\n");
    printKartu(kartu2, jumlahKartu);
    printf("Waktu Merge Sort: %f detik\n", waktuMerge);

    return 0;
}
