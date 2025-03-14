#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct deadline
{
    int tgl;
    int bln;
    int thn;
};

struct data
{
    char namaTugas[100];  // Menggunakan array char untuk namaTugas
    char kategori[50];    // Menggunakan array char untuk kategori
    struct deadline tenggat;
    char status[20];      // Menggunakan array char untuk status
};

int tambah();
int tampil();
int cari();
int tampilLewatDeadline();
int perbaruiStatus();
int hapusTugas();

int main()
{
    int pil;
    bool errorMenu = false;
    char kembali;
    do
    {
        system("cls");
        errorMenu = false;
        printf("-----------------Work Tracker-----------------");
        printf("\n");
        printf("1. Menambahkan Tugas Baru");
        printf("\n");
        printf("2. Menampilkan Daftar Tugas");
        printf("\n");
        printf("3. Mencari Tugas berdasarkan Kategori");
        printf("\n");
        printf("4. Menampilkan Tugas yang Melewati Deadline");
        printf("\n");
        printf("5. Memperbarui Status Tugas");
        printf("\n");
        printf("6. Menghapus Tugas yang Sudah Selesai");
        printf("\n");
        printf("7. Keluar");
        printf("\n");
        printf("----------------------------------------------");
        printf("\n");
        printf("Pilih : ");
        scanf("%d", &pil);
        switch (pil)
        {
        case 1:
            tambah();
            printf("Kembali ke menu [y/n] : ");
            cin >> kembali;
            break;
        case 2:
            tampil();
            printf("Kembali ke menu [y/n] : ");
            cin >> kembali;
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        default:
            printf("\n");
            printf("Pilihan tidak ada.");
            printf("\n");
            printf("Pilih angka 1-7.");
            system("pause");
            errorMenu = true;
            break;
        }
    } while (errorMenu == true || kembali == 'y');
}

int tambah()
{
    FILE *file = fopen("C:\\Temp\\WorkTracker.dat", "ab");
    if (file == NULL)
    {
        printf("Anda Gagal membuka file!!!\n");
        return 1;
    }
    else
    {
        printf("Masukkan Nama Tugas                : ");
        cin.ignore();
        cin.getline(tugas.namaTugas, sizeof(tugas.namaTugas));  // Menggunakan cin.getline untuk array char
        printf("Masukan Kategori tugas             : ");
        cin.getline(tugas.kategori, sizeof(tugas.kategori));  // Menggunakan cin.getline untuk array char
        printf("Masukkan Tgl Deadline (DD MM YYYY) : ");
        cin >> tenggat.tgl >> tenggat.bln >> tenggat.thn;
        cin.ignore();
        printf("Masukkan status tugas              : ");
        cin.getline(tugas.status, sizeof(tugas.status));  // Menggunakan cin.getline untuk array char
        if (fwrite(&tugas, sizeof(struct data), 1, file) != 1)
        {
            printf("Gagal menulis data ke file.\n");
            fclose(file);
            return 1;
        }
        printf("Tugas berhasil ditambahkan.\n");
        fclose(file);
    }
    return 0;
}

int tampil()
{
    FILE *file = fopen("C:\\Temp\\WorkTracker.dat", "rb");
    if (file == NULL)
    {
        printf("Anda gagal membuka file!!!");
        return 1;
    }
    else
    {
        while (fread(&tugas, sizeof(struct data), 1, file) == 1)
        {
            printf("Tugas      : %s\n", tugas.namaTugas);
            printf("Kategori   : %s\n", tugas.kategori);
            printf("Deadline   : %02d-%02d-%04d\n", tugas.tenggat.tgl, tugas.tenggat.bln, tugas.tenggat.thn);  // Format tanggal
            printf("Status     : %s\n", tugas.status);
        }
        fclose(file);
    }
    return 0;
}

int cari()
{
    return 0;
}

int tampilLewatDeadline()
{
    return 0;
}

int
