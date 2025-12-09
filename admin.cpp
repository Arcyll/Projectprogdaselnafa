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
    cout << "\n  ========== Menu Admin ==========\n";
    cout << "  1. Tambah Buku\n";
    cout << "  2. Daftar Buku\n";
    cout << "  3. Edit Data Buku\n";
    cout << "  4. Hapus Buku (Tandai Sudah Didonasikan)\n";
    cout << "  5. Buku yang Sudah Didonasikan\n";
    cout << "  6. Logout\n";
    cout << "  ================================\n";
    cout << "  Pilih menu: ";
}
