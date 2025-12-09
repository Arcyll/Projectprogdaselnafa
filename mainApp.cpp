#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "header.h"
#include "book.h"
#include "user.h"
#include "admin.h"

using namespace std;

// Global variables
vector<Book> books;
Admin admin("admin", "admin123");
int nextBookId = 1;

// Function prototypes
void initializeData();
void mainMenu();
void userMode();
void adminLogin();
void adminMenu();
void addBookByUser(Donasi& donasi);
void addBookByAdmin();
void displayAllBooks();
void editBook();
void deleteBook();
void displayDonatedBooks();
void clearScreen();

int main() {
    initializeData();
    displayHeader();
    mainMenu();
    
    return 0;
}

void initializeData() {
    // Sample books
    books.push_back(Book(nextBookId++, "Laskar Pelangi", "Andrea Hirata", 2005, "Budi", "Santoso"));
    books.push_back(Book(nextBookId++, "Bumi Manusia", "Pramoedya Ananta Toer", 1980, "Siti", "Aminah"));
    books.push_back(Book(nextBookId++, "Algoritma Pemrograman", "Rinaldi Munir", 2015, "Admin", "System"));
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
        cout << "\n  ========== Menu Utama ==========\n";
        cout << "  1. User - Donasi Buku\n";
        cout << "  2. Admin - Kelola Data\n";
        cout << "  3. Daftar Buku\n";
        cout << "  4. Buku yang Sudah Didonasikan\n";
        cout << "  5. Keluar\n";
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
                displayAllBooks();
                break;
            case 4:
                displayDonatedBooks();
                break;
            case 5:
                cout << "\n  Terima kasih telah menggunakan Sahabat Buku!\n";
                cout << "  Sampai jumpa lagi!\n\n";
                return;
            default:
                cout << "\n  Pilihan tidak valid!\n";
        }
    }
}

void userMode() {
    Donasi donasi;
    
    cout << "\n  ============ Donasi Buku ============\n";
    cout << "  Silakan isi data diri Anda terlebih dahulu.\n\n";
    
    string firstName, lastName;
    cout << "  First Name: ";
    getline(cin, firstName);
    cout << "  Last Name: ";
    getline(cin, lastName);
    
    donasi.setName(firstName, lastName);
    
    cout << "\n  Data diri berhasil disimpan!\n";
    cout << "  Selamat datang, " << donasi.getFullName() << "!\n";
    
    // Loop untuk menambahkan buku
    while (true) {
        cout << "\n  ===== Donasi Buku =====\n";
        cout << "  1. Donasi Buku Baru\n";
        cout << "  2. Kembali ke Menu Utama\n";
        cout << "  =======================\n";
        cout << "  Pilih: ";
        
        int choice;
        cin >> choice;
        cin.ignore();
        
        if (choice == 1) {
            addBookByUser(donasi);
        } else if (choice == 2) {
            cout << "\n  Terima kasih atas donasi Anda, " << donasi.getFullName() << "!\n";
            break;
        } else {
            cout << "\n  Pilihan tidak valid!\n";
        }
    }
}

void addBookByUser(Donasi& donasi) {
    string title, author;
    int year;
    
    cout << "\n  ----- Input Data Buku -----\n";
    cout << "  Judul Buku: ";
    getline(cin, title);
    cout << "  Penulis: ";
    getline(cin, author);
    cout << "  Tahun Terbit: ";
    cin >> year;
    cin.ignore();
    
    books.push_back(Book(nextBookId++, title, author, year, donasi.getFirstName(), donasi.getLastName()));
    cout << "\n  Buku berhasil ditambahkan!\n";
}

void adminLogin() {
    string username, password;
    
    cout << "\n  ========== Login Admin ==========\n";
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
        admin.displayMenu();
        
        int choice;
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                addBookByAdmin();
                break;
            case 2:
                displayAllBooks();
                break;
            case 3:
                editBook();
                break;
            case 4:
                deleteBook();
                break;
            case 5:
                displayDonatedBooks();
                break;
            case 6:
                cout << "\n  Logout berhasil!\n";
                return;
            default:
                cout << "\n  Pilihan tidak valid!\n";
        }
    }
}

void addBookByAdmin() {
    string title, author, firstName, lastName;
    int year;
    
    cout << "\n  ========== Tambah Buku ==========\n";
    cout << "  Judul Buku: ";
    getline(cin, title);
    cout << "  Penulis: ";
    getline(cin, author);
    cout << "  Tahun Terbit: ";
    cin >> year;
    cin.ignore();
    cout << "  Nama Donatur (First Name): ";
    getline(cin, firstName);
    cout << "  Nama Donatur (Last Name): ";
    getline(cin, lastName);
    
    books.push_back(Book(nextBookId++, title, author, year, firstName, lastName));
    cout << "\n  Buku berhasil ditambahkan!\n";
}

void displayAllBooks() {
    // Filter hanya buku yang belum didonasikan
    vector<Book> availableBooks;
    for (size_t i = 0; i < books.size(); i++) {
        if (!books[i].getIsDonated()) {
            availableBooks.push_back(books[i]);
        }
    }
    
    if (availableBooks.empty()) {
        cout << "\n  Belum ada buku yang tersedia.\n";
        return;
    }
    
    cout << "\n  ============================================ Daftar Buku Tersedia ============================================\n";
    cout << "  | ID   | Judul                          | Penulis              | Tahun  | Donatur                   |\n";
    cout << "  ===============================================================================================================\n";
    
    for (size_t i = 0; i < availableBooks.size(); i++) {
        availableBooks[i].display();
    }
    
    cout << "  ===============================================================================================================\n";
    cout << "  Total: " << availableBooks.size() << " buku tersedia\n";
}

void editBook() {
    if (books.empty()) {
        cout << "\n  Belum ada buku yang tersedia.\n";
        return;
    }
    
    // Tampilkan semua buku (termasuk yang sudah didonasikan)
    cout << "\n  ============================================ Semua Buku ============================================\n";
    cout << "  | ID   | Judul                          | Penulis              | Tahun  | Donatur                   |\n";
    cout << "  ====================================================================================================\n";
    
    for (size_t i = 0; i < books.size(); i++) {
        if (!books[i].getIsDonated()) {
            books[i].display();
        }
    }
    cout << "  ====================================================================================================\n";
    
    int id;
    cout << "\n  Masukkan ID buku yang akan diedit: ";
    cin >> id;
    cin.ignore();
    
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].getId() == id && !books[i].getIsDonated()) {
            cout << "\n  Data buku saat ini:\n";
            cout << "  Judul: " << books[i].getTitle() << endl;
            cout << "  Penulis: " << books[i].getAuthor() << endl;
            cout << "  Tahun: " << books[i].getYear() << endl;
            cout << "  Donatur: " << books[i].getDonaturFullName() << endl;
            
            cout << "\n  Fitur edit belum diimplementasikan sepenuhnya.\n";
            cout << "  Untuk saat ini, silakan hapus dan tambah ulang.\n";
            return;
        }
    }
    
    cout << "\n  Buku dengan ID tersebut tidak ditemukan.\n";
}

void deleteBook() {
    if (books.empty()) {
        cout << "\n  Belum ada buku yang tersedia.\n";
        return;
    }
    
    displayAllBooks();
    
    int id;
    string recipient;
    
    cout << "\n  Masukkan ID buku yang akan ditandai sudah didonasikan: ";
    cin >> id;
    cin.ignore();
    
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].getId() == id && !books[i].getIsDonated()) {
            cout << "  Didonasikan kepada siapa/kemana? ";
            getline(cin, recipient);
            
            books[i].setDonated(recipient);
            cout << "\n  Buku \"" << books[i].getTitle() << "\" telah ditandai sudah didonasikan ke " << recipient << ".\n";
            return;
        }
    }
    
    cout << "\n  Buku dengan ID tersebut tidak ditemukan atau sudah didonasikan.\n";
}

void displayDonatedBooks() {
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
    
    cout << "\n  ================================================ Buku yang Sudah Didonasikan ================================================\n";
    cout << "  | ID   | Judul                          | Penulis              | Donatur                   | Didonasikan Ke       |\n";
    cout << "  ==================================================================================================================================\n";
    
    for (size_t i = 0; i < donatedBooks.size(); i++) {
        donatedBooks[i].displayDonated();
    }
    
    cout << "  ==================================================================================================================================\n";
    cout << "  Total: " << donatedBooks.size() << " buku telah didonasikan\n";
}
