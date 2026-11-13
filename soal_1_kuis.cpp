
#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

struct Mahasiswa {
    string nim;
    string nama;
    int nilai;
    Mahasiswa* next;
};

Mahasiswa* head = nullptr;
vector<int> dataNilai;
bool nilaiTerurut = false;

void tambahMahasiswa() {
    Mahasiswa* baru = new Mahasiswa;

    cout << "\nMasukkan NIM: ";
    getline(cin, baru->nim);

    cout << "Masukkan Nama: ";
    getline(cin, baru->nama);

    cout << "Masukkan Nilai: ";
    cin >> baru->nilai;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    baru->next = nullptr;

    if (head == nullptr) {
        head = baru;
    } else {
        Mahasiswa* temp = head;

        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = baru;
    }

    dataNilai.push_back(baru->nilai);
    nilaiTerurut = false;

    cout << "\nData mahasiswa berhasil ditambahkan!\n";
}

void tampilkanMahasiswa() {
    if (head == nullptr) {
        cout << "\nData mahasiswa masih kosong.\n";
        return;
    }

    Mahasiswa* temp = head;

    cout << "\n=== DATA MAHASISWA ===\n";

    while (temp != nullptr) {
        cout << "NIM   : " << temp->nim << "\n";
        cout << "Nama  : " << temp->nama << "\n";
        cout << "Nilai : " << temp->nilai << "\n";
        cout << "----------------------\n";

        temp = temp->next;
    }

    cout << "\n=== DYNAMIC ARRAY NILAI ===\n";

    for (int i = 0; i < dataNilai.size(); i++) {
        cout << dataNilai[i] << " ";
    }

    cout << "\n";
}

void insertionSort() {
    if (dataNilai.empty()) {
        cout << "\nData nilai masih kosong.\n";
        return;
    }

    for (int i = 1; i < dataNilai.size(); i++) {
        int key = dataNilai[i];
        int j = i - 1;

        while (j >= 0 && dataNilai[j] > key) {
            dataNilai[j + 1] = dataNilai[j];
            j--;
        }

        dataNilai[j + 1] = key;
    }

    nilaiTerurut = true;

    cout << "\nNilai berhasil diurutkan: ";

    for (int i = 0; i < dataNilai.size(); i++) {
        cout << dataNilai[i] << " ";
    }

    cout << "\n";
}

void linearSearch() {
    if (head == nullptr) {
        cout << "\nData mahasiswa masih kosong.\n";
        return;
    }

    string cariNIM;

    cout << "\nMasukkan NIM yang dicari: ";
    getline(cin, cariNIM);

    Mahasiswa* temp = head;
    bool ditemukan = false;

    while (temp != nullptr) {
        if (temp->nim == cariNIM) {
            cout << "\nMahasiswa ditemukan!\n";
            cout << "NIM   : " << temp->nim << "\n";
            cout << "Nama  : " << temp->nama << "\n";
            cout << "Nilai : " << temp->nilai << "\n";

            ditemukan = true;
            break;
        }

        temp = temp->next;
    }

    if (!ditemukan) {
        cout << "\nMahasiswa tidak ditemukan.\n";
    }
}

void binarySearch() {
    if (dataNilai.empty()) {
        cout << "\nData nilai masih kosong.\n";
        return;
    }

    if (!nilaiTerurut) {
        cout << "\nUrutkan nilai terlebih dahulu!\n";
        return;
    }

    int cariNilai;

    cout << "\nMasukkan nilai yang dicari: ";
    cin >> cariNilai;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int kiri = 0;
    int kanan = dataNilai.size() - 1;
    bool ditemukan = false;

    while (kiri <= kanan) {
        int tengah = kiri + (kanan - kiri) / 2;

        if (dataNilai[tengah] == cariNilai) {
            cout << "\nNilai ditemukan pada indeks "
                 << tengah << " (posisi " << tengah + 1 << ").\n";

            ditemukan = true;
            break;
        } else if (dataNilai[tengah] < cariNilai) {
            kiri = tengah + 1;
        } else {
            kanan = tengah - 1;
        }
    }

    if (!ditemukan) {
        cout << "\nNilai tidak ditemukan.\n";
    }
}

int main() {
    int pilihan;

    do {
        cout << "\n==================================\n";
        cout << "SISTEM PENGELOLAAN NILAI MAHASISWA\n";
        cout << "==================================\n";
        cout << "1. Tambah Mahasiswa\n";
        cout << "2. Tampilkan Data\n";
        cout << "3. Urutkan Nilai (Insertion Sort)\n";
        cout << "4. Cari Mahasiswa (Linear Search)\n";
        cout << "5. Cari Nilai (Binary Search)\n";
        cout << "0. Keluar\n";
        cout << "==================================\n";
        cout << "Pilihan: ";

        cin >> pilihan;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilihan) {
            case 1:
                tambahMahasiswa();
                break;
            case 2:
                tampilkanMahasiswa();
                break;
            case 3:
                insertionSort();
                break;
            case 4:
                linearSearch();
                break;
            case 5:
                binarySearch();
                break;
            case 0:
                cout << "\nProgram selesai.\n";
                break;
            default:
                cout << "\nPilihan tidak valid.\n";
        }

    } while (pilihan != 0);

    Mahasiswa* temp = head;

    while (temp != nullptr) {
        Mahasiswa* hapus = temp;
        temp = temp->next;
        delete hapus;
    }

    return 0;
}
