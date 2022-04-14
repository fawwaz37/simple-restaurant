#include <fstream>
#include <iostream>
#include <regex>

using namespace std;

void identitas() {
    system("cls");
    cout << "\n======================================================\n";
    cout << "\tSISTEM INFORMASI RESTORAN\n";
    cout << "======================================================\n";
}

class Product {
   private:
    string line;
    struct data {
        string nm;
        long int pr;
    };
    struct data get[100];
    ofstream writeFile;
    ifstream readFile;
    regex r{R"(([^,]*), (\d*.?\d*))"};
    smatch m;

   public:
    void addProduct(string productName, long int price) {
        writeFile.open("product.txt", ios::app);
        writeFile << productName + ", " << price << "\n";
        writeFile.close();
    }

    int showProduct() {
        int i = 0;
        readFile.open("product.txt");
        if (readFile.is_open()) {
            cout << "\n-------------------------------------------------\n";
            cout << "|\t\t  PRODUCT LIST  \t\t|\n";
            cout << "-------------------------------------------------\n";
            cout << "|   NO \t|  MENU\t\t\t|  HARGA\t|\n";
            cout << "-------------------------------------------------\n";
            while (getline(readFile, line)) {
                regex_match(line, m, r);
                string name{m[1]};
                long int prices{stoi(m[2])};
                cout << "|   " << i + 1 << " \t|   " + name + " \t\t|  " << prices << " \t|\n";
                i++;
            }
            cout << "-------------------------------------------------\n";
        }
        readFile.close();
        return i;
    }

    void updatePrice(string productName) {
        long int newPrice;
        int a = 0;
        bool isAction = false;

        readFile.open("product.txt");
        if (readFile.is_open()) {
            while (getline(readFile, line)) {
                regex_match(line, m, r);
                string name{m[1]};
                long int prices{stoi(m[2])};

                get[a].nm = name;
                if (productName == name) {
                    cout << "\n[INFO] Harga " + name + " Sebelumnya adalah : " << prices << endl;
                    cout << "\n[INFO] Input Harga Baru : ";
                    cin >> newPrice;
                    get[a].pr = newPrice;
                } else {
                    get[a].pr = prices;
                }
                a++;
            }
        }
        readFile.close();
        renewProduct(a);
    }

    void deleteProduct(string productName) {
        int a = 0;
        bool isAction = false;

        readFile.open("product.txt");
        if (readFile.is_open()) {
            while (getline(readFile, line)) {
                regex_match(line, m, r);
                string name{m[1]};
                long int prices{stoi(m[2])};

                if (productName == name) {
                    continue;
                }
                get[a].nm = name;
                get[a].pr = prices;
                a++;
            }
        }
        readFile.close();
        renewProduct(a);
    }

    void renewProduct(int a) {
        remove("product.txt");
        writeFile.open("product.txt", ios::app);
        for (int b = 0; b < a; b++) {
            writeFile << get[b].nm + ", " << get[b].pr << "\n";
        }
        writeFile.close();
    }
};

class Order {
   private:
    string line;
    ofstream writeFile;
    ifstream readFile;
    regex r{R"(([^,]*), (\d*.?\d*))"};
    smatch m;

   public:
    int length = 0;
    long int cash, total = 0;
    string options;
    struct pilihan {
        string productName, choice;
        long int productPrice, totalPrice;
        int qt;
    };
    struct pilihan choose[100];

    void invoice() {
        cout << "\n[INFO] Menampilkan Tagihan\n";
        cout << "\n=========================================================\n";
        cout << "|\t\t\tINVOICE\t\t\t\t|";
        cout << "\n=========================================================\n";
        cout << "\n-------------------------------------------------\n";
        cout << "|   NO \t|  MENU\t\t\t|  HARGA\t|\n";
        cout << "-------------------------------------------------\n";
        for (int a = 0; a < length; a++) {
            choose[a].totalPrice = choose[a].productPrice * choose[a].qt;
            total += choose[a].totalPrice;
            cout << "|   " << a + 1 << " \t|   " + choose[a].productName + " \t\t|  " << choose[a].totalPrice << " \t|\n";
        }
        cout << "-------------------------------------------------\n";
        cout << "|\t  TOTAL AMOUNT  \t|  " << total << "  \t|\n";
        cout << "-------------------------------------------------\n";
    }

    void chooseOrder() {
        bool stop = false;
        string options;
        int is = 0, a = 0, j = 0;

        while (stop == false) {
            cout << "\n(ORDER) Tulis Makanan/Minuman Yang Diinginkan (ex: mie) : ";
            getline(cin >> ws, choose[length].choice);
            cout << "(ORDER) Masukkan Porsi/Quantity (ex: 2) : ";
            cin >> choose[length].qt;

            cout << "\n(ORDER) Ingin Pesan Makanan/Minuman Lainnya [y/n] ? : ";
            cin >> options;

            cout << "\n=========================================================\n";

            readFile.open("product.txt");
            if (readFile.is_open()) {
                while (getline(readFile, line)) {
                    regex_match(line, m, r);
                    string name{m[1]};
                    long int prices{stoi(m[2])};

                    if (choose[length].choice == name) {
                        choose[length].productName = name;
                        choose[length].productPrice = prices;
                    };
                    a++;
                }
            }
            readFile.close();

            regex regExp("^(|y|Y)(|e|E)(|s|S)$");
            if (regex_search(options, m, regExp)) {
                stop = false;
            } else {
                stop = true;
            }
            length++;
        }
        system("cls");
        invoice();
    }
};

class Menu : public Product, Order {
   private:
    string option, productName;
    long int price;

   public:
    void adminMenu() {
    awal:
        cout << "\n---------------------------------\n";
        cout << "|\t  ADMIN MENU\t\t|\n";
        cout << "---------------------------------\n";
        cout << "|  1. ADD PRODUCT\t\t|\n|  2. SHOW PRODUCT\t\t|\n|  3. UPDATE HARGA PRODUCT\t|\n|  4. DELETE PRODUCT\t\t|\n|  5. BACK TO MAIN MENU\t\t|\n|  6. EXIT PROGRAM\t\t|\n";
        cout << "---------------------------------\n";
        cout << "\nPilih Menu Di Atas (1, 2, 3, 4, 5 atau 6)!\n> ";
        cin >> option;

        regex regExp("1|2|3|4|5|6");
        smatch m;
        if (regex_search(option, m, regExp)) {
            if (option == "1") {
                system("cls");
                cout << "\n[INFO] Kamu Memilih MENU " << option << " (ADD PRODUCT)\n";
                cout << "\n[INFO] Menampilkan List Makanan/Minuman Yang Tersedia : \n";
                showProduct();
                cout << "\n(ADDPRODUCT) Input Nama Makanan/Minuman Baru (ex: mie) : ";
                getline(cin >> ws, productName);
                cout << "\n(ADDPRODUCT) Input Harga Makanan/Minuman Baru (ex: 3000) : ";
                cin >> price;
                addProduct(productName, price);
                cout << "\n[INFO] Sukses Menambahkan Makanan/Minuman Baru : " + productName + " - " << price << "\n";
                cout << "\n[INFO] Menampilkan List Makanan/Minuman Terkini..\n";
                showProduct();
                cout << "\n======================================================\n";
                goto awal;
            } else if (option == "2") {
                system("cls");
                cout << "\n[INFO] Kamu Memilih MENU " << option << " (SHOW PRODUCT)\n";
                cout << "\n[INFO] Di Bawah ini List Makanan/Minuman Terbaru..\n";
                showProduct();
                cout << "\n======================================================\n";
                goto awal;
            } else if (option == "3") {
                system("cls");
                cout << "\n[INFO] Kamu Memilih MENU " << option << " (UPDATE HARGA PRODUCT)\n";
                cout << "\n[INFO] Menampilkan List Makanan/Minuman Terkini..\n";
                showProduct();
                cout << "\n(UPDTPRODUCT) Nama Makanan/Minuman Yang Ingin Di Update (ex: mie) : ";
                getline(cin >> ws, productName);
                updatePrice(productName);
                cout << "\n[INFO] Sukses Update Harga Makanan/Minuman : " + productName + "\n";
                cout << "\n[INFO] Menampilkan List Makanan/Minuman Terbaru..\n";
                showProduct();
                cout << "\n======================================================\n";
                goto awal;
            } else if (option == "4") {
                system("cls");
                cout << "\n[INFO] Kamu Memilih MENU " << option << " (DELETE PRODUCT)\n";
                cout << "\n[INFO] Menampilkan List Makanan/Minuman Terkini..\n";
                showProduct();
                cout << "\n(DELPRODUCT) Nama Makanan/Minuman Yang Ingin Di Hapus (ex: mie) : ";
                getline(cin >> ws, productName);
                deleteProduct(productName);
                cout << "\n[INFO] Sukses Menghapus Makanan/Minuman : " + productName + "\n";
                cout << "\n[INFO] Menampilkan List Makanan/Minuman Terbaru..\n";
                showProduct();
                cout << "\n======================================================\n";
                goto awal;
            } else if (option == "5") {
                system("cls");
                cout << "\n[INFO] Kamu Memilih MENU " << option << " (BACK TO MAIN MENU)\n";
                cout << "\n======================================================\n";
                mainMenu();
            } else if (option == "6") {
                cout << "\n======================================================\n";
                cout << "EXIT";
            }
        } else {
            cout << "\nPilihan " << option << " Tidak Ada! Silahkan Pilih/Ketik 1, 2, 3, 4, 5, atau 6!\n";
            cout << "\n======================================================\n";
            goto awal;
        }
    }

    void orderMenu() {
        cout << "\n[INFO] Menampilkan List Makanan/Minuman Yang Tersedia..\n";
        int banyak = showProduct();
        if (banyak == 0) {
            cout << "\n[INFO] Makanan/Minuman Tidak Ada! Silahkan Tambah Makanan/Minuman Pada MENU ADMIN\n";
            cout << "\n[INFO] Kembali ke MAIN MENU\n";
            cout << "\n======================================================\n";
            mainMenu();
        } else {
            chooseOrder();
        }

    bayars:
        cout << "\n=========================================================\n";
        cout << "|\t\t\tPAYMENT SUMMARY\t\t\t|";
        cout << "\n=========================================================\n";
        cout << "[PAYMENT] Masukkan CASH Yang Anda Punya \t: ";
        cin >> cash;

        if (total == 0) {
            cout << "[PAYMENT] Anda Sedang Tidak Memesan Menu Makanan/Minuman Apapun!\n";
            cout << "[PAYMENT] Silahkan pilih BUAT PESANAN Dibawah ini!\n";
            cout << "\n=========================================================\n";
        } else if (cash < total) {
            system("cls");
            cout << "[PAYMENT] CASH Tidak Cukup Untuk Membayar Pesanan!\n";
            cout << "[PAYMENT] Input CASH Lebih Dari Atau Sama Dengan Total Harga!\n";
            cout << "\n=========================================================\n";
            cout << "\n[PAYMENT] Apakah Anda Ingin Membatalkan Pesanan [Yes (y)/No (n)]? : ";
            cin >> option;

            regex regExp("^(|y|Y)(|e|E)(|s|S)$");
            smatch m;
            if (regex_search(option, m, regExp)) {
                system("cls");
                cout << "[INFO] Pesanan Dibatalkan! Kembali ke MENU UTAMA\n";
                cout << "\n=========================================================\n";
                total = 0;
                length = 0;
                mainMenu();
            } else {
                total = 0;
                invoice();
                goto bayars;
            }

        } else if (cash >= total) {
            cout << "[PAYMENT] Uang Kembalian \t\t\t: " << cash - total;
            cout << "\n\n[PAYMENT] PEMBAYARAN BERHASIL!\n";
            cout << "\n=========================================================\n";
            cout << "|\t\t\tTERIMA KASIH\t\t\t|";
            cout << "\n=========================================================\n";
            total = 0;
            length = 0;
            cout << "\n[PAYMENT] Apakah Anda Ingin Kembali ke MENU UTAMA [y/n]? : ";
            cin >> option;

            regex regExp("^(|y|Y)(|e|E)(|s|S)$");
            smatch m;
            if (regex_search(option, m, regExp)) {
                system("cls");
                cout << "[INFO] Anda Memilih Kembali ke MENU UTAMA\n";
                cout << "\n=========================================================\n";
                mainMenu();
            } else {
                cout << "\n=========================================================\n";
                cout << "\n\nEXIT";
            }
        }
    }

    void mainMenu() {
        cout << "\n---------------------------------\n";
        cout << "|\t  MAIN MENU\t\t|\n";
        cout << "---------------------------------\n";
        cout << "|  1. BUAT PESANAN\t\t|\n|  2. ADMINISTRATOR MODE\t|\n|  3. EXIT PROGRAM\t\t|\n";
        cout << "---------------------------------\n";
        cout << "\nPilih Menu Di Atas (1, 2, atau 3)!\n> ";
        cin >> option;

        regex regExp("1|2|3");
        smatch m;
        if (regex_search(option, m, regExp)) {
            if (option == "1") {
                system("cls");
                cout << "\n[INFO] Memilih MENU " << option << " (BUAT PESANAN)!\n";
                cout << "\n======================================================\n";
                orderMenu();
            } else if (option == "2") {
                system("cls");
                cout << "\n[INFO] Memilih MENU " << option << " (ADMINISTRATOR MODE), Membuka ADMIN MENU!\n";
                cout << "\n======================================================\n";
                adminMenu();
            } else if (option == "3") {
                cout << "\n======================================================\n";
                cout << "EXIT";
            }
        }
    }
};

class User {
   private:
    bool isRegistered = false, isLogin = false;
    string line;
    ifstream readFile;
    ofstream writeFile;
    regex r{R"(([^,]*), (\d*.?\d*))"};
    smatch m;

   public:
    void textAuth();
    void registers(string name, string pass) {
        readFile.open("dataUser.txt");
        if (readFile.is_open()) {
            while (getline(readFile, line)) {
                regex_match(line, m, r);
                string username{m[1]}, password{m[2]};
                if (username == name && password == pass) {
                    system("cls");
                    cout << "\n[WARN!] Username sudah terdaftar sebelumnya!\n";
                    cout << "\n======================================================\n";
                    isRegistered = true;
                    break;
                }
            }
        }
        readFile.close();
        if (!isRegistered) {
            writeFile.open("dataUser.txt", ios::app);
            writeFile << name + ", " + pass + "\n";
            system("cls");
            cout << "\n[INFO] Sukses REGISTER User Baru! Silahkan Lanjut Login (Pilih 2)!\n";
            cout << "\n======================================================\n";
            writeFile.close();
        }
    }
    void login(string name, string pass) {
        Menu menu;

        readFile.open("dataUser.txt");
        if (readFile.is_open()) {
            while (getline(readFile, line)) {
                regex_match(line, m, r);
                string username{m[1]}, password{m[2]};
                if (username == name && password == pass) {
                    system("cls");
                    cout << "\n[INFO] LOGIN Berhasil! Diarahkan ke Halaman MAIN MENU\n";
                    cout << "\n======================================================\n";
                    menu.mainMenu();
                    isLogin = true;
                    break;
                }
            }
            readFile.close();
            if (!isLogin) {
                system("cls");
                cout << "\n[WARN!] Username atau Password Salah!\n";
                cout << "\n======================================================\n";
                textAuth();
            }
        }
    }
};

void User::textAuth() {
    string option;
    string name, pass;

awal:
    cout << "\n---------------------------------\n";
    cout << "|\t  HOME MENU\t\t|\n";
    cout << "---------------------------------\n";
    cout << "|  1. REGISTER\t\t\t|\n|  2. LOG IN\t\t\t|\n|  3. EXIT PROGRAM\t\t|\n";
    cout << "---------------------------------\n";
    cout << "\nPilih Menu Di Atas (1, 2, atau 3)!\n> ";
    cin >> option;

    regex regExp("1|2|3");
    smatch m;
    if (regex_search(option, m, regExp)) {
        if (option == "1") {
            cout << "\n(REGISTER) Input Username : ";
            cin >> name;
            cout << "(REGISTER) Input Password : ";
            cin >> pass;

            registers(name, pass);
            goto awal;
        } else if (option == "2") {
            cout << "\n(LOGIN) Input Username : ";
            cin >> name;
            cout << "(LOGIN) Input Password : ";
            cin >> pass;

            login(name, pass);
        } else if (option == "3") {
            cout << "\n======================================================\n";
            cout << "\n\nEXIT";
        }
    } else {
        cout << "\nPilihan " << option << " Tidak Ada! Silahkan Pilih/Ketik 1, 2, atau 3!\n";
        cout << "\n======================================================\n";
        goto awal;
    }
}

int main() {
    User user;
    identitas();

    user.textAuth();

    return 0;
}