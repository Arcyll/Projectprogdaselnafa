#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "header.h"
#include "book.h"
#include "user.h"
#include "admin.h"

using namespace std;

class SahabatBukuApp {
private:
    vector<Book> books;
    Admin admin;
    int nextBookId;
    
    void loadData();
    void saveData();
    void clearScreen();
    void mainMenu();
    void userMode();
    void adminLogin();
    void adminMenu();
    void addDonation(string firstName, string lastName);
    void displayAvailableBooks();
    void donateBook();
    void displayDonationHistory();
    
public:
    SahabatBukuApp();
    ~SahabatBukuApp();
    
    void run();
};

int main() {
    SahabatBukuApp app;
    app.run();
    return 0;
}

SahabatBukuApp::SahabatBukuApp() : admin("admin", "admin111"), nextBookId(1) {
    loadData();
}

SahabatBukuApp::~SahabatBukuApp() {
    saveData();
}

// Run app
void SahabatBukuApp::run() {
    displayHeader();
    mainMenu();
}

// Load data dari file
void SahabatBukuApp::loadData() {
    ifstream file("data_buku.txt");
    
    if (!file.is_open()) {
        cout << "\n  [INFO] File data tidak ditemukan. Membuat data baru...\n";
        books.push_back(Book(nextBookId++, "Laskar Pelangi", "Andrea Hirata", 2005, "Budi", "Santoso"));
        books.push_back(Book(nextBookId++, "Bumi Manusia", "Pramoedya Ananta Toer", 1980, "Siti", "Aminah"));
        books.push_back(Book(nextBookId++, "Algoritma Pemrograman", "Rinaldi Munir", 2015, "Admin", "System"));
        return;
    }
    
    books.clear();
    string line;
    int maxId = 0;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string idStr, title, author, yearStr, firstName, lastName, isDonatedStr, donatedTo;
        
        getline(ss, idStr, '|');
        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, yearStr, '|');
        getline(ss, firstName, '|');
        getline(ss, lastName, '|');
        getline(ss, isDonatedStr, '|');
        getline(ss, donatedTo, '|');
        
        int id = atoi(idStr.c_str());
        int year = atoi(yearStr.c_str());
        bool isDonated = (isDonatedStr == "1");
        
        Book book(id, title, author, year, firstName, lastName);
        if (isDonated) {
            book.setDonated(donatedTo);
        }
        
        books.push_back(book);
        
        if (id > maxId) {
            maxId = id;
        }
    }
    
    file.close();
    nextBookId = maxId + 1;
}

// Save data ke file
void SahabatBukuApp::saveData() {
    if (books.size() > 1000) {
        cout << "\n  [WARNING] Data terlalu banyak (" << books.size() << " buku)!\n";
        cout << "  [WARNING] Kemungkinan ada error. Data tidak disimpan.\n";
        return;
    }
    
    ofstream file("data_buku.txt");
    
    if (!file.is_open()) {
        cout << "\n  [ERROR] Tidak dapat menyimpan data!\n";
        return;
    }
    
    for (size_t i = 0; i < books.size(); i++) {
        file << books[i].getId() << "|"
             << books[i].getTitle() << "|"
             << books[i].getAuthor() << "|"
             << books[i].getYear() << "|"
             << books[i].getDonaturFirstName() << "|"
             << books[i].getDonaturLastName() << "|"
             << (books[i].getIsDonated() ? "1" : "0") << "|"
             << books[i].getDonatedTo() << "\n";
    }
    
    file.close();
}

void SahabatBukuApp::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void SahabatBukuApp::mainMenu() {
    while (true) {
        cout << "\n  ========== MENU UTAMA ==========\n";
        cout << "  1. User\n";
        cout << "  2. Admin\n";
        cout << "  3. Riwayat Donasi\n";
        cout << "  4. Tutup Aplikasi\n";
        cout << "  ================================\n";
        cout << "  Pilih menu: ";
        
        string choiceStr;
        getline(cin, choiceStr);
        int choice = atoi(choiceStr.c_str());
        
        switch (choice) {
            case 1:
                userMode();
                break;
            case 2:
                adminLogin();
                break;
            case 3:
                displayDonationHistory();
                break;
            case 4:
                cout << "\n  ========================================\n";
                cout << "  Terima kasih telah menggunakan\n";
                cout << "  Sahabat Buku!\n";
                cout << "  Sampai jumpa...\n";
                cout << "  ========================================\n\n";
                return;
            default:
                cout << "\n  Pilihan tidak valid!\n";
        }
    }
}

void SahabatBukuApp::userMode() {
    string firstName, lastName;
    
    cout << "\n  ========== MODE USER ==========\n";
    cout << "  Silakan isi data diri Anda\n\n";
    
    cout << "  First Name: ";
    getline(cin, firstName);
    cout << "  Last Name: ";
    getline(cin, lastName);
    
    cout << "\n  Selamat datang, " << firstName << " " << lastName << "!\n";
    
    while (true) {
        cout << "\n  ===== Menu User =====\n";
        cout << "  1. Tambah Donasi Buku\n";
        cout << "  2. Kembali ke Menu Utama\n";
        cout << "  =====================\n";
        cout << "  Pilih: ";
        
        string choiceStr;
        getline(cin, choiceStr);
        int choice = atoi(choiceStr.c_str());
        
        if (choice == 1) {
            addDonation(firstName, lastName);
            saveData();
        } else if (choice == 2) {
            cout << "\n  Terima kasih atas kontribusi Anda!\n";
            break;
        } else {
            cout << "\n  Pilihan tidak valid!\n";
        }
    }
}

void SahabatBukuApp::addDonation(string firstName, string lastName) {
    string title, author, yearStr;
    int year;
    
    cout << "\n  ===== Input Data Buku =====\n";
    cout << "  Judul Buku: ";
    getline(cin, title);
    
    if (title.empty()) {
        cout << "\n  Judul tidak boleh kosong!\n";
        return;
    }
    
    cout << "  Penulis: ";
    getline(cin, author);
    
    if (author.empty()) {
        cout << "\n  Penulis tidak boleh kosong!\n";
        return;
    }
    
    cout << "  Tahun Terbit: ";
    getline(cin, yearStr);
    
    year = atoi(yearStr.c_str());
    if (year == 0 && yearStr != "0") {
        cout << "\n  Tahun tidak valid!\n";
        return;
    }
    
    books.push_back(Book(nextBookId++, title, author, year, firstName, lastName));
    cout << "\n  Buku berhasil ditambahkan ke daftar!\n";
}

void SahabatBukuApp::adminLogin() {
    string username, password;
    
    cout << "\n  ========== LOGIN ADMIN ==========\n";
    cout << "  Username: ";
    getline(cin, username);
    cout << "  Password: ";
    getline(cin, password);
    
    if (admin.authenticate(username, password)) {
        cout << "\n  Login berhasil!\n";
        adminMenu();
    } else {
        cout << "\n  Login gagal! Username atau password salah.\n";
    }
}

void SahabatBukuApp::adminMenu() {
    while (true) {
        cout << "\n  ========== MENU ADMIN ==========\n";
        cout << "  1. Tambah Donasi Buku\n";
        cout << "  2. Display Semua Buku\n";
        cout << "  3. Donasi Buku\n";
        cout << "  4. Riwayat Donasi\n";
        cout << "  5. Logout\n";
        cout << "  ================================\n";
        cout << "  Pilih menu: ";
        
        string choiceStr;
        getline(cin, choiceStr);
        int choice = atoi(choiceStr.c_str());
        
        switch (choice) {
            case 1: {
                string firstName, lastName;
                cout << "\n  ========== Tambah Donasi Buku ==========\n";
                cout << "  Nama Donatur (First Name): ";
                getline(cin, firstName);
                cout << "  Nama Donatur (Last Name): ";
                getline(cin, lastName);
                addDonation(firstName, lastName);
                saveData();
                break;
            }
            case 2:
                displayAvailableBooks();
                break;
            case 3:
                donateBook();
                saveData();
                break;
            case 4:
                displayDonationHistory();
                break;
            case 5:
                cout << "\n  Logout berhasil!\n";
                return;
            default:
                cout << "\n  Pilihan tidak valid!\n";
        }
    }
}

void SahabatBukuApp::displayAvailableBooks() {
    vector<Book> availableBooks;
    for (size_t i = 0; i < books.size(); i++) {
        if (!books[i].getIsDonated()) {
            availableBooks.push_back(books[i]);
        }
    }
    
    if (availableBooks.empty()) {
        cout << "\n  Belum ada buku yang tersedia untuk didonasikan.\n";
        return;
    }
    
    cout << "\n  ============================================ BUKU TERSEDIA UNTUK DIDONASIKAN ============================================\n";
    cout << "  | ID   | Judul                          | Penulis              | Tahun  | Donatur                   |\n";
    cout << "  ===================================================================================================================\n";
    
    for (size_t i = 0; i < availableBooks.size(); i++) {
        availableBooks[i].display();
    }
    
    cout << "  ===================================================================================================================\n";
    cout << "  Total: " << availableBooks.size() << " buku tersedia\n";
}

void SahabatBukuApp::donateBook() {
    displayAvailableBooks();
    
    if (books.empty()) {
        return;
    }
    
    bool hasAvailable = false;
    for (size_t i = 0; i < books.size(); i++) {
        if (!books[i].getIsDonated()) {
            hasAvailable = true;
            break;
        }
    }
    
    if (!hasAvailable) {
        return;
    }
    
    string idStr, destination;
    
    cout << "\n  Masukkan ID buku yang akan didonasikan (ketik 0 untuk kembali): ";
    getline(cin, idStr);
    int id = atoi(idStr.c_str());
    
    if (id == 0) return;
    
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].getId() == id && !books[i].getIsDonated()) {
            cout << "  Tujuan donasi : ";
            getline(cin, destination);
            
            books[i].setDonated(destination);
            cout << "\n  Buku \"" << books[i].getTitle() << "\" didonasikan ke " << destination << "!\n";
            return;
        }
    }
    
    cout << "\n  Buku dengan ID tersebut tidak ditemukan atau sudah didonasikan.\n";
}

void SahabatBukuApp::displayDonationHistory() {
    vector<Book> donatedBooks;
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].getIsDonated()) {
            donatedBooks.push_back(books[i]);
        }
    }
    
    if (donatedBooks.empty()) {
        cout << "\n  Belum ada buku yang didonasikan.\n";
        return;
    }
    
    cout << "\n  ================================================ RIWAYAT DONASI BUKU ================================================\n";
    cout << "  | ID   | Judul                          | Penulis              | Donatur                   | Didonasikan Ke       |\n";
    cout << "  ======================================================================================================================\n";
    
    for (size_t i = 0; i < donatedBooks.size(); i++) {
        donatedBooks[i].displayDonated();
    }
    
    cout << "  ======================================================================================================================\n";
    cout << "  Total: " << donatedBooks.size() << " buku telah didonasikan\n";
}
