#include <fstream>
#include <iostream>
#include <regex>

using namespace std;

ifstream readfile;
ofstream writefile;

// https://regex101.com/r/ljeHoF/1
regex re{R"(([^,]*), ([^,]*))"};
smatch m;
bool awalMenu = false;

class Identitas {
   public:
    Identitas(string nama1, string nama2) {
        system("cls");
        cout << "\n=================================================\n";
        cout << "|\tSISTEM INFORMASI RESTORAN\t\t|\n";
        cout << "|\t\t\t\t\t\t|\n|\tOLEH " << nama1 << " (11111111111)\t\t\t|\n";
        cout << "|\t\t\t\t\t\t|\n|\tDAN " << nama2 << " (22222222222)\t\t|\n";
    }

    Identitas(int kel) {
        cout << "|\t\t\t\t\t\t|\n|\tKELOMPOK " << kel << "\t\t\t\t|\n";
        cout << "=================================================\n";
    }
};

class Makanan {
   public:
    string nama, line;
    long int harga;
    struct pilihan {
        string productName, choice;
        long int productPrice, totalPrice;
        int qt;
    };
    struct pilihan choose[100];

    Makanan *next, *head, *tail, *temp, *now, *del, *show;
    Makanan() {
        head = NULL;
        tail = NULL;
    }

    void awal() {
        int i = 0;
        readfile.open("product.txt");
        while (getline(readfile, line)) {
            regex_match(line, m, re);
            string nama{m[1]};
            long int harga{stoi(m[2])};  // stoi => String TO Integer
            this->addMakanan(nama, harga, true);
            i++;
        }
        readfile.close();
    }

    void addMakanan(string nama, long int harga, bool notNew) {
        temp = new Makanan();
        temp->nama = nama;
        temp->harga = harga;
        temp->next = NULL;

        if (notNew == false) {
            writefile.open("product.txt", ios::app);
            writefile << temp->nama << ", " << temp->harga << "\n";
            writefile.close();
        }

        if (head == NULL) {
            head = temp;
            tail = temp;
        } else {
            tail->next = temp;
            tail = tail->next;
        }
    }

    void updateHargaMakanan(string nama) {
        long int hargaBaru;
        temp = head;
        bool isUpdate = false;
        while (temp != NULL) {
            if (temp->nama == nama) {
                cout << "\n[INFO] Harga " + nama + " Sebelumnya adalah : " << temp->harga << endl;
                cout << "\n[UPDATE PRODUCT] Input Harga Baru : ";
                cin >> hargaBaru;
                temp->harga = hargaBaru;
                isUpdate = true;
            }
            temp = temp->next;
        }
        if (isUpdate) {
            renewMakanan();
        }
    }

    void renewMakanan() {
        temp = head;
        remove("product.txt");
        writefile.open("product.txt", ios::app);
        while (temp != NULL) {
            writefile << temp->nama + ", " << temp->harga << "\n";
            temp = temp->next;
        }
        writefile.close();
    }

    void deleteMakanan(string nama) {
        int index = 0;
        now = head;
        while (now != NULL) {
            if (index == 0 && now->nama == nama) {
                del = head;
                head = head->next;
                delete del;
            } else if (index != 0 && now->nama == nama) {
                temp->next = now->next;
            } else {
                temp = now;
            }
            now = now->next;
            index++;
        }
        renewMakanan();
    }

    int showMakanan() {
        int i = 0;
        readfile.open("product.txt");
        show = head;
        cout << "\n-------------------------------------------------\n";
        cout << "|\t\t  PRODUCT LIST  \t\t|\n";
        cout << "-------------------------------------------------\n";
        cout << "|   NO \t|  MENU\t\t\t|  HARGA\t|\n";
        cout << "-------------------------------------------------\n";
        while (show != NULL) {
            cout << "|   " << i + 1 << " \t|   " + show->nama + " \t\t|  " << show->harga << " \t|\n";
            i++;
            show = show->next;
        }
        cout << "-------------------------------------------------\n";
        readfile.close();
        return i;
    }
};

class Counts {
   public:
    int value = 0;

    void operator++() {
        ++value;
    }

    void display() {
        cout << "\n===================================================\n";
        cout << "|\t Anda Sudah Salah Login Sebanyak : " << value << "\t  |";
        cout << "\n===================================================\n";
    }
};

class Menu : public Makanan {
   public:
    int pilihan, length = 0;
    string namaProduk, pilihanUser;
    long int total = 0, harga, cash;
    Makanan mk;
    bool isStop;

    void mainMenu() {
    awal:
        if (awalMenu) {
            this->awal();
            awalMenu = false;
        }
        cout << "\n=========================================\n";
        cout << "|\t\tMAIN MENU\t\t|";
        cout << "\n=========================================\n";
        cout << "|  1. | \tBuat Pesanan\t\t|\n|  2. | \tAdmin Mode\t\t|\n|  3. | \tExit Program\t\t|";
        cout << "\n=========================================\n";
        cout << "\nPilihan Mu\n> ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                this->menuOrder();
                break;

            case 2:
                system("cls");
                cout << "\n=================================================================\n";
                cout << "|\t[INFO] Anda Memilih 2! Diarahkan ke Menu Admin\t\t|";
                cout << "\n=================================================================\n";
                this->menuAdmin();
                break;

            case 3:
                cout << "\n\nEXIT PROGRAM...";
                break;

            default:
                cout << "\nPilihan " << pilihan << " Tidak Ada! Silahkan Pilih/Ketik 1, 2, 3, 4, 5, atau 6!\n";
                cout << "\n======================================================\n";
                goto awal;
                break;
        }
    }

    void menuOrder() {
    awal:
        system("cls");
        cout << "\n=================================================\n";
        cout << "|\t\tMEMBUAT PESANAN\t\t\t|";
        cout << "\n=================================================\n";
        cout << "\n=================================================\n";
        cout << "|\tMENAMPILKAN PRODUK YANG TERSEDIA...\t|";
        cout << "\n=================================================\n";
        int banyak = this->showMakanan();

        if (banyak == 0) {
            cout << "\n=====================================================================\n";
            cout << "|  MENU MAKANAN TIDAK ADA! SILAHKAN TAMBAH MAKANAN PADA ADMIN MENU  |";
            cout << "\n=====================================================================\n";
            this->mainMenu();
        } else {
            this->pilihProduk();
        bayars:
            cout << "\n=================================================\n";
            cout << "|\t\tPAYMENT SUMMARY\t\t\t|";
            cout << "\n=================================================\n";
            cout << "[PAYMENT] Masukkan CASH Yang Anda Punya \t: ";
            cin >> cash;

            if (total == 0) {
                cout << "\n=========================================================\n";
                cout << "[PAYMENT] Anda Sedang Tidak Memesan Menu Makanan/Minuman Apapun!\n";
                cout << "[PAYMENT] Silahkan pilih BUAT PESANAN pada Admin Menu";
                cout << "\n=========================================================\n";
                this->mainMenu();
            } else if (cash < total) {
                cout << "\n=========================================================================\n";
                cout << "|\t\t[INFO] CASH Tidak Cukup Untuk Membayar Pesanan!\t\t|";
                cout << "\n=========================================================================\n";

                cout << "\n=========================================================================\n";
                cout << "|\t[INFO] Input CASH Lebih Dari Atau Sama Dengan Total Harga!\t|";
                cout << "\n=========================================================================\n";
                cout << "\n[PAYMENT] Apakah Anda Ingin Membatalkan Pesanan [Yes (y)/No (n)]? : ";
                cin >> pilihanUser;

                regex regExp("^(|y|Y)(|e|E)(|s|S)$");
                smatch m;
                if (regex_search(pilihanUser, m, regExp)) {
                    system("cls");
                    cout << "\n=======================================================\n";
                    cout << "|  [INFO] Pesanan Dibatalkan! Kembali ke MENU UTAMA   |";
                    cout << "\n=======================================================\n";
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
                cin >> pilihanUser;

                regex regExp("^(|y|Y)(|e|E)(|s|S)$");
                smatch m;
                if (regex_search(pilihanUser, m, regExp)) {
                    system("cls");
                    cout << "\n=======================================================\n";
                    cout << "|  [INFO] Pesanan Dibatalkan! Kembali ke MENU UTAMA   |";
                    cout << "\n=======================================================\n";
                    mainMenu();
                } else {
                    cout << "\n=========================================================\n";
                    cout << "\n\nEXIT PROGRAM...";
                }
            }
        }
    }

    void menuAdmin() {
    awal:
        // this->awal();
        cout << "\n=========================================\n";
        cout << "|\t\tADMIN MENU\t\t|";
        cout << "\n=========================================\n";
        cout << "| 1. | \t\tShow Product\t\t|\n| 2. | \t\tAdd Product\t\t|\n| 3. | \t\tUpdate Harga\t\t|\n| 4. | \t\tDelete Produk\t\t|\n| 5. | \t\tMain Menu\t\t|";
        cout << "\n=========================================\n";
        cout << "\nPilihan mu : \n> ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                system("cls");
                cout << "\n=================================================================\n";
                cout << "|\t[INFO] Memilih Pilihan 1! Menampilkan Product/Makanan\t|";
                cout << "\n=================================================================\n";
                this->showMakanan();
                goto awal;
                break;

            case 2:
                system("cls");
                cout << "\n=================================================================\n";
                cout << "|\t[INFO] Memilih Pilihan 2! Menampilkan Product/Makanan\t|";
                cout << "\n=================================================================\n";
                this->showMakanan();
                cout << "\n[ADD PRODUCT] Input Nama Makanan/Minuman Baru (ex: mie) : ";
                getline(cin >> ws, namaProduk);
                cout << "\n[ADD PRODUCT] Input Harga Makanan/Minuman Baru (ex: 3000) : ";
                cin >> harga;
                this->addMakanan(namaProduk, harga, false);
                cout << "\n[ADD PRODUCT] Menampilkan List Makanan/Minuman Terkini..\n";
                this->showMakanan();
                goto awal;
                break;

            case 3:
                system("cls");
                cout << "\n=================================================================\n";
                cout << "|\t[INFO] Memilih Pilihan 3! Menampilkan Product/Makanan\t|";
                cout << "\n=================================================================\n";
                this->showMakanan();
                cout << "\n[UPDATE PRODUCT] Input Nama Makanan/Minuman Yang Akan di Update Harganya (ex: mie) : ";
                getline(cin >> ws, namaProduk);
                this->updateHargaMakanan(namaProduk);
                cout << "\n[UPDATE PRODUCT] Menampilkan List Makanan/Minuman Terbaru..\n";
                this->showMakanan();
                goto awal;
                break;

            case 4:
                system("cls");
                cout << "\n=================================================================\n";
                cout << "|\t[INFO] Memilih Pilihan 4! Menampilkan Product/Makanan\t|";
                cout << "\n=================================================================\n";
                this->showMakanan();
                cout << "\n[DELETE PRODUCT] Input Nama Makanan/Minuman Yang Akan di Delete / Hapus (ex: mie) : ";
                getline(cin >> ws, namaProduk);
                this->deleteMakanan(namaProduk);
                cout << "\n[DELETE PRODUCT] Menampilkan List Makanan/Minuman Terbaru..\n";
                this->showMakanan();
                goto awal;
                break;

            case 5:
                system("cls");
                cout << "\n=================================================================\n";
                cout << "|\t[INFO] Memilih Pilihan 5! Menampilkan Main Menu\t\t|";
                cout << "\n=================================================================\n";
                this->mainMenu();
                break;

            default:
                cout << "\nPilihan " << pilihan << " Tidak Ada! Silahkan Pilih/Ketik 1, 2, 3, 4, 5, atau 6!\n";
                cout << "\n======================================================\n";
                goto awal;
                break;
        }
    }

    void invoice() {
        system("cls");
        cout << "\n=================================================\n";
        cout << "|\t    [INFO] Menampilkan Tagihan    \t|";
        cout << "\n=================================================\n";
        cout << "\n=================================================\n";
        cout << "|\t\t    INVOICE\t\t\t|";
        cout << "\n=================================================\n";
        cout << "\n-------------------------------------------------\n";
        cout << "|   NO \t|  MENU\t\t\t|  HARGA\t|\n";
        cout << "-------------------------------------------------\n";
        for (int a = 0; a < this->length; a++) {
            this->choose[a].totalPrice = this->choose[a].productPrice * this->choose[a].qt;
            total += this->choose[a].totalPrice;
            cout << "|   " << a + 1 << " \t|   " + this->choose[a].productName + " \t\t|  " << this->choose[a].totalPrice << " \t|\n";
        }
        cout << "-------------------------------------------------\n";
        cout << "|\t  TOTAL AMOUNT  \t|  " << total << "  \t|\n";
        cout << "-------------------------------------------------\n";
    }

    void pilihProduk() {
        this->isStop = false;
        while (this->isStop == false) {
            cout << "\n[ORDER] Tulis Makanan/Minuman Yang Diinginkan (ex: mie) : ";
            getline(cin >> ws, this->choose[length].choice);
            cout << "[ORDER] Masukkan Porsi/Quantity (ex: 2) : ";
            cin >> this->choose[length].qt;

            cout << "\n[ORDER] Ingin Pesan Makanan/Minuman Lainnya [y/n] ? : ";
            cin >> pilihanUser;

            readfile.open("product.txt");
            while (getline(readfile, line)) {
                regex_match(line, m, re);
                string name{m[1]};
                long int prices{stoi(m[2])};

                if (this->choose[length].choice == name) {
                    this->choose[length].productName = name;
                    this->choose[length].productPrice = prices;
                };
            }
            readfile.close();

            regex regExp("^(|y|Y)(|e|E)(|s|S)$");
            if (regex_search(pilihanUser, m, regExp)) {
                this->isStop = false;
            } else {
                this->isStop = true;
            }
            length++;
        }
        system("cls");
        this->invoice();
    }
};

class User {
   public:
    string name, pass, pilihanUser, line;
    int hasil, length = 0, total = 0;
    bool isStop;

    void registers() {
        bool isRegistered = false;

        readfile.open("dataUser.txt");
        while (getline(readfile, line)) {
            regex_match(line, m, re);
            string username{m[1]}, password{m[2]};
            if (username == name && password == pass) {
                system("cls");
                cout << "\n===================================================\n";
                cout << "|\t\t\t\t\t\t  |\n|   [WARN!] Username sudah terdaftar sebelumnya!  |\n";
                cout << "|\t\t\t\t\t\t  |\n===================================================\n";
                isRegistered = true;
                break;
            }
        }
        readfile.close();

        if (!isRegistered) {
            writefile.open("dataUser.txt", ios::app);
            writefile << name + ", " + pass + "\n";
            system("cls");
            cout << "\n==========================================================================\n";
            cout << "|\t\t\t\t\t\t\t\t\t |";
            cout << "\n|   [INFO] Sukses REGISTER User Baru! Silahkan Lanjut Login (Pilih 2)!   |\n";
            cout << "|\t\t\t\t\t\t\t\t\t |";
            cout << "\n==========================================================================\n";
            writefile.close();
        }
    }

    int login() {
        bool isLogin = false;
        readfile.open("dataUser.txt");
        while (getline(readfile, line)) {
            regex_match(line, m, re);
            string username{m[1]}, password{m[2]};
            if (username == name && pass == password) {
                system("cls");
                cout << "\n==================================================================\n";
                cout << "|\t\t\t\t\t\t\t\t |";
                cout << "\n|   [INFO] LOGIN USER Berhasil! Diarahkan ke Halaman MAIN MENU!\t |\n";
                cout << "|\t\t\t\t\t\t\t\t |";
                cout << "\n==================================================================\n";
                isLogin = true;
                break;
            }
        }
        readfile.close();
        if (!isLogin) {
            system("cls");
            cout << "\n===================================================\n";
            cout << "|\t\t\t\t\t\t  |\n|   [WARN!] Username & Password Tidak Terdaftar!  |\n";
            cout << "|\t\t\t\t\t\t  |\n===================================================\n";
        }
        this->hasil = isLogin == true ? 1 : 0;
        return this->hasil;
    }
};

int main() {
    int option, hasilLogin;
    User user;
    Menu menu;
    Counts cou;

    Identitas id = Identitas("ASEP", "BAMBANG");
    Identitas id2 = Identitas(1);

awal:
    cout << "\n---------------------------------\n";
    cout << "|\t  HOME MENU\t\t|\n";
    cout << "---------------------------------\n";
    cout << "|  1. REGISTER\t\t\t|\n|  2. LOG IN\t\t\t|\n|  3. EXIT PROGRAM\t\t|\n";
    cout << "---------------------------------\n";
    cout << "\nPilih Menu Di Atas (1, 2, atau 3)!\n> ";
    cin >> option;

    switch (option) {
        case 1:
            cout << "\n=========================================\n";
            cout << "|\t Memilih 1 : REGISTER\t\t|\n";
            cout << "=========================================\n";
            cout << "\n[REGISTER] Input Username : ";
            cin >> user.name;
            cout << "[REGISTER] Input Password : ";
            cin >> user.pass;

            user.registers();
            goto awal;
            break;

        case 2:
            cout << "\n=========================================\n";
            cout << "|\t Memilih 2 : LOGIN\t\t|\n";
            cout << "=========================================\n";
            cout << "\n[LOGIN] Input Username : ";
            cin >> user.name;
            cout << "[LOGIN] Input Password : ";
            cin >> user.pass;

            hasilLogin = user.login();
            if (hasilLogin == 1) {
                awalMenu = true;
                menu.mainMenu();
            } else {
                ++cou;
                cou.display();
                if (cou.value >= 5) {
                    cout << "\nTERLALU BANYAK PERCOBAAN LOGIN, PROGRAM BERHENTI...";
                } else {
                    goto awal;
                }
            }
            break;

        case 3:
            cout << "\n=========================================\n";
            cout << "|\t Memilih 3 : EXIT\t\t|\n";
            cout << "=========================================\n";
            cout << "\nPROGRAM BERHENTI...";
            break;

        default:
            system("cls");
            cout << "\n=========================================\n";
            cout << "|\t Memilih " << option << " : NOT FOUND\t\t|\n";
            cout << "=========================================\n";
            cout << "\nPilihan " << option << " Tidak Ada! Silahkan Pilih/Ketik 1, 2, atau 3!\n";
            cout << "\n=======================================================\n";
            goto awal;
            break;
    }
}