#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
using namespace std;

struct Node
{
    int nomor;
    int nomorMeja;
    string nama;
    string pesanan;
    Node *next;
    Node *prev;
};

Node *awal = nullptr;
Node *akhir = nullptr;

bool listkosong()
{
    return (awal == nullptr);
}

void tambahAntrian(int nomorBaru, int nomorMejaBaru, string namaBaru, string pesananBaru)
{
    Node *NB = new Node;
    NB->nomor = nomorBaru;
    NB->nomorMeja = nomorMejaBaru;
    NB->nama = namaBaru;
    NB->pesanan = pesananBaru;
    NB->next = nullptr;
    NB->prev = nullptr;

    if (listkosong())
    {
        awal = akhir = NB;
    }
    else if (NB->nama <= awal->nama)
    {
        NB->next = awal;
        awal->prev = NB;
        awal = NB;
    }
    else
    {
        Node *bantu = awal;
        while (bantu->next != nullptr && NB->nama > bantu->next->nama)
        {
            bantu = bantu->next;
        }
        NB->next = bantu->next;
        if (bantu->next != nullptr)
        {
            bantu->next->prev = NB;
        }
        NB->prev = bantu;
        bantu->next = NB;

        if (NB->next == nullptr)
        {
            akhir = NB;
        }
    }
}

void simpanFile(Node *node)
{
    FILE *file = fopen("riwayat.txt", "a");
    if (file == nullptr)
    {
        cout << "Gagal membuka file riwayat.\n";
        return;
    }
    fprintf(file, "%d,%s,%d,%s\n", node->nomor, nama.c_str(), node->nomorMeja, pesanan.c_str());
    fclose(file);
}

void layani()
{
    if (listkosong())
    {
        cout << "Tidak ada antrian.\n";
        return;
    }
    Node *temp = awal;
    cout << "Melayani ID " << temp->nomor << " atas nama " << temp->nama << "\n";
    simpanFile(temp);

    if (awal == akhir)
    {
        awal = akhir = nullptr;
    }
    else
    {
        awal = awal->next;
        awal->prev = nullptr;
    }
    delete temp;

    cout << "Pelanggan dengan ID " << temp->nomor << " telah dilayani.\n";
}

void edit(int nomor)
{
    Node *bantu = awal;
    while (bantu != nullptr)
    {
        if (bantu->nomor == nomor)
        {
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

void hapus(int nomor)
{
    Node *bantu = awal;
    while (bantu != nullptr && bantu->nomor != nomor)
    {
        bantu = bantu->next;
    }
    if (bantu == nullptr)
    {
        cout << "ID tidak ditemukan.\n";
        return;
    }

    if (bantu == awal && bantu == akhir)
    {
        awal = akhir = nullptr;
    }
    else if (bantu == awal)
    {
        awal = awal->next;
        awal->prev = nullptr;
    }
    else if (bantu == akhir)
    {
        akhir = akhir->prev;
        akhir->next = nullptr;
    }
    else
    {
        bantu->prev->next = bantu->next;
        bantu->next->prev = bantu->prev;
    }

    delete bantu;
    cout << "Data berhasil dihapus.\n";
}

void tampil()
{
    cout << "\n==== DAFTAR ANTRIAN ====\n";

    if (listkosong())
    {
        cout << "Antrian kosong!\n";
    }
    else
    {
        cout << left << setw(5) << "ID"
             << setw(20) << "Nama"
             << setw(10) << "No.Meja"
             << setw(25) << "Pesanan" << endl;
        cout << string(60, '-') << endl;

        Node *bantu = awal;
        while (bantu != nullptr)
        {
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

void menumakanan()
{
    cout << "\n";
    cout << "===============================================\n";
    cout << "           MENU RESTORAN GACOAN              \n";
    cout << "===============================================\n";
    cout << "| No |        Nama Menu        |   Harga    |\n";
    cout << "===============================================\n";

    // Mie
    cout << "|    |      ** MIE GACOAN **   |            |\n";
    cout << "| 1  | Mie Gacoan Level 0      | Rp 15.000  |\n";
    cout << "| 2  | Mie Gacoan Level 1      | Rp 15.000  |\n";
    cout << "| 3  | Mie Gacoan Level 2      | Rp 15.000  |\n";
    cout << "| 4  | Mie Gacoan Level 3      | Rp 15.000  |\n";
    cout << "| 5  | Mie Gacoan Level 4      | Rp 15.000  |\n";
    cout << "| 6  | Mie Gacoan Level 5      | Rp 15.000  |\n";
    cout << "-----------------------------------------------\n";

    // Dimsum
    cout << "|    |      ** DIMSUM **       |            |\n";
    cout << "| 7  | Dimsum Ayam (4 pcs)     | Rp 12.000  |\n";
    cout << "| 8  | Dimsum Udang (4 pcs)    | Rp 15.000  |\n";
    cout << "| 9  | Dimsum Kulit (4 pcs)    | Rp 10.000  |\n";
    cout << "-----------------------------------------------\n";

    // Tahu & Tempe
    cout << "|    |    ** TAHU & TEMPE **   |            |\n";
    cout << "| 10 | Tahu Gejrot              | Rp 8.000   |\n";
    cout << "| 11 | Tahu Crispy              | Rp 10.000  |\n";
    cout << "| 12 | Tempe Mendoan            | Rp 8.000   |\n";
    cout << "-----------------------------------------------\n";

    // Minuman
    cout << "|    |      ** MINUMAN **      |            |\n";
    cout << "| 13 | Es Teh Manis             | Rp 5.000   |\n";
    cout << "| 14 | Es Jeruk                 | Rp 7.000   |\n";
    cout << "| 15 | Es Cappuccino            | Rp 12.000  |\n";
    cout << "| 16 | Air Mineral              | Rp 3.000   |\n";
    cout << "-----------------------------------------------\n";

    // Snack
    cout << "|    |      ** SNACK **        |            |\n";
    cout << "| 17 | Kerupuk                  | Rp 2.000   |\n";
    cout << "| 18 | Rempeyek                 | Rp 3.000   |\n";
    cout << "| 19 | Emping                   | Rp 4.000   |\n";
    cout << "===============================================\n";
    cout << "         * Level pedas: 0 = Tidak Pedas *    \n";
    cout << "         * Level pedas: 1-5 = Makin Pedas *  \n";
    cout << "===============================================\n";
}

void sorting()
{
    if (listkosong() || awal->next == nullptr)
    {
        cout << "\nAntrian kosong atau hanya ada 1 data, tidak perlu diurutkan!\n";
        cout << "Tekan Enter untuk kembali ke menu...";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "\n==== SORTING ANTRIAN ====\n";
    cout << "Pilih kriteria sorting:\n";
    cout << "1. Berdasarkan Nama (A-Z)\n";
    cout << "2. Berdasarkan ID (Ascending)\n";
    cout << "3. Berdasarkan Nomor Meja (Ascending)\n";
    cout << "Pilihan Anda: ";

    int pilihan;
    cin >> pilihan;

    // Bubble sort untuk doubly linked list
    bool tukar;
    Node *current;
    Node *last = nullptr;

    do
    {
        tukar = false;
        current = awal;

        while (current->next != last)
        {
            bool harus_tukar = false;

            switch (pilihan)
            {
            case 1: // Sort berdasarkan nama
                if (current->nama > current->next->nama)
                {
                    harus_tukar = true;
                }
                break;
            case 2: // Sort berdasarkan ID
                if (current->nomor > current->next->nomor)
                {
                    harus_tukar = true;
                }
                break;
            case 3: // Sort berdasarkan nomor meja
                if (current->nomorMeja > current->next->nomorMeja)
                {
                    harus_tukar = true;
                }
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                return;
            }

            if (harus_tukar)
            {
                // Tukar data
                int tempNomor = current->nomor;
                int tempNomorMeja = current->nomorMeja;
                string tempNama = current->nama;
                string tempPesanan = current->pesanan;

                current->nomor = current->next->nomor;
                current->nomorMeja = current->next->nomorMeja;
                current->nama = current->next->nama;
                current->pesanan = current->next->pesanan;

                current->next->nomor = tempNomor;
                current->next->nomorMeja = tempNomorMeja;
                current->next->nama = tempNama;
                current->next->pesanan = tempPesanan;

                tukar = true;
            }
            current = current->next;
        }
        last = current;
    } while (tukar);

    cout << "Sorting berhasil!\n";
    cout << "Tekan Enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

Node *cari(string nama)
{
    Node *bantu = awal;
    while (bantu != nullptr)
    {
        if (bantu->nama == nama)
            return bantu;
        bantu = bantu->next;
    }
    return nullptr;
}

void riwayat()
{
    FILE *file = fopen("riwayat.txt", "r");
    if (file == nullptr)
    {
        cout << "Belum ada riwayat.\n";
        return;
    }

    char line[256];
    cout << "\n=== Riwayat Antrian ===\n";
    cout << "ID\tNama\t\tKursi\tPesanan\n";
    while (fgets(line, sizeof(line), file))
    {
        int nomor, nomorMeja;
        char nama[100], pesanan[100];
        sscanf(line, "%d,%[^,],%d,%[^\n]", &nomor, nama, &nomorMeja, pesanan);
        cout << nomor << "\t" << nama << "\t\t" << nomorMeja << "\t" << pesanan << "\n";
    }
    fclose(file);
}

void cariNomor(int nomor)
{
    Node *bantu = awal;
    bool ketemu = false;
    while (bantu != nullptr)
    {
        if (bantu->nomor == nomor)
        {
            cout << "Ditemukan: ID " << bantu->nomor << ", Nama " << bantu->nama << ", Pesanan: " << bantu->pesanan << endl;
            ketemu = true;
        }
        bantu = bantu->next;
    }
    if (!ketemu)
        cout << "Nomor kursi " << nomor << " tidak ditemukan.\n";
}

void tampilmenu()
{
    system("cls");
    cout << "##################################\n"
         << "##   SISTEM ANTRIAN RESTAURAN   ##\n"
         << "##################################\n"
         << "## 1. Tambah Antrian            ##\n"
         << "## 2. Tampilkan Antrian         ##\n"
         << "## 3. Hapus Antrian             ##\n"
         << "## 4. Layani Pelanggan          ##\n"
         << "## 5. Cari Antrian              ##\n"
         << "## 6. Urutkan Data              ##\n"
         << "## 7. Edit Antrian              ##\n"
         << "## 8. Riwayat Pesanan           ##\n"
         << "## 9. Keluar                    ##\n"
         << "##################################\n"
         << "Pilihan Anda (1-9) : ";
}

int main()
{
    int menu;
    int nomor, nomorMeja;
    string nama, pesanan;

    do
    {
        tampilmenu();
        cin >> menu;
        switch (menu)
        {
        case 1:
        {
            menumakanan();
            cout << "Masukkan ID: ";
            cin >> nomor;
            cout << "Masukkan Nama Pelanggan: ";
            cin.ignore();
            getline(cin, nama);
            cout << "Masukkan Nomor Meja: ";
            cin >> nomorMeja;
            cin.ignore();
            cout << "Masukkan Pesanan: ";
            getline(cin, pesanan);
            tambahAntrian(nomor, nomorMeja, nama, pesanan);
            system("pause");
            break;
        }
        case 2:
            tampil();
            break;
        case 3:
            cout << "Nomor yang ingin dihapus: ";
            cin >> nomor;
            hapus(nomor);
            system("pause");
            break;
        case 4:
            layani();
            system("pause");
            break;
        case 5:
            int nomor;
            cout << "Masukkan nomor : ";
            cin >> nomor;
            cariNomor(nomor);
            system("pause");
            break;
        case 6:
            sorting();
            break;
        case 7:
            cout << "Nomor yang ingin diedit: ";
            cin >> nomor;
            edit(nomor);
            system("pause");
            break;
        case 8:
            riwayat();
            break;
        case 9:
            exit(0);
        default:
            break;
        }
    } while (menu != 10);
    return 0;
}
