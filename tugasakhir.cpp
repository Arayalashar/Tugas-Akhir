#include <iostream>
#include <iomanip>
#include <cstring>
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

bool listkosong(){
    return (awal == nullptr);
}

void tambahAntrian(int nomorBaru, int nomorMejaBaru, string namaBaru, string pesananBaru){
    Node*NB = new Node;
    NB -> nomor = nomorBaru;
    NB -> nomorMeja = nomorMejaBaru;
    NB -> nama = namaBaru;
    NB -> pesanan = pesananBaru;
    NB -> next = nullptr;
    NB -> prev = nullptr;

    if(listkosong()){
        awal = akhir = NB;
    } else if (NB -> nama <= awal -> nama){
        NB -> next = awal;
        awal -> prev = NB;
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
    cout << "Melayani ID " << temp->nomor << " atas nama " << temp->nama << "\n";
    simpanFile(temp);

    if (awal == akhir) {
        awal = akhir = nullptr;
    } else {
        awal = awal->next;
        awal->prev = nullptr;
    }
    delete temp;
}

void edit(int nomor) {
    Node* bantu = awal;
    while (bantu != nullptr) {
        if (bantu->nomor == nomor) {
            cout << "Edit data untuk ID " << nomor << ":\n";
            cout << "Nama baru: "; cin.ignore(); getline(cin, bantu->nama);
            cout << "Nomor kursi baru: "; cin >> bantu->nomorMeja;
            cin.ignore();
            cout << "Pesanan baru: "; getline(cin, bantu->pesanan);
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

Node* cari(string nama) {
    Node* bantu = awal;
    while (bantu != nullptr) {
        if (bantu->nama == nama) return bantu;
        bantu = bantu->next;
    }
    return nullptr;
}


void tampilmenu();
int main()
{
    int menu;
    tampilmenu();
    cin >> menu;
    switch (menu){
    case 1:
        {
        int nomor, nomorMeja;
        string nama, pesanan;
        cout << "Masukkan ID: "; cin >> nomor;
        cout << "Masukkan Nama Pelanggan: "; cin.ignore(); getline(cin, nama);
        cout << "Masukkan Nomor Meja: "; cin >> nomorMeja;
        cin.ignore();
        cout << "Masukkan Pesanan: "; getline(cin, pesanan);
        tambahAntrian(nomor, nomorMeja, nama, pesanan);
        break;
        }
    case 2:
        //tampil();
        break;
    case 3:
        int nomor;
        cout << "Nomor yang ingin dihapus: "; cin >> nomor;
        hapus(nomor); break;
        break;
    case 4:
        layani();
        break;
    case 5:
        //cari();
        break;
    case 6:
        //urutkan();
        break;
    case 7:
        int nomor;
        cout << "Nomor yang ingin diedit: "; cin >> nomor;
        edit(nomor); break;
        break;
    case 8:
        //riwayat();
    case 9:
        exit(0);
    default:
        break;
    }
}
void tampilmenu()
{
    cout << "##################################\n"
         << "##             MENU             ##\n"
         << "##################################\n"
         << "## 1. Tambah Antrian            ##\n"
         << "## 2. Tampilkan ANtrian         ##\n"
         << "## 3. Hapus Antrian             ##\n"
         << "## 4. Layani Pelanggan          ##\n"
         << "## 5. Cari Antriam              ##\n"
         << "## 6. Urutkan Data              ##\n"
         << "## 7. Edit Antrian              ##\n"
         << "## 8. Riwayat Pesanan           ##\n"
         << "## 9. Keluar                    ##\n"
         << "##################################\n"
         << "Pilihan Anda (1-8) : ";
}