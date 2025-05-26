#include <iostream>
#include <iomanip>
using namespace std;

void tampilmenu();
int main()
{
    int menu;
    tampilmenu();
    cin >> menu;
    cout << "hai";
    switch (menu)
    {
    case 1:
        tambah();
        break;
    case 2:
        tampil();
        break;
    case 3:
        hapus();
        break;
    case 4:
        layani();
        break;
    case 5:
        cari();
        break;
    case 6:
        urutkan();
        break;
    case 7:
        edit();
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