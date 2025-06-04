#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Node {
    int nomor;
    int nomorMeja;
    string nama;
    string pesanan;
    Node* next;
    Node* prev;
};

Node* awal = nullptr;
Node* akhir = nullptr;

bool listkosong() {
    return (awal == nullptr);
}

void tambahAntrian(int nomorBaru, int nomorMejaBaru, string namaBaru, string pesananBaru) {
    Node* NB = new Node;
    NB->nomor = nomorBaru;
    NB->nomorMeja = nomorMejaBaru;
    NB->nama = namaBaru;
    NB->pesanan = pesananBaru;
    NB->next = nullptr;
    NB->prev = nullptr;

    if (listkosong()) {
        awal = akhir = NB;
    } else if (NB->nama <= awal->nama) {
        NB->next = awal;
        awal->prev = NB;
        awal = NB;
    } else {
        Node* bantu = awal;
        while (bantu->next != nullptr && NB->nama > bantu->next->nama) {
            bantu = bantu->next;
        }
        NB->next = bantu->next;
        if (bantu->next != nullptr) {
            bantu->next->prev = NB;
        }
        NB->prev = bantu;
        bantu->next = NB;

        if (NB->next == nullptr) {
            akhir = NB;
        }
    }
}

void simpanFile(Node* node) {
    FILE* file = fopen("riwayat.txt", "a");
    if (file == nullptr) {
        cout << "Gagal membuka file riwayat.\n";
        return;
    }
    fprintf(file, "%d,%s,%d,%s\n", node->nomor, node->nama.c_str(), node->nomorMeja, node->pesanan.c_str());
    fclose(file);
}

void layani() {
    if (listkosong()) {
        cout << "Tidak ada antrian.\n";
        return;
    }

    Node* temp = awal;

    int id = temp->nomor;
    int noMeja = temp->nomorMeja;
    string nama = temp->nama;
    string pesanan = temp->pesanan;

    cout << "Melayani ID " << id << " atas nama " << nama << "\n";

    // Simpan ke riwayat
    simpanFile(temp);

    if (awal == akhir) {
        awal = akhir = nullptr;
    } else {
        awal = awal->next;
        awal->prev = nullptr;
    }
    delete temp;

    cout << "Pelanggan dengan ID " << id << " telah dilayani.\n";
}

void edit(int nomor) {
    Node* bantu = awal;
    while (bantu != nullptr) {
        if (bantu->nomor == nomor) {
            cout << "Edit data untuk ID " << nomor << ":\n";
            cout << "Nama baru: ";
            cin.ignore();
            getline(cin, bantu->nama);
            cout << "Nomor kursi baru: ";
            cin >> bantu->nomorMeja;
            cin.ignore();
            cout << "Pesanan baru: ";
            getline(cin, bantu->pesanan);
            cout << "Berhasil diubah.\n";
            return;
        }
        bantu = bantu->next;
    }
    cout << "ID tidak ditemukan.\n";
}

void hapus(int nomor) {
    Node* bantu = awal;
    while (bantu != nullptr && bantu->nomor != nomor) {
        bantu = bantu->next;
    }
    if (bantu == nullptr) {
        cout << "ID tidak ditemukan.\n";
        return;
    }

    if (bantu == awal && bantu == akhir) {
        awal = akhir = nullptr;
    } else if (bantu == awal) {
        awal = awal->next;
        awal->prev = nullptr;
    } else if (bantu == akhir) {
        akhir = akhir->prev;
        akhir->next = nullptr;
    } else {
        bantu->prev->next = bantu->next;
        bantu->next->prev = bantu->prev;
    }

    delete bantu;
    cout << "Data berhasil dihapus.\n";
}

void tampil() {
    cout << "\n==== DAFTAR ANTRIAN ====\n";

    if (listkosong()) {
        cout << "Antrian kosong!\n";
    } else {
        cout << left << setw(5) << "ID"
             << setw(20) << "Nama"
             << setw(10) << "No.Meja"
             << setw(25) << "Pesanan" << endl;
        cout << string(60, '-') << endl;

        Node* bantu = awal;
        while (bantu != nullptr) {
            cout << left << setw(5) << bantu->nomor
                 << setw(20) << bantu->nama
                 << setw(10) << bantu->nomorMeja
                 << setw(25) << bantu->pesanan << endl;
            bantu = bantu->next;
        }
    }
    cout << "\nTekan Enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

void menumakanan() {
    cout << "\n"
         << "=============================================\n"
         << "           MENU RESTORAN GACOAN              \n"
         << "=============================================\n"
         << "| No |        Nama Menu        |   Harga    |\n"
         << "=============================================\n"

         << "|    |      ** MIE GACOAN **   |            |\n"
         << "| 1  | Mie Gacoan Level 0      | Rp 15.000  |\n"
         << "| 2  | Mie Gacoan Level 1      | Rp 15.000  |\n"
         << "| 3  | Mie Gacoan Level 2      | Rp 15.000  |\n"
         << "| 4  | Mie Gacoan Level 3      | Rp 15.000  |\n"
         << "| 5  | Mie Gacoan Level 4      | Rp 15.000  |\n"
         << "| 6  | Mie Gacoan Level 5      | Rp 15.000  |\n"
         << "---------------------------------------------\n"

         << "|    |      ** DIMSUM **       |            |\n"
         << "| 7  | Dimsum Ayam (4 pcs)     | Rp 12.000  |\n"
         << "| 8  | Dimsum Udang (4 pcs)    | Rp 15.000  |\n"
         << "| 9  | Dimsum Kulit (4 pcs)    | Rp 10.000  |\n"
         << "---------------------------------------------\n"

         << "|    |    ** TAHU & TEMPE **   |            |\n"
         << "| 10 | Tahu Gejrot             | Rp 8.000   |\n"
         << "| 11 | Tahu Crispy             | Rp 10.000  |\n"
         << "| 12 | Tempe Mendoan           | Rp 8.000   |\n"
         << "---------------------------------------------\n"

         << "|    |      ** MINUMAN **      |            |\n"
         << "| 13 | Es Teh Manis            | Rp 5.000   |\n"
         << "| 14 | Es Jeruk                | Rp 7.000   |\n"
         << "| 15 | Es Cappuccino           | Rp 12.000  |\n"
         << "| 16 | Air Mineral             | Rp 3.000   |\n"
         << "---------------------------------------------\n"

         << "|    |      ** SNACK **        |            |\n"
         << "| 17 | Kerupuk                 | Rp 2.000   |\n"
         << "| 18 | Rempeyek                | Rp 3.000   |\n"
         << "| 19 | Emping                  | Rp 4.000   |\n"
         << "=============================================\n"
         << "       * Level pedas: 0 = Tidak Pedas *      \n"
         << "      * Level pedas: 1-5 = Makin Pedas *     \n"
         << "=============================================\n";
}

int cariHarga(int noMenu) {
    switch (noMenu) {
        case 1: case 2: case 3: case 4: case 5: case 6: return 15000;
        case 7: return 12000;
        case 8: return 15000;
        case 9: return 10000;
        case 10: return 8000;
        case 11: return 10000;
        case 12: return 8000;
        case 13: return 5000;
        case 14: return 7000;
        case 15: return 12000;
        case 16: return 3000;
        case 17: return 2000;
        case 18: return 3000;
        case 19: return 4000;
        default: return 0;
    }
}

void sorting() {
    if (listkosong() || awal == akhir) {
        cout << "Data kurang untuk diurutkan.\n";
        return;
    }

    bool swapped;
    do {
        swapped = false;
        Node* current = awal;

        while (current->next != nullptr) {
            if (current->nama > current->next->nama) {
                // Tukar data saja (bukan node)
                swap(current->nomor, current->next->nomor);
                swap(current->nomorMeja, current->next->nomorMeja);
                swap(current->nama, current->next->nama);
                swap(current->pesanan, current->next->pesanan);

                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);

    cout << "Data berhasil diurutkan berdasarkan nama.\n";
}

Node* cari(string namaCari) {
    Node* bantu = awal;
    while (bantu != nullptr) {
        if (bantu->nama == namaCari) {
            return bantu;
        }
        bantu = bantu->next;
    }
    return nullptr;
}

void riwayat() {
    FILE* file = fopen("riwayat.txt", "r");
    if (file == nullptr) {
        cout << "Tidak ada riwayat.\n";
        return;
    }

    cout << "\n=== RIWAYAT PELAYANAN ===\n";
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        cout << line;
    }
    fclose(file);

    cout << "\nTekan Enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

int inputPesanan() {
    char lagi;
    int totalBayar = 0;
    string detailPesanan = "";

    do {
        menumakanan();

        int noMenu;
        cout << "Masukkan nomor menu (1-19): ";
        cin >> noMenu;

        int harga = cariHarga(noMenu);
        if (harga == 0) {
            cout << "Nomor menu tidak valid!\n";
            continue;
        }

        int jumlah;
        cout << "Jumlah pesanan: ";
        cin >> jumlah;

        int subtotal = harga * jumlah;
        totalBayar += subtotal;

        cout << "Subtotal: Rp " << subtotal << "\n";

        // Tambah ke detail pesanan
        detailPesanan += "NoMenu " + to_string(noMenu) + " x" + to_string(jumlah) + ", ";

        cout << "Pesan lagi? (y/n): ";
        cin >> lagi;
    } while (lagi == 'y' || lagi == 'Y');

    cout << "Total yang harus dibayar: Rp " << totalBayar << "\n";

    return totalBayar;
}

void tampilmenu() {
    cout << "\n======= MENU UTAMA =======\n"
         << "1. Tambah Antrian\n"
         << "2. Tampilkan Antrian\n"
         << "3. Hapus Antrian\n"
         << "4. Layani Antrian\n"
         << "5. Cari Antrian\n"
         << "6. Sorting Antrian\n"
         << "7. Edit Antrian\n"
         << "8. Riwayat Pelayanan\n"
         << "9. Keluar\n"
         << "==========================\n"
         << "Pilih menu: ";
}

int main() {
    int pilihan;
    int idCounter = 1;

    do {
        tampilmenu();
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                string nama;
                int noMeja;
                cin.ignore();

                cout << "Nama pelanggan: ";
                getline(cin, nama);
                cout << "Nomor Meja: ";
                cin >> noMeja;
                cin.ignore();

                cout << "Masukkan pesanan:\n";
                int totalBayar = inputPesanan();

                // Simpan deskripsi pesanan sebagai string ringkas
                string pesanan = "Pesanan senilai Rp " + to_string(totalBayar);

                tambahAntrian(idCounter++, noMeja, nama, pesanan);
                cout << "Antrian berhasil ditambahkan.\n";
                break;
            }
            case 2:
                tampil();
                break;
            case 3: {
                int id;
                cout << "Masukkan ID yang ingin dihapus: ";
                cin >> id;
                hapus(id);
                break;
            }
            case 4:
                layani();
                break;
            case 5: {
                string namaCari;
                cin.ignore();
                cout << "Masukkan nama yang dicari: ";
                getline(cin, namaCari);
                Node* hasil = cari(namaCari);
                if (hasil) {
                    cout << "Ditemukan: ID " << hasil->nomor
                         << ", Nama " << hasil->nama
                         << ", No Meja " << hasil->nomorMeja
                         << ", Pesanan: " << hasil->pesanan << "\n";
                } else {
                    cout << "Nama tidak ditemukan.\n";
                }
                break;
            }
            case 6:
                sorting();
                break;
            case 7: {
                int id;
                cout << "Masukkan ID yang ingin diedit: ";
                cin >> id;
                edit(id);
                break;
            }
            case 8:
                riwayat();
                break;
            case 9:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }

    } while (pilihan != 9);

    return 0;
}
