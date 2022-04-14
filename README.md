# Simple Restaurant

Program Restoran sederhana dilengkapi dengan login dan register user.

## Deskripsi Singkat

Pada program restoran yang saya buat ini terintegrasi dengan file .txt sebagai database untuk menyimpan beberapa data diantaranya data user, dan data makanan. Beberapa fitur lainnya:

-   User dapat melakukan registrasi, dengan menginputkan username dan password.
-   User dapat melakukan login dari data yang sudah teregistrasi.
-   Mode Admin untuk menambahkan, mengupdate, membaca, dan menghapus makanan/minuman pada database
-   User dapat membuat pesanan dari produk makanan/minuman yang tersedia.
-   Dapat memunculkan tagihan dan harga total sesuai dengan pesanan user.
-   User dapat menginputkan cash sebagai metode pembayaran.
-   Menampilkan total uang kembali jika user menginputkan cash lebih dari tagihan.
-   Program akan terus berjalan dengan berbagai pilihan menu yang menarik.
-   Program akan berhenti jika user memilih menu exit program.

## Dokumentasi

#### Halaman Awal Saat Program diajalankan

<img src="image/awal.png" width="400">

#### Register

Input Username & Password
<img src="image/register.png" width="400">

Register Sukses
<img src="image/register_sukses.png" width="400">

#### Login

Input username & password, jika sukses maka akan tampil **Menu Utama** dibawah ini
<img src="image/login_sukses.png" width="400">

#### Administrator Mode

<img src="image/admin_menu.png" width="400">

-   **Menambahkan Produk**
    Input Nama & Harga.
    <img src="image/add_product.png" width="400">

-   **Show Produk**
    <img src="image/show_product.png" width="400">

-   **Update Produk**
    Input nama produk yang ingin diperbarui.
    dan Input Harga terbarunya.
    <img src="image/update_product.png" width="400">

-   **Delete Produk**
    Input nama produk yang ingin dihapus.
    <img src="image/delete_product.png" width="400">

#### Membuat Pesanan

Input nama produk yang diinginkan beserta dengan jumlahnya.
<img src="image/buat_pesanan.png" width="400">

-   **Invoice**
    Jika input **no** pada pilihan diatas, maka akan menampilkan tagihan user.
    <img src="image/tagihan.png" width="400">

-   **Payment**
    Jika input **CASH** lebih dari sama dengan total tagihan, maka tampilan sebagai berikut
    <img src="image/pembayaran_sukses.png" width="400">
