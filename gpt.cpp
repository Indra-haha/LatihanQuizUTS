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
    char namaTugas[100];
    char kategori[50];
    struct deadline tenggat;
    char status[20];
};

int tambahTugas();
int tampilTugas();
int cariTugasKategori();
int tampilLewatDeadline();
int perbaruiStatus();
int hapusTugas();
int validasiTugas(char namaTugas[]);

int main()
{
    int pil;
    bool errorMenu = false;
    char kembali;

    do
    {
        system("cls");
        errorMenu = false;
        printf("-----------------Work Tracker-----------------\n");
        printf("1. Menambahkan Tugas Baru\n");
        printf("2. Menampilkan Daftar Tugas\n");
        printf("3. Mencari Tugas berdasarkan Kategori\n");
        printf("4. Menampilkan Tugas yang Melewati Deadline\n");
        printf("5. Memperbarui Status Tugas\n");
        printf("6. Menghapus Tugas yang Sudah Selesai\n");
        printf("7. Keluar\n");
        printf("----------------------------------------------\n");
        printf("Pilih : ");
        scanf("%d", &pil);

        switch (pil)
        {
        case 1:
            tambahTugas();
            break;
        case 2:
            tampilTugas();
            break;
        case 3:
            cariTugasKategori();
            break;
        case 4:
            tampilLewatDeadline();
            break;
        case 5:
            perbaruiStatus();
            break;
        case 6:
            hapusTugas();
            break;
        case 7:
            printf("Terima kasih telah menggunakan WorkTracker! Tetap produktif!\n");
            break;
        default:
            printf("Pilihan tidak ada. Pilih angka 1-7.\n");
            system("pause");
            errorMenu = true;
            break;
        }

        if (pil != 7)
        {
            printf("Kembali ke menu [y/n] : ");
            cin >> kembali;
        }

    } while (kembali == 'y' || errorMenu);

    return 0;
}

int tambahTugas()
{
    FILE *file = fopen("WorkTracker.dat", "ab");
    if (file == NULL)
    {
        printf("Gagal membuka file untuk menambahkan tugas.\n");
        return 1;
    }

    data tugas;
    char namaTugas[100];
    bool tugasTersedia = false;

    printf("Masukkan Nama Tugas: ");
    cin.ignore();
    cin.getline(namaTugas, sizeof(namaTugas));

    // Validasi jika tugas sudah ada
    tugasTersedia = validasiTugas(namaTugas);
    if (tugasTersedia)
    {
        printf("Tugas ini sudah terdaftar!\n");
        fclose(file);
        return 1;
    }

    strcpy(tugas.namaTugas, namaTugas);

    printf("Masukkan Kategori tugas: ");
    cin.getline(tugas.kategori, sizeof(tugas.kategori));
    printf("Masukkan Tgl Deadline (DD/MM/YYYY): ");
    cin >> tugas.tenggat.tgl >> tugas.tenggat.bln >> tugas.tenggat.thn;
    cin.ignore();
    strcpy(tugas.status, "Belum Selesai");

    fwrite(&tugas, sizeof(data), 1, file);
    printf("Tugas berhasil ditambahkan.\n");

    fclose(file);
    return 0;
}

int validasiTugas(char namaTugas[])
{
    FILE *file = fopen("WorkTracker.dat", "rb");
    if (file == NULL)
    {
        printf("Gagal membuka file untuk validasi.\n");
        return 0;
    }

    data tugas;
    while (fread(&tugas, sizeof(data), 1, file))
    {
        if (strcmp(tugas.namaTugas, namaTugas) == 0)
        {
            fclose(file);
            return 1; // Tugas sudah ada
        }
    }

    fclose(file);
    return 0; // Tugas tidak ada
}

int tampilTugas()
{
    FILE *file = fopen("WorkTracker.dat", "rb");
    if (file == NULL)
    {
        printf("Gagal membuka file untuk menampilkan tugas.\n");
        return 1;
    }

    data tugas[100];
    int jumlah = 0;
    while (fread(&tugas[jumlah], sizeof(data), 1, file))
    {
        jumlah++;
    }

    fclose(file);

    // Sorting tugas berdasarkan deadline (Descending)
    for (int i = 0; i < jumlah - 1; i++)
    {
        for (int j = i + 1; j < jumlah; j++)
        {
            if (tugas[i].tenggat.thn < tugas[j].tenggat.thn ||
                (tugas[i].tenggat.thn == tugas[j].tenggat.thn && tugas[i].tenggat.bln < tugas[j].tenggat.bln) ||
                (tugas[i].tenggat.thn == tugas[j].tenggat.thn && tugas[i].tenggat.bln == tugas[j].tenggat.bln && tugas[i].tenggat.tgl < tugas[j].tenggat.tgl))
            {
                data temp = tugas[i];
                tugas[i] = tugas[j];
                tugas[j] = temp;
            }
        }
    }

    // Menampilkan tugas
    for (int i = 0; i < jumlah; i++)
    {
        printf("Tugas: %s\n", tugas[i].namaTugas);
        printf("Kategori: %s\n", tugas[i].kategori);
        printf("Deadline: %02d-%02d-%04d\n", tugas[i].tenggat.tgl, tugas[i].tenggat.bln, tugas[i].tenggat.thn);
        printf("Status: %s\n\n", tugas[i].status);
    }

    return 0;
}

int cariTugasKategori()
{
    FILE *file = fopen("WorkTracker.dat", "rb");
    if (file == NULL)
    {
        printf("Gagal membuka file untuk mencari tugas.\n");
        return 1;
    }

    char kategori[50];
    printf("Masukkan kategori untuk pencarian: ");
    cin.ignore();
    cin.getline(kategori, sizeof(kategori));

    data tugas;
    bool tugasDitemukan = false;
    while (fread(&tugas, sizeof(data), 1, file))
    {
        if (strcmp(tugas.kategori, kategori) == 0)
        {
            printf("Tugas: %s\n", tugas.namaTugas);
            printf("Kategori: %s\n", tugas.kategori);
            printf("Deadline: %02d-%02d-%04d\n", tugas.tenggat.tgl, tugas.tenggat.bln, tugas.tenggat.thn);
            printf("Status: %s\n\n", tugas.status);
            tugasDitemukan = true;
        }
    }

    if (!tugasDitemukan)
    {
        printf("Tidak ada tugas dalam kategori ini!\n");
    }

    fclose(file);
    return 0;
}

int tampilLewatDeadline()
{
    FILE *file = fopen("WorkTracker.dat", "rb");
    if (file == NULL)
    {
        printf("Gagal membuka file untuk menampilkan tugas lewat deadline.\n");
        return 1;
    }

    time_t now = time(0);
    struct tm *ltm = localtime(&now);
    int tahunSekarang = 1900 + ltm->tm_year;
    int bulanSekarang = 1 + ltm->tm_mon;
    int hariSekarang = ltm->tm_mday;

    data tugas;
    bool tugasLewatDeadline = false;

    while (fread(&tugas, sizeof(data), 1, file))
    {
        if (tugas.tenggat.thn < tahunSekarang ||
            (tugas.tenggat.thn == tahunSekarang && tugas.tenggat.bln < bulanSekarang) ||
            (tugas.tenggat.thn == tahunSekarang && tugas.tenggat.bln == bulanSekarang && tugas.tenggat.tgl < hariSekarang))
        {
            if (strcmp(tugas.status, "Belum Selesai") == 0)
            {
                if (!tugasLewatDeadline)
                {
                    printf("Perhatian! Tugas berikut sudah melewati deadline:\n");
                    tugasLewatDeadline = true;
                }
                printf("Tugas: %s\n", tugas.namaTugas);
                printf("Kategori: %s\n", tugas.kategori);
                printf("Deadline: %02d-%02d-%04d\n", tugas.tenggat.tgl, tugas.tenggat.bln, tugas.tenggat.thn);
                printf("Status: %s\n\n", tugas.status);
            }
        }
    }

    if (!tugasLewatDeadline)
    {
        printf("Semua tugas masih dalam batas waktu.\n");
    }

    fclose(file);
    return 0;
}

int perbaruiStatus()
{
    FILE *file = fopen("WorkTracker.dat", "r+b");
    if (file == NULL)
    {
        printf("Gagal membuka file untuk memperbarui status.\n");
        return 1;
    }

    char namaTugas[100];
    printf("Masukkan Nama Tugas yang ingin diperbarui statusnya: ");
    cin.ignore();
    cin.getline(namaTugas, sizeof(namaTugas));

    data tugas;
    bool tugasDitemukan = false;
    while (fread(&tugas, sizeof(data), 1, file))
    {
        if (strcmp(tugas.namaTugas, namaTugas) == 0)
        {
            tugasDitemukan = true;
            printf("Tugas ditemukan. Memperbarui status menjadi 'Selesai'.\n");
            strcpy(tugas.status, "Selesai");

            fseek(file, -sizeof(data), SEEK_CUR);
            fwrite(&tugas, sizeof(data), 1, file);
            break;
        }
    }

    if (!tugasDitemukan)
    {
        printf("Tugas tidak ditemukan!\n");
    }

    fclose(file);
    return 0;
}

int hapusTugas()
{
    FILE *file = fopen("WorkTracker.dat", "rb");
    if (file == NULL)
    {
        printf("Gagal membuka file untuk menghapus tugas.\n");
        return 1;
    }

    FILE *tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL)
    {
        printf("Gagal membuka file sementara untuk menghapus tugas.\n");
        fclose(file);
        return 1;
    }

    char namaTugas[100];
    printf("Masukkan Nama Tugas yang ingin dihapus: ");
    cin.ignore();
    cin.getline(namaTugas, sizeof(namaTugas));

    data tugas;
    bool tugasDitemukan = false;
    while (fread(&tugas, sizeof(data), 1, file))
    {
        if (strcmp(tugas.namaTugas, namaTugas) == 0)
        {
            if (strcmp(tugas.status, "Selesai") == 0)
            {
                tugasDitemukan = true;
            }
            else
            {
                fwrite(&tugas, sizeof(data), 1, tempFile);
            }
        }
        else
        {
            fwrite(&tugas, sizeof(data), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (tugasDitemukan)
    {
        remove("WorkTracker.dat");
        rename("temp.dat", "WorkTracker.dat");
        printf("Tugas berhasil dihapus.\n");
    }
    else
    {
        remove("temp.dat");
        printf("Tugas tidak ditemukan atau belum selesai.\n");
    }

    return 0;
}
