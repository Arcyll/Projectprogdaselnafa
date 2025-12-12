#include "admin.h"
#include <iostream>
using namespace std;

Admin::Admin(string username, string password) {
    this->username = username;
    this->password = password;
}

bool Admin::authenticate(string user, string pass) {
    return (username == user && password == pass);
}

void Admin::displayMenu() {
    cout << "\n  ========== MENU ADMIN ==========\n";
    cout << "  1. Tambah Donasi Buku\n";
    cout << "  2. Display Semua Buku\n";
    cout << "  3. Donasi Buku\n";
    cout << "  4. Riwayat Donasi\n";
    cout << "  5. Keluar\n";
    cout << "  ================================\n";
    cout << "  Pilih menu: ";

}
