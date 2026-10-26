// // #ifndef SINGLYLIST_H
// // #define SINGLYLIST_H

// // #include <iostream>
// // using namespace std;

// // #define Nil NULL

// // typedef int infotype;
// // typedef struct ElmList *address;

// // struct ElmList {
// //     infotype info;
// //     address next;
// // };

// // struct List {
// //     address first;
// // };

// // void CreateList(List &L);
// // address alokasi(infotype x);
// // void dealokasi(address &P);
// // void printInfo(List L);
// // void insertFirst(List &L, address P);

// // #endif

// #ifndef SINGLYLIST_H
// #define SINGLYLIST_H

// #include <iostream>
// using namespace std;

// #define Nil NULL

// typedef int infotype;
// typedef struct ElmList *address;

// struct ElmList {
//     infotype info;
//     address next;
// };

// struct List {
//     address first;
// };

// void CreateList(List &L);
// address alokasi(infotype x);
// void dealokasi(address &P);
// void printInfo(List L);
// void insertFirst(List &L, address P);
// address findElm(List L, infotype x);

// #endif

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