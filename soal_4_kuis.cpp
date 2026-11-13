#include <iostream>
#include <string>
using namespace std;

const int SIZE = 20;

struct Mahasiswa {
    long long nim;
    string nama;
    int status;
};

Mahasiswa tabel[SIZE];

int hash1(long long key) {
    return key % SIZE;
}

int hash2(long long key) {
    return 19 - (key % 19);
}

int cariIndex(long long nim) {
    int h1 = hash1(nim);
    int h2 = hash2(nim);

    for (int i = 0; i < SIZE; i++) {
        int index = (h1 + i * h2) % SIZE;

        if (tabel[index].status == 0) {
            return -1;
        }

        if (tabel[index].status == 1 && tabel[index].nim == nim) {
            return index;
        }
    }

    return -1;
}

void insert(long long nim, string nama) {
    if (cariIndex(nim) != -1) {
        cout << "NIM sudah terdaftar.\n";
        return;
    }

    int h1 = hash1(nim);
    int h2 = hash2(nim);

    for (int i = 0; i < SIZE; i++) {
        int index = (h1 + i * h2) % SIZE;

        if (tabel[index].status == 0 || tabel[index].status == 2) {
            tabel[index].nim = nim;
            tabel[index].nama = nama;
            tabel[index].status = 1;

            cout << "Data mahasiswa berhasil ditambahkan.\n";
            return;
        }
    }

    cout << "Hash Table penuh.\n";
}

void search(long long nim) {
    int index = cariIndex(nim);

    if (index != -1) {
        cout << "Data mahasiswa ditemukan.\n";
        cout << "NIM: " << tabel[index].nim << "\n";
        cout << "Nama: " << tabel[index].nama << "\n";
        cout << "Index: " << index << "\n";
    } else {
        cout << "Data mahasiswa tidak ditemukan.\n";
    }
}

void removeData(long long nim) {
    int index = cariIndex(nim);

    if (index != -1) {
        tabel[index].status = 2;
        cout << "Data mahasiswa berhasil dihapus.\n";
    } else {
        cout << "Data mahasiswa tidak ditemukan.\n";
    }
}

void display() {
    cout << "\n=== ISI HASH TABLE ===\n";

    for (int i = 0; i < SIZE; i++) {
        cout << "Index " << i << ": ";

        if (tabel[i].status == 1) {
            cout << tabel[i].nim << " - " << tabel[i].nama;
        } else if (tabel[i].status == 2) {
            cout << "Data dihapus";
        } else {
            cout << "Kosong";
        }

        cout << "\n";
    }
}

void isiDataAwal() {
    insert(2401001, "Andi");
    insert(2401002, "Budi");
    insert(2401003, "Citra");
    insert(2401004, "Dina");
    insert(2401005, "Eko");
    insert(2401006, "Fajar");
    insert(2401007, "Gita");
    insert(2401008, "Hani");
    insert(2401009, "Indra");
    insert(2401010, "Joko");
    insert(2401011, "Kiki");
    insert(2401012, "Lina");
    insert(2401013, "Maya");
    insert(2401014, "Nanda");
    insert(2401015, "Oki");
}

int main() {
    int pilihan;
    long long nim;
    string nama;

    isiDataAwal();

    do {
        cout << "\n=== SISTEM HASH TABLE MAHASISWA ===\n";
        cout << "1. Insert Data\n";
        cout << "2. Search Data\n";
        cout << "3. Remove Data\n";
        cout << "4. Display Hash Table\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan NIM: ";
                cin >> nim;

                cin.ignore();
                cout << "Masukkan Nama: ";
                getline(cin, nama);

                insert(nim, nama);
                break;

            case 2:
                cout << "Masukkan NIM yang dicari: ";
                cin >> nim;
                search(nim);
                break;

            case 3:
                cout << "Masukkan NIM yang dihapus: ";
                cin >> nim;
                removeData(nim);
                break;

            case 4:
                display();
                break;

            case 0:
                cout << "Program selesai.\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);

    return 0;
}