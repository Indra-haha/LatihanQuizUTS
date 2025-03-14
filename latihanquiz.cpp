#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>

using namespace std;

struct deadline
{
    int tgl;
    int bln;
    int thn;
};

struct data
{
    char nama[100];
    char kategori[100];
    struct deadline tenggat;
    char status[20];
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
            cari();
            printf("Kembali ke menu [y/n] : ");
            cin >> kembali;
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
    FILE *file = fopen("WorkTracker.dat", "ab");
    if (file == NULL)
    {
        printf("Anda Gagal membuka file!!!\n");
        return 1;
    }
    else
    {
        data tugas;
        char namaTugas[100];
        printf("Masukkan Nama Tugas                : ");
        cin.ignore();
        cin.getline(namaTugas, sizeof(namaTugas));
        strcpy(tugas.nama, namaTugas);
        printf("Masukan Kategori tugas             : ");
        cin.getline(tugas.kategori, sizeof(tugas.kategori));
        printf("Masukkan Tgl Deadline (DD/MM/YYYY) : ");
        cin >> tugas.tenggat.tgl >> tugas.tenggat.bln >> tugas.tenggat.thn;
        cin.ignore();
        strcpy(tugas.status, "Belum");
        fwrite(&tugas, sizeof(data), 1, file);
        printf("Tugas berhasil ditambahkan.\n");
        fclose(file);
        return 0;
    }
}

int tampil()
{

    FILE *file = fopen("WorkTracker.dat", "rb");
    if (file == NULL)
    {
        printf("Anda gagal membuka file!!!");
        return 1;
    }
    else
    {
        data tugas[200];
        int indeks = 0;
        while (fread(&tugas[indeks], sizeof(data), 1, file))
        {
            indeks++;
        }
        fclose(file);

        // urutin data descending
        for (int i = 0; i < indeks - 1; i++)
        {
            for (int j = i + 1; j < indeks; j++)
            {
                if (tugas[i].tenggat.thn > tugas[j].tenggat.thn ||
                    (tugas[i].tenggat.thn == tugas[j].tenggat.thn && tugas[i].tenggat.bln > tugas[j].tenggat.bln) ||
                    (tugas[i].tenggat.thn == tugas[j].tenggat.thn && tugas[i].tenggat.bln == tugas[j].tenggat.bln && tugas[i].tenggat.tgl > tugas[j].tenggat.tgl))
                {
                    data temp = tugas[i];
                    tugas[i] = tugas[j];
                    tugas[j] = temp;
                }
            }
        }

        // menampilkan data
        for (int k = 0; k < indeks; k++)
        {
            printf("Tugas : %s\n", tugas[k].nama);
            printf("Kategori : %s\n", tugas[k].kategori);
            printf("Deadline  : %d-%d-%d\n", tugas[k].tenggat.tgl, tugas[k].tenggat.bln, tugas[k].tenggat.thn);
            printf("Status   : %s\n", tugas[k].status);
        }
        return 0;
    }
}

int cari() 
{
    FILE *file = fopen("WorkTracker.dat", "rb");
    if (file == NULL)
    {
        printf("Gagal membuka file!!!\n");
        return 1;
    }

    char cariKategori[100];
    printf("Masukkan kategori yang anda cari : ");
    cin.ignore();
    cin.getline(cariKategori, sizeof(cariKategori));
    printf("%s",cariKategori);
    system("pause");
    data tugas;
    bool ditemukan = false;
    while (fread(&tugas, sizeof(data), 1, file))
    {
        if (strcmp(tugas.kategori, cariKategori) == 0)
        {
            printf("Tugas: %s\n", tugas.nama);
            printf("Kategori: %s\n", tugas.kategori);
            printf("Deadline: %02d-%02d-%04d\n", tugas.tenggat.tgl, tugas.tenggat.bln, tugas.tenggat.thn);
            printf("Status: %s\n\n", tugas.status);
            ditemukan = true;
        }
    }

    if (!ditemukan)
    {
        printf("Tugas dalam kategori ini tidak ada\n");
    }

    fclose(file);
    return 0;
}

int tampilLewatDeadline()
{
    return 0;
}

int perbaruiStatus()
{
    return 0;
}

int hapusTugas()
{
    return 0;
}