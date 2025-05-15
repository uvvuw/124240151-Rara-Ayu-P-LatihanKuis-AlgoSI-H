#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int nomor;
    string nama;
    string keluhan;
    Node *prev;
    Node *next;
};

Node *head = nullptr, *tail = nullptr;

bool isEmpty()
{
    return head == nullptr;
}

// Tambah Pasien
void sisipPasien(string nama, int antrian, string keluhan)
{
    Node *newNode = new Node;
    newNode->nama = nama;
    newNode->nomor = antrian;
    newNode->keluhan = keluhan;
    newNode->prev = newNode->next = nullptr;

    if (isEmpty())
    {
        head = tail = newNode;
    }
    else if (antrian < head->nomor)
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    else if (antrian > tail->nomor)
    {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    else
    {
        Node *cur = head;
        while (cur != nullptr && antrian > cur->nomor)
        {
            cur = cur->next;
        }
        newNode->next = cur;
        newNode->prev = cur->prev;
        cur->prev->next = newNode;
        cur->prev = newNode;
    }

    cout << "Pasien berhasil ditambahkan ke daftar.\n"
         << endl;
}

// Tampilkan Antrian dari Awal (print depan)
void tampilkanDariDepan()
{
    if (isEmpty())
    {
        cout << "Antrian kosong.\n";
        return;
    }

    cout << "\nDaftar Antrian (Dari Awal)\n";
    cout << "=============================\n";

    Node *temp = head;
    while (temp != nullptr)
    {
        cout << "No Antrian: " << temp->nomor << endl;
        cout << "Nama: " << temp->nama << endl;
        cout << "Keluhan: " << temp->keluhan << endl;
        cout << "--------------------------------\n";
        temp = temp->next;
    }
}

// Tampilkan Antrian dari Akhir (print belakang)
void tampilkanDariBelakang()
{
    if (isEmpty())
    {
        cout << "Antrian kosong.\n";
        return;
    }

    cout << "\nDaftar Antrian (Dari Akhir)\n";
    cout << "=============================\n";

    Node *temp = tail;
    while (temp != nullptr)
    {
        cout << "No Antrian: " << temp->nomor << endl;
        cout << "Nama: " << temp->nama << endl;
        cout << "Keluhan: " << temp->keluhan << endl;
        cout << "--------------------------------\n";
        temp = temp->prev;
    }
}

// Cari Pasien Berdasarkan Nomor Antrian
void cariPasien(int nomor)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->nomor == nomor)
        {
            cout << "Pasien Ditemukan: " << endl;
            cout << "No Antrian: " << temp->nomor << endl;
            cout << "Nama: " << temp->nama << endl;
            cout << "Keluhan: " << temp->keluhan << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Pasien dengan no antrian " << nomor << " tidak ditemukan.\n";
}

// Hapus Pasien Berdasarkan Nomor Antrian
void hapusPasien(int nomor)
{
    if (isEmpty())
    {
        cout << "Antrian kosong.\n";
        return;
    }

    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->nomor == nomor)
        {
            if (temp == head)
            {
                head = head->next;
                if (head != nullptr)
                    head->prev = nullptr;
                else
                    tail = nullptr;
            }
            else if (temp == tail)
            {
                tail = tail->prev;
                if (tail != nullptr)
                    tail->next = nullptr;
                else
                    head = nullptr;
            }
            else
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            delete temp;
            cout << "Data pasien berhasil dihapus.\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Pasien dengan no antrian " << nomor << " tidak ditemukan.\n";
}

void menu()
{
    int pilihan;
    do
    {
        cout << "\n=== MENU ANTRIAN PASIEN KLINIK SEHAT SELALU ===\n";
        cout << "1. Tambah Data Pasien\n";
        cout << "2. Tampilkan Antrian dari Awal\n";
        cout << "3. Tampilkan Antrian dari Akhir\n";
        cout << "4. Cari Data Pasien\n";
        cout << "5. Hapus Data Pasien\n";
        cout << "6. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        if (cin.fail())
        {
            cin.clear();
            cout << "Input tidak valid.\n";
            return;
        }

        int nomor;
        string nama, keluhan;

        switch (pilihan)
        {
        case 1:
            cout << "Masukkan No Antrian : ";
            cin >> nomor;
            cin.ignore();
            cout << "Masukkan Nama Pasien : ";
            getline(cin, nama);
            cout << "Masukkan Keluhan : ";
            getline(cin, keluhan);
            sisipPasien(nama, nomor, keluhan);
            break;
        case 2:
            tampilkanDariDepan();
            break;
        case 3:
            tampilkanDariBelakang();
            break;
        case 4:
            cout << "Masukkan No Antrian yang dicari: ";
            cin >> nomor;
            cout << endl;
            cariPasien(nomor);
            break;
        case 5:
            cout << "Masukkan No Antrian yang ingin dihapus: ";
            cin >> nomor;
            hapusPasien(nomor);
            break;
        case 6:
            cout << "Keluar dari Program...\n";
            break;
        default:
            cout << "Pilihan tidak tersedia.\n";
        }

    } while (pilihan != 6);
}

int main()
{
    menu();
    return 0;
}