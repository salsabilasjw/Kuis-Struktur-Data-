#include <iostream>
#include <string>
using namespace std;

struct NodeQueue {
    string nama;
    NodeQueue* next;
};

struct NodeStack {
    int idBuku;
    NodeStack* next;
};

struct NodeBST {
    int idBuku;
    NodeBST* left;
    NodeBST* right;
};

NodeQueue* frontQueue = nullptr;
NodeQueue* rearQueue = nullptr;
NodeStack* topStack = nullptr;
NodeBST* root = nullptr;

void tambahAntrean(string nama) {
    NodeQueue* baru = new NodeQueue{nama, nullptr};

    if (frontQueue == nullptr) {
        frontQueue = rearQueue = baru;
    } else {
        rearQueue->next = baru;
        rearQueue = baru;
    }

    cout << nama << " masuk ke antrean peminjaman.\n";
}

void prosesAntrean() {
    if (frontQueue == nullptr) {
        cout << "Antrean kosong.\n";
        return;
    }

    NodeQueue* hapus = frontQueue;
    cout << "Mahasiswa yang dilayani: " << hapus->nama << "\n";

    frontQueue = frontQueue->next;

    if (frontQueue == nullptr) {
        rearQueue = nullptr;
    }

    delete hapus;
}

void tampilkanAntrean() {
    if (frontQueue == nullptr) {
        cout << "Antrean kosong.\n";
        return;
    }

    NodeQueue* bantu = frontQueue;

    cout << "Antrean peminjaman:\n";
    while (bantu != nullptr) {
        cout << bantu->nama << "\n";
        bantu = bantu->next;
    }
}

void tambahRiwayat(int idBuku) {
    NodeStack* baru = new NodeStack{idBuku, topStack};
    topStack = baru;

    cout << "Buku ID " << idBuku << " berhasil dikembalikan.\n";
}

void tampilkanRiwayat() {
    if (topStack == nullptr) {
        cout << "Riwayat pengembalian kosong.\n";
        return;
    }

    NodeStack* bantu = topStack;

    cout << "Riwayat pengembalian (LIFO):\n";
    while (bantu != nullptr) {
        cout << "ID Buku: " << bantu->idBuku << "\n";
        bantu = bantu->next;
    }
}

NodeBST* tambahBuku(NodeBST* node, int idBuku) {
    if (node == nullptr) {
        return new NodeBST{idBuku, nullptr, nullptr};
    }

    if (idBuku < node->idBuku) {
        node->left = tambahBuku(node->left, idBuku);
    } else if (idBuku > node->idBuku) {
        node->right = tambahBuku(node->right, idBuku);
    } else {
        cout << "ID buku sudah ada.\n";
    }

    return node;
}

bool cariBuku(NodeBST* node, int idBuku) {
    if (node == nullptr) {
        return false;
    }

    if (node->idBuku == idBuku) {
        return true;
    }

    if (idBuku < node->idBuku) {
        return cariBuku(node->left, idBuku);
    }

    return cariBuku(node->right, idBuku);
}

void preOrder(NodeBST* node) {
    if (node != nullptr) {
        cout << node->idBuku << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
}

void inOrder(NodeBST* node) {
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->idBuku << " ";
        inOrder(node->right);
    }
}

void postOrder(NodeBST* node) {
    if (node != nullptr) {
        postOrder(node->left);
        postOrder(node->right);
        cout << node->idBuku << " ";
    }
}

int main() {
    int pilihan, idBuku;
    string nama;

    do {
        cout << "\n=== SISTEM PERPUSTAKAAN ===\n";
        cout << "1. Tambah antrean peminjaman\n";
        cout << "2. Proses antrean peminjaman\n";
        cout << "3. Tampilkan antrean\n";
        cout << "4. Pengembalian buku\n";
        cout << "5. Tampilkan riwayat pengembalian\n";
        cout << "6. Tambah ID buku ke BST\n";
        cout << "7. Cari ID buku\n";
        cout << "8. Tampilkan traversal BST\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan nama mahasiswa: ";
                cin.ignore();
                getline(cin, nama);
                tambahAntrean(nama);
                break;

            case 2:
                prosesAntrean();
                break;

            case 3:
                tampilkanAntrean();
                break;

            case 4:
                cout << "Masukkan ID buku yang dikembalikan: ";
                cin >> idBuku;
                tambahRiwayat(idBuku);
                break;

            case 5:
                tampilkanRiwayat();
                break;

            case 6:
                cout << "Masukkan ID buku: ";
                cin >> idBuku;
                root = tambahBuku(root, idBuku);
                cout << "ID buku berhasil dimasukkan ke BST.\n";
                break;

            case 7:
                cout << "Masukkan ID buku yang dicari: ";
                cin >> idBuku;

                if (cariBuku(root, idBuku)) {
                    cout << "ID buku ditemukan.\n";
                } else {
                    cout << "ID buku tidak ditemukan.\n";
                }
                break;

            case 8:
                cout << "Pre-Order: ";
                preOrder(root);
                cout << "\n";

                cout << "In-Order: ";
                inOrder(root);
                cout << "\n";

                cout << "Post-Order: ";
                postOrder(root);
                cout << "\n";
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