#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct Barang {
    int idBarang;
    string namaBarang;
    int stok;
    float harga;
};

struct NodeBarang {
    Barang data;
    NodeBarang* prev;
    NodeBarang* next;
};

NodeBarang* head = nullptr; // Pointer ke head dari linked list

// Fungsi-fungsi untuk manipulasi double linked list
void tambahBarang(int id, string nama, int stok, float harga) {
    NodeBarang* newNode = new NodeBarang;
    newNode->data.idBarang = id;
    newNode->data.namaBarang = nama;
    newNode->data.stok = stok;
    newNode->data.harga = harga;
    newNode->prev = nullptr;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        NodeBarang* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

void hapusBarang(int id) {
    NodeBarang* temp = head;
    while (temp != nullptr) {
        if (temp->data.idBarang == id) {
            if (temp->prev != nullptr) {
                temp->prev->next = temp->next;
            } else {
                head = temp->next;
            }
            if (temp->next != nullptr) {
                temp->next->prev = temp->prev;
            }
            delete temp;
            cout << "Barang dengan ID " << id << " telah dihapus." << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Barang dengan ID " << id << " tidak ditemukan." << endl;
}

void tampilkanBarang() {
    NodeBarang* temp = head;
    while (temp != nullptr) {
        cout << "ID    : " << temp->data.idBarang << endl;
        cout << "Nama  : " << temp->data.namaBarang << endl;
        cout << "Stok  : " << temp->data.stok << endl;
        cout << "Harga : " << temp->data.harga << endl;
        temp = temp->next;
    }
}

// Fungsi untuk antrian pembelian (queue)
queue<Barang> antrianPembelian;

void tambahKeAntrian(int id, int jumlah) {
    NodeBarang* temp = head;
    while (temp != nullptr) {
        if (temp->data.idBarang == id) {
            Barang beli = temp->data;
            beli.stok = jumlah;
            antrianPembelian.push(beli);
            cout << "Barang dengan ID " << id << " sejumlah " << jumlah << " telah ditambahkan ke antrian pembelian." << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Barang dengan ID " << id << " tidak ditemukan." << endl;
}

void prosesPembelian() {
    while (!antrianPembelian.empty()) {
        Barang beli = antrianPembelian.front();
        NodeBarang* temp = head;
        while (temp != nullptr) {
            if (temp->data.idBarang == beli.idBarang) {
                if (temp->data.stok >= beli.stok) {
                    temp->data.stok -= beli.stok;
                    cout << "Pembelian berhasil: " << beli.namaBarang << " sejumlah " << beli.stok << endl;
                } else {
                    cout << "Stok tidak mencukupi untuk " << beli.namaBarang << " sejumlah " << beli.stok << endl;
                }
                break;
            }
            temp = temp->next;
        }
        antrianPembelian.pop();
    }
}

// Fungsi untuk menampilkan menu
void tampilkanMenu() {
    cout << "Pilih operasi yang ingin dilakukan:" << endl;
    cout << "1. Tambah Barang" << endl;
    cout << "2. Hapus Barang" << endl;
    cout << "3. Tampilkan Barang" << endl;
    cout << "4. Tambahkan ke Antrian Pembelian" << endl;
    cout << "5. Proses Pembelian" << endl;
    cout << "6. Keluar" << endl;
    cout << "Pilihan Anda: ";
}

// Inisialisasi daftar barang
void inisialisasiDaftarBarang() {
    tambahBarang(1, "Beras", 100, 15000);
    tambahBarang(2, "Gula", 50, 12000);
    tambahBarang(3, "Sabun", 200, 5000);
}

// Fungsi main dengan menu
int main() {
    // Menambahkan beberapa barang ke daftar saat program dimulai
    inisialisasiDaftarBarang();
    
    int pilihan;
    do {
        tampilkanMenu();
        cin >> pilihan;
        switch (pilihan) {
            case 1: {
                int id;
                string nama;
                int stok;
                float harga;
                cout << "Masukkan ID Barang: ";
                cin >> id;
                cout << "Masukkan Nama Barang: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan Stok Barang: ";
                cin >> stok;
                cout << "Masukkan Harga Barang: ";
                cin >> harga;
                tambahBarang(id, nama, stok, harga);
                break;
            }
            case 2: {
                int idHapus;
                cout << "Masukkan ID Barang yang akan dihapus: ";
                cin >> idHapus;
                hapusBarang(idHapus);
                break;
            }
            case 3: {
                cout << "Daftar Barang:" << endl;
                tampilkanBarang();
                break;
            }
            case 4: {
                int idBeli, jumlahBeli;
                cout << "Masukkan ID Barang yang akan dibeli: ";
                cin >> idBeli;
                cout << "Masukkan Jumlah Barang yang akan dibeli: ";
                cin >> jumlahBeli;
                tambahKeAntrian(idBeli, jumlahBeli);
                break;
            }
            case 5: {
                prosesPembelian();
                break;
            }
            case 6: {
                cout << "Terima kasih! Program selesai." << endl;
                break;
            }
            default: {
                cout << "Pilihan tidak valid!" << endl;
                break;
            }
        }
    } while (pilihan != 6);

    return 0;
}

