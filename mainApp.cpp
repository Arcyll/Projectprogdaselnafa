#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "header.h"
#include "book.h"
#include "user.h"
#include "admin.h"

using namespace std;

vector<Book> books;
Admin admin("admin", "admin111");
int nextBookId = 1;

void loadData();
void saveData();
void mainMenu();
void userMode();
void adminLogin();
void adminMenu();
void addDonation(string firstName, string lastName);
void displayAvailableBooks();
void donateBook();
void displayDonationHistory();
void clearScreen();

int main() {
    loadData();  // Load data dari file
    displayHeader();
    mainMenu();
    saveData();  // Save data sebelum keluar
    
    return 0;
}

void loadData() {
    ifstream file("data_buku.txt");
    
    if (!file.is_open()) {
        cout << "\n  [INFO] File data tidak ditemukan. Membuat data baru...\n";
        // Data sample
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
        
        int id = atoi(idStr.c_str()); //mengubah string ke integer
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

void saveData() {
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

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void mainMenu() {
    while (true) {
        cout << "\n  ========== MENU UTAMA ==========\n";
        cout << "  1. User\n";
        cout << "  2. Admin\n";
        cout << "  3. Riwayat Donasi\n";
        cout << "  4. Tutup Aplikasi\n";
        cout << "  ================================\n";
        cout << "  Pilih menu: ";
        
        int choice;
        cin >> choice;
        cin.ignore();
        
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

void userMode() {
    string firstName, lastName;
    
    cout << "\n  ========== MODE USER ==========\n";
    cout << "  Silakan isi data diri Anda\n\n";
    
    cout << "  First Name: ";
    getline(cin, firstName);
    cout << "  Last Name: ";
    getline(cin, lastName);
    
    cout << "\n  Selamat datang, " << firstName << " " << lastName << "!\n";
    
    // Loop donasi buku
    while (true) {
        cout << "\n  ===== Menu User =====\n";
        cout << "  1. Tambah Donasi Buku\n";
        cout << "  2. Kembali ke Menu Utama\n";
        cout << "  =====================\n";
        cout << "  Pilih: ";
        
        int choice;
        cin >> choice;
        cin.ignore();
        
        if (choice == 1) {
            addDonation(firstName, lastName);
            saveData();  // Auto save
        } else if (choice == 2) {
            cout << "\n  Terima kasih atas kontribusi Anda!\n";
            break;
        } else {
            cout << "\n  Pilihan tidak valid!\n";
        }
    }
}

void addDonation(string firstName, string lastName) {
    string title, author;
    int year;
    
    cout << "\n  ===== Input Data Buku =====\n";
    cout << "  Judul Buku: ";
    getline(cin, title);
    cout << "  Penulis: ";
    getline(cin, author);
    cout << "  Tahun Terbit: ";
    cin >> year;
    cin.ignore();
    
    books.push_back(Book(nextBookId++, title, author, year, firstName, lastName));
    cout << "\n  Buku berhasil ditambahkan ke daftar!\n";
}

void adminLogin() {
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

void adminMenu() {
    while (true) {
        cout << "\n  ========== MENU ADMIN ==========\n";
        cout << "  1. Tambah Donasi Buku\n";
        cout << "  2. Display Semua Buku\n";
        cout << "  3. Donasi Buku\n";
        cout << "  4. Riwayat Donasi\n";
        cout << "  5. Logout\n";
        cout << "  ================================\n";
        cout << "  Pilih menu: ";
        
        int choice;
        cin >> choice;
        cin.ignore();
        
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

void displayAvailableBooks() {
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

void donateBook() {
    displayAvailableBooks();
    
    if (books.empty()) {
        return;
    }
    
    // Cek apakah ada buku yang tersedia
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
    
    int id;
    string destination;
    
    cout << "\n  Masukkan ID buku yang akan didonasikan (ketik 0 untuk kembali): ";
    cin >> id;
    cin.ignore();
    
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

void displayDonationHistory() {
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
