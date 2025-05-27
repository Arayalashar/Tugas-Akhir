#include <iostream>
#include <iomanip>
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

void tambahAntrean(int nomorBaru, int nomorMejaBaru, string namaBaru, string pesananBaru){
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
        tambahAntrean(nomor, nomorMeja, nama, pesanan);
        break;
        }
    case 2:
        //tampil();
        break;
    case 3:
        //hapus();
        break;
    case 4:
        //layani();
        break;
    case 5:
        //cari();
        break;
    case 6:
        //urutkan();
        break;
    case 7:
        //edit();
        break;
    case 8:
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
         << "## 8. Keluar                    ##\n"
         << "##################################\n"
         << "Pilihan Anda (1-8) : ";
}