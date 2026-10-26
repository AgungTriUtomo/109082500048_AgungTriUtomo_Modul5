# <h1 align="center">Laporan Praktikum Modul 5 - Singly Linked List (Bagian Kedua)</h1>
<p align="center">Agung Tri Utomo - 109082500048</p>

## Dasar Teori

Linked list atau senarai berantai adalah struktur data linear yang elemen-elemennya dihubungkan menggunakan pointer. Berbeda dengan array yang berukuran tetap, linked list memanfaatkan alokasi memori dinamis sehingga memori baru dialokasikan hanya ketika dibutuhkan saat program berjalan [2]. Karakter ini membuat linked list fleksibel dan hemat memori, meskipun waktu aksesnya lebih lambat dibandingkan array [1]. Dalam pengelolaan data, array unggul pada akses langsung berdasarkan indeks dengan kompleksitas O(1), sedangkan linked list lebih cocok untuk data yang sering berubah karena penyisipan dan penghapusan tidak memerlukan pergeseran elemen lain [3].

### A. Singly Linked List<br/>
Singly linked list adalah jenis linked list yang setiap node-nya hanya memiliki satu pointer, yaitu menuju node berikutnya, sehingga penelusuran hanya dapat dilakukan satu arah dari awal list sampai akhir list.
#### 1. Node (ElmList)
Setiap elemen (node) terdiri dari dua bagian: `info` yang menyimpan data dan `next` yang menyimpan alamat node selanjutnya. Pada modul ini `info` bertipe `int` dan `address` adalah pointer ke `ElmList`.
#### 2. List dan Pointer First
List direpresentasikan oleh sebuah struct `List` yang hanya memiliki satu field, yaitu `first`, pointer yang menunjuk ke node pertama. List dinyatakan kosong apabila `first` bernilai `Nil` (`NULL`). Node terakhir ditandai dengan `next` yang bernilai `Nil`.
#### 3. Abstract Data Type (ADT)
Operasi-operasi pada list dikumpulkan dalam sebuah ADT yang terdiri dari file header (`*.h`) berisi deklarasi tipe dan prototype, file implementasi (`*.cpp`) berisi isi fungsi dan prosedur, serta file `main.cpp` untuk mencoba ADT tersebut. Struktur ini memisahkan definisi dari penggunaannya sehingga kode lebih rapi dan mudah dipakai ulang.

### B. Operasi Dasar Singly Linked List<br/>
Operasi dasar pada linked list mencakup pembuatan list, alokasi dan dealokasi node, penambahan elemen, penghapusan elemen, pencarian, serta penelusuran seluruh elemen. Operasi tambah, cari, dan hapus data merupakan fungsi utama yang diuji pada penerapan linked list untuk mengelola data [2].
#### 1. Alokasi dan insertFirst
Fungsi `alokasi` membuat node baru dengan `new`, mengisi `info`, dan mengatur `next` ke `Nil`. Prosedur `insertFirst` menyisipkan node di awal list dengan cara mengarahkan `next` node baru ke `first` yang lama, lalu menjadikan node baru sebagai `first`. Karena penyisipan selalu di awal, elemen yang dimasukkan terakhir menjadi elemen pertama pada list.
#### 2. Searching (findElm)
Searching dilakukan dengan mengunjungi setiap node dari `first`, membandingkan `info` dengan nilai yang dicari, dan berhenti begitu ditemukan. Jika sampai akhir list tidak ditemukan, fungsi mengembalikan `Nil`. Operasi searching mempermudah operasi lain seperti insert after, delete after, dan update.
#### 3. Traversal (printInfo dan penjumlahan info)
Traversal adalah proses menelusuri seluruh node dari awal sampai akhir list dengan pointer bantu. Pola ini dipakai untuk menampilkan isi list (`printInfo`) maupun untuk menghitung total `info` seluruh elemen.

## Guided
### 1.ListBuah.h
```c++
#ifndef LISTBUAH_H
#define LISTBUAH_H
#define Nil NULL

#include<iostream>
using namespace std;

struct buah{
    string nama;
    int jumlah; 
    float harga;
};

typedef buah dataBuah; 

typedef struct node *address; 

struct node{ 
    buah isidata;
    address next;
};

struct linkedlist{ 
    address first;
};

bool isEmpty(linkedlist List);
void createList(linkedlist &List);
address alokasi(string nama, int jumlah, float harga);
void dealokasi(address &node);
void printList(linkedlist List);
void insertFirst(linkedlist &List, address nodeBaru);
void insertAfter(linkedlist &List, address nodeBaru, address Prev);
void insertLast(linkedlist &List, address nodeBaru);
void delFirst(linkedlist &List);
void delLast(linkedlist &List);
void delAfter(linkedlist &List, address nodeHapus, address nodePrev);
int nbList(linkedlist List);
void deleteList(linkedlist &List);

void updateFirst(linkedlist List);
void updateLast(linkedlist List);
void updateAfter(linkedlist List, address prev);

void FindNodeByData(linkedlist list, string data);
void FindNodeByAddress(linkedlist list, address node);
void FindNodeByRange(linkedlist list, float hargaAwal, float HargaAkhir);

#endif

```
Penjelasan Guided 1
listbuah.h adalah header ADT singly linked list untuk data buah (nama, jumlah, harga) yang mendefinisikan struktur buah, node, dan linkedlist beserta prototype operasi pembuatan list, penambahan, penghapusan, penampilan, penghitungan, pembaruan, dan pencarian node.

### 2.listBuah.cpp
```c++
#include "listBuah.h"
#include <iostream>
using namespace std;

//fungsi untuk cek apakah list kosong atau tidak
bool isEmpty(linkedlist List) {
    if(List.first == Nil){
        return true; 
    } else {
        return false;
    }
}

//pembuatan linked list kosong
void createList(linkedlist &List) {
    List.first = Nil;
}

//pembuatan node baru dengan menerapkan manajemen memori
address alokasi(string nama, int jumlah, float harga) { 
    address nodeBaru = new node; 
    nodeBaru->isidata.nama = nama;
    nodeBaru->isidata.jumlah = jumlah; 
    nodeBaru->isidata.harga = harga;
    nodeBaru->next = Nil;
    return nodeBaru;
}

//penghapusan node dengan menerapkan manajemen memori
void dealokasi(address &node) {
    node->next = Nil;
    delete node;
}

//prosedur-prosedur untuk insert / menambahkan node baru kedalam list
void insertFirst(linkedlist &List, address nodeBaru) {
    nodeBaru->next = List.first; 
    List.first = nodeBaru;
}

void insertAfter(linkedlist &List, address nodeBaru, address Prev) {
    if (Prev != Nil) {
        nodeBaru->next = Prev->next;
        Prev->next = nodeBaru;
    } else {
        cout << "Node sebelumnya tidak valid!" << endl;
    }
}

void insertLast(linkedlist &List, address nodeBaru) {
    if (isEmpty(List)) {
        List.first = nodeBaru;
    } else {
        address nodeBantu = List.first;
        while (nodeBantu->next != Nil) {
            nodeBantu = nodeBantu->next;
        }
        nodeBantu->next = nodeBaru;
    }
}

//prosedur-prosedur untuk delete / menghapus node yang ada didalam list
void delFirst(linkedlist &List){
    address nodeHapus;
    if (isEmpty(List) == false) {
        nodeHapus = List.first;
        List.first = List.first->next;
        nodeHapus->next = Nil;
        dealokasi(nodeHapus);
        cout << "Node pertama berhasil terhapus!" << endl;
    } else {
        cout << "List kosong!" << endl;
    }
}

void delLast(linkedlist &List){
    address nodeHapus, nodePrev;
    if(isEmpty(List) == false){
        nodeHapus = List.first;
        if(nodeHapus->next == Nil){
            List.first->next = Nil;
            dealokasi(nodeHapus);
        } else { 
            while(nodeHapus->next != Nil){
                nodePrev = nodeHapus; 
                nodeHapus = nodeHapus->next;
            }
            nodePrev->next = Nil; 
            dealokasi(nodeHapus);
        }
        cout << "Node terakhir berhasil terhapus!" << endl;
    } else {
        cout << "list kosong" << endl;
    }
}

void delAfter(linkedlist &List, address nodeHapus, address nodePrev){
    if(isEmpty(List) == true){
        cout << "List kosong!" << endl;
    } else { //jika list tidak kosong
        if (nodePrev != Nil && nodePrev->next != Nil) { 
            nodeHapus = nodePrev->next;       
            nodePrev->next = nodeHapus->next;  
            nodeHapus->next = Nil;         
            dealokasi(nodeHapus);
            cout << "Node setelah node " << nodePrev->isidata.nama << " berhasil terhapus!" << endl;
        } else {
            cout << "Node sebelumnya (prev) tidak valid!" << endl;
        }
    }
}

//prosedur untuk menampilkan isi list
void printList(linkedlist List) {
    if (isEmpty(List)) {
        cout << "List kosong." << endl;
    } else {
        address nodeBantu = List.first;
        while (nodeBantu != Nil) { 
            cout << "Nama Buah : " << nodeBantu->isidata.nama << ", Jumlah : " << nodeBantu->isidata.jumlah << ", Harga : " << nodeBantu->isidata.harga << endl;
            nodeBantu = nodeBantu->next;
        }
    }
}

//function untuk menampilkan jumlah node didalam list
int nbList(linkedlist List) {
    int count = 0;
    address nodeBantu = List.first;
    while (nodeBantu != Nil) {
        count++;
        nodeBantu = nodeBantu->next; 
    }
    return count;
}

//prosedur untuk menghapus list (menghapus semua node didalam list)
void deleteList(linkedlist &List){
    address nodeBantu, nodeHapus;
    nodeBantu = List.first;
    while(nodeBantu != Nil){
        nodeHapus = nodeBantu;
        nodeBantu = nodeBantu->next;
        dealokasi(nodeHapus); 
    }
    List.first = Nil; 
    cout << "List berhasil terhapus!" << endl;
}

/*----- MATERI PERTEMUAN 5 - SINGLY LINKED LIST (BAGIAN KEDUA) - UPDATE -----*/
//prosedur-prosedur untuk melakukan update data node
void updateFirst(linkedlist List){
    if(isEmpty(List) == true){
        cout << "List kosong!" << endl;
    } else {
        cout << "Masukkan update data node pertama : " << endl;
        cout << "Nama buah : ";
        cin >> List.first->isidata.nama;
        cout << "Jumlah : ";
        cin >> List.first->isidata.jumlah;
        cout << "Harga : ";
        cin >> List.first->isidata.harga;
        cout << "Data Berhasil Diupdate!" << endl;
        cout << endl;
    }
}

void updateLast(linkedlist List){
    if (isEmpty(List) == true) {
        cout << "List Kosong!" << endl;
    } else {
        address nodeBantu = List.first;
        while (nodeBantu->next != Nil) {
            nodeBantu = nodeBantu->next;
        }
        cout << "masukkan update data node terakhir : " << endl;
        cout << "Nama buah : ";
        cin >> nodeBantu->isidata.nama;
        cout << "Jumlah : ";
        cin >> nodeBantu->isidata.jumlah;
        cout << "Harga : ";
        cin >> nodeBantu->isidata.harga;
        cout << "Data Berhasil Diupdate!" << endl;
        cout << endl;
    }
}

void updateAfter(linkedlist List, address nodePrev){
    if(isEmpty(List) == true){
        cout << "List kosong!" << endl;
    } else {
        if (nodePrev != Nil && nodePrev->next != Nil){
            address nodeBantu = nodePrev->next;
            cout << "masukkan update data node setelah node " << nodePrev->isidata.nama << " : " << endl;
            cout << "Nama buah : ";
            cin >> nodeBantu->isidata.nama;
            cout << "Jumlah : ";
            cin >> nodeBantu->isidata.jumlah;
            cout << "Harga : ";
            cin >> nodeBantu->isidata.harga;
            cout << "Data Berhasil Diupdate!" << endl;
            cout << endl;
        } else {
            cout << "Node sebelumnya (prev) tidak valid!" << endl;
        }
    }
}

/*----- MATERI PERTEMUAN 5 - SINGLY LINKED LIST (BAGIAN KEDUA) - SEARCHING -----*/
//prosedur-prosedur untuk searching data
//prosedur untuk mencari node berdasarkan data
void FindNodeByData(linkedlist list, string data){
    if(isEmpty(list) == true){
        cout << "List kosong!" << endl;
    } else {
        address nodeBantu = list.first;
        int posisi = 0;
        bool found = false;
        while(nodeBantu != Nil){
            posisi++;
            if(nodeBantu->isidata.nama == data){
                cout << "Data " << data << " ditemukan pada posisi ke-" << posisi << "!" << endl;
                cout << "Nama Buah : " << nodeBantu->isidata.nama << ", Jumlah : " << nodeBantu->isidata.jumlah << ", Harga : " << nodeBantu->isidata.harga << endl;
                found = true;
                break;
            }
            nodeBantu = nodeBantu->next;
        }
        if(found == false){
            cout << "Node dengan data " << data << " tidak ditemukan!" << endl;
        }
    }
    cout << endl;
}

//prosedur untuk mencari node berdasarkan alamat node
void FindNodeByAddress(linkedlist list, address node) {
    if(isEmpty(list) == true) {
        cout << "List kosong!" << endl;
    } else {
        address nodeBantu = list.first;
        int posisi = 0;
        bool found = false;
        while (nodeBantu != Nil) {
            posisi++;
            if(nodeBantu == node) {
                cout << "Node ditemukan pada posisi ke-" << posisi << "!" << endl;
                cout << "Alamat node : " << nodeBantu << endl;
                cout << "Nama Buah : " << nodeBantu->isidata.nama << ", Jumlah : " << nodeBantu->isidata.jumlah << ", Harga : " << nodeBantu->isidata.harga << endl;
                found = true;
                break;
            }
            nodeBantu = nodeBantu->next;
        }
        if(found == false) {
            cout << "Node dengan alamat " << node << " tidak ditemukan dalam list!" << endl;
        }
    }
    cout << endl;
}

//prosedur untuk mencari node berdasarkan range data (range harga)
void FindNodeByRange(linkedlist list, float hargaAwal, float hargaAkhir) {
    if(isEmpty(list) == true) {
        cout << "List kosong!" << endl;
    } else {
        address nodeBantu = list.first;
        int posisi = 0;
        bool found = false;
        cout << "--- Buah dalam range harga " << hargaAwal << " - " << hargaAkhir << " ---" << endl;
        cout << "-------------------------------------------" << endl;
        while (nodeBantu != Nil) {
            posisi++;
            float harga = nodeBantu->isidata.harga;
            if(harga >= hargaAwal && harga <= hargaAkhir) {
                cout << "Data ditemukan pada posisi ke-" << posisi << " :" << endl;
                cout << "Nama Buah : " << nodeBantu->isidata.nama << ", Jumlah : " << nodeBantu->isidata.jumlah << ", Harga : " << nodeBantu->isidata.harga << endl;
                cout << "-------------------------------------------" << endl;
                found = true;
            }
            nodeBantu = nodeBantu->next;
        }
        if(found == false) {
            cout << "Tidak ada data buah dalam range harga tersebut!" << endl;
            cout << "-------------------------------------------" << endl;
        }
    }
    cout << endl;
}
```
Penjelasan guided 2
Program ini Berisi implementasi semua prototype di listBuah.h, yaitu pembuatan dan alokasi node, penyisipan dan penghapusan node, penampilan dan penghitungan isi list, pembaruan data node, serta pencarian node berdasarkan nama, alamat, atau rentang harga dengan menelusuri list dari first sampai Nil.

### 3.main.cpp
```c++
#include "listBuah.h"

  #include<iostream>
  using namespace std;

  int main(){
      linkedlist List;
      address nodeA, nodeB, nodeC, nodeD, nodeE = Nil;
      createList(List);

      dataBuah dtBuah;

      nodeA = alokasi("Jeruk", 100, 3000);
      nodeB = alokasi("Apel", 75, 4000);
      nodeC = alokasi("Pir", 87, 5000);
      nodeD = alokasi("Semangka", 43, 11500);
      nodeE = alokasi("Durian", 15, 31450);

      insertFirst(List, nodeA);
      insertLast(List, nodeB);
      insertAfter(List, nodeC, nodeA);
      insertAfter(List, nodeD, nodeC);
      insertLast(List, nodeE);

      cout << "--- ISI LIST SETELAH DILAKUKAN INSERT ---" << endl;
      printList(List);
      cout << "jumlah node : " << nbList(List) << endl;
      cout << endl;

      updateFirst(List);
      printList(List);
      updateLast(List);
      printList(List);
      updateAfter(List, nodeD);
      printList(List);

      cout << "--- ISI LIST SETELAH DILAKUKAN UPDATE ---" << endl;
      printList(List);
      cout << "jumlah node : " << nbList(List) << endl;
      cout << endl;

      FindNodeByData(List, "kelapa");
      FindNodeByAddress(List, nodeC);
      FindNodeByRange(List, 5000, 10000);

      delFirst(List);
      printList(List);
      delLast(List);
      printList(List);
      delAfter(List, nodeD, nodeC);
      printList(List);

      cout << "--- ISI LIST SETELAH DILAKUKAN DELETE ---" << endl;
      printList(List);
      cout << "jumlah node : " << nbList(List) << endl;
      cout << endl;

      deleteList(List);
      cout << "--- ISI LIST SETELAH DILAKUKAN HAPUS LIST ---" << endl;
      printList(List);
      cout << "jumlah node : " << nbList(List) << endl;
      cout << endl;

      return 0;
  }
  ```
  Penjelasan guided 3
  Program ini membuat list lima buah, lalu menguji operasi insert, update, pencarian, delete, dan hapus list secara berurutan sambil menampilkan isi list dan jumlah node di setiap tahap.

## Unguided

### 1. Buatlah ADT Singly Linked List pada file "Singlylist.h", implementasinya pada file "Singlylist.cpp", lalu cobalah pada file "main.cpp" dengan isi list 9, 12, 8, 0, 2

**Singlylist.h**
```C++
#ifndef SINGLYLIST_H
#define SINGLYLIST_H

#include <iostream>
using namespace std;

#define Nil NULL

typedef int infotype;
typedef struct ElmList *address;

struct ElmList {
    infotype info;
    address next;
};

struct List {
    address first;
};

void CreateList(List &L);
address alokasi(infotype x);
void dealokasi(address &P);
void printInfo(List L);
void insertFirst(List &L, address P);

#endif
```

**Singlylist.cpp**
```C++
#include "Singlylist.h"

void CreateList(List &L) {
    L.first = Nil;
}

address alokasi(infotype x) {
    address P = new ElmList;
    P->info = x;
    P->next = Nil;
    return P;
}

void dealokasi(address &P) {
    delete P;
    P = Nil;
}

void printInfo(List L) {
    address P = L.first;
    while (P != Nil) {
        cout << P->info << " ";
        P = P->next;
    }
    cout << endl;
}

void insertFirst(List &L, address P) {
    P->next = L.first;
    L.first = P;
}
```

**main.cpp**
```C++
#include "Singlylist.h"

int main() {
    List L;
    address P1, P2, P3, P4, P5 = Nil;
    CreateList(L);

    P1 = alokasi(2);
    insertFirst(L, P1);
    P2 = alokasi(0);
    insertFirst(L, P2);
    P3 = alokasi(8);
    insertFirst(L, P3);
    P4 = alokasi(12);
    insertFirst(L, P4);
    P5 = alokasi(9);
    insertFirst(L, P5);

    printInfo(L);
    return 0;
}
```
### Output Unguided 1 :

##### Output 1
![Screenshot Output Unguided 1_1](https://github.com/AgungTriUtomo/109082500048_AgungTriUtomo_Modul5/blob/main/Output/Outputsoal1.png)

Program membuat list kosong dengan `CreateList`, lalu mengalokasikan lima node dengan nilai 2, 0, 8, 12, dan 9 yang masing-masing disisipkan di awal list menggunakan `insertFirst`. Karena setiap node baru menjadi elemen pertama, urutan list akhir adalah kebalikan dari urutan penyisipan, yaitu 9 → 12 → 8 → 0 → 2, sesuai dengan ilustrasi pada Gambar 5-1 modul. Fungsi `printInfo` menelusuri list dari `first` hingga `Nil` sehingga menampilkan `9 12 8 0 2`.

### 2. Carilah elemen dengan info 8 dengan membuat fungsi baru `findElm(L : List, x : infotype) : address`

Tambahan prototype pada **Singlylist.h**
```C++
address findElm(List L, infotype x);
```

Tambahan implementasi pada **Singlylist.cpp**
```C++
address findElm(List L, infotype x) {
    address P = L.first;
    while (P != Nil) {
        if (P->info == x) {
            return P;
        }
        P = P->next;
    }
    return Nil;
}
```

Tambahan pada **main.cpp** (setelah `printInfo(L);`)
```C++
    address cari = findElm(L, 8);
    if (cari != Nil) {
        cout << cari->info << " ditemukan dalam list" << endl;
    } else {
        cout << "8 tidak ditemukan dalam list" << endl;
    }
```
### Output Unguided 2 :

##### Output 1
![Screenshot Output Unguided 2_1](https://github.com/AgungTriUtomo/109082500048_AgungTriUtomo_Modul5/blob/main/Output/Outputsoal2.png)

Fungsi `findElm` menelusuri list dengan pointer bantu `P` mulai dari `first`. Pada setiap node, `info` dibandingkan dengan nilai `x` yang dicari. Jika sama, alamat node dikembalikan dan pencarian berhenti; jika sampai `Nil` tidak ada yang cocok, fungsi mengembalikan `Nil`. Pada list 9, 12, 8, 0, 2, nilai 8 ditemukan di node ketiga sehingga `main` menampilkan "8 ditemukan dalam list".

### 3. Hitunglah jumlah total info seluruh elemen (9+12+8+0+2=31)

Tambahan prototype pada **Singlylist.h**
```C++
int sumInfo(List L);
```

Tambahan implementasi pada **Singlylist.cpp**
```C++
int sumInfo(List L) {
    int total = 0;
    address P = L.first;
    while (P != Nil) {
        total += P->info;
        P = P->next;
    }
    return total;
}
```

Tambahan pada **main.cpp** (setelah proses pencarian)
```C++
    cout << "Total info dari kelima elemen adalah " << sumInfo(L) << endl;
```
### Output Unguided 3 :

##### Output 1
![Screenshot Output Unguided 3_1](https://github.com/AgungTriUtomo/109082500048_AgungTriUtomo_Modul5/blob/main/Output/Outputsoal3.png)

Fungsi `sumInfo` menelusuri seluruh node dari `first` sampai `Nil` dan menjumlahkan nilai `info` setiap node ke variabel `total`. Untuk list 9, 12, 8, 0, 2 hasilnya 9 + 12 + 8 + 0 + 2 = 31, sesuai dengan output yang diminta pada modul.

## Kesimpulan
Pada praktikum ini ADT singly linked list berhasil diimplementasikan dalam tiga file, yaitu `Singlylist.h`, `Singlylist.cpp`, dan `main.cpp`. Operasi `insertFirst` menyisipkan elemen di awal list sehingga urutan list menjadi kebalikan dari urutan penyisipan. Operasi searching (`findElm`) dan penjumlahan info (`sumInfo`) sama-sama bertumpu pada penelusuran node satu per satu dari `first` sampai `Nil`, dan seluruh hasilnya sesuai dengan output pada modul. Praktikum ini menunjukkan bahwa linked list memanfaatkan pointer dan alokasi memori dinamis sehingga penambahan data tidak terbatas ukuran tetap seperti array.

## Referensi
[1] Wijoyo, A., Prasetiyo, A. R., Salsabila, A. A., Nife, K., Murni, & Nadapdap, P. B. (2024). "Evaluasi Efisiensi Struktur Data Linked List pada Implementasi Sistem Antrian". JRIIN: Jurnal Riset Informatika dan Inovasi, 1(12), 1244–1246. Diakses melalui https://jurnalmahasiswa.com/index.php/jriin/article/view/1060.
<br>[2] Fitra, M. R. A., Effendi, A. A. S., & Ramadhani, F. (2025). "Implementasi Python dalam Pengolahan Data Pribadi Mahasiswa Ilmu Komputer Angkatan 23 pada Universitas Negeri Medan Menggunakan Struktur Data Linked List". JATI (Jurnal Mahasiswa Teknik Informatika), 9(1), 51–58. https://doi.org/10.36040/jati.v9i1.12164.
<br>[3] Sofianti, H. A., Manullang, Y. V., Tampubolon, N. A., Naibaho, L. H., & Gunawan, I. (2025). "Implementasi Struktur Data Array dan Linked List dalam Pengelolaan Data Mahasiswa". Menulis: Jurnal Penelitian Nusantara, 1(6), 871–877. https://doi.org/10.59435/menulis.v1i6.417.
