#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

// Ham tao mot node moi
Node* taoNode(int data) {
    Node* node = new Node;
    node->data = data;
    node->next = nullptr;
    return node;
}

// Ham tao danh sach vong tron
Node* taoDanhSachVongTron(int soNguoi) {
    Node* dau = taoNode(1); // Tao node dau tien
    Node* truoc = dau;

    // Tao danh sach vong tron gom soNguoi node
    for (int i = 2; i <= soNguoi; i++) {
        Node* node = taoNode(i);
        truoc->next = node;
        truoc = node;
    }

    truoc->next = dau; // Ket noi node cuoi cung voi node dau tien
    return dau;
}

// Giai thuat Josephus
int josephus(int soNguoi, int buocLoaiBo) {
    if (soNguoi == 1) return 1;

    Node* dau = taoDanhSachVongTron(soNguoi);
    Node* truoc = dau;
    Node* current = dau;

    // Di chuyen truoc den node dung truoc dau de khoi tao vong tron
    while (truoc->next != dau) {
        truoc = truoc->next;
    }

    // Lap cho den khi con mot node
    while (current->next != current) {
        // Di chuyen buocLoaiBo - 1 buoc de tim node bi loai
        for (int i = 1; i < buocLoaiBo; i++) {
            truoc = current;
            current = current->next;
        }

        // In ra node bi loai
        cout << "Node bi loai: " << current->data << endl;

        // Loai bo node hien tai
        truoc->next = current->next;
        delete current;
        current = truoc->next; // Nguoi ke tiep giu qua bong
    }

    int nguoiChienThang = current->data;
    delete current; // Giai phong bo nho cua node cuoi cung
    return nguoiChienThang;
}

int main() {
    int soNguoi, buocLoaiBo;
    cout << "Nhap so nguoi choi (N): ";
    cin >> soNguoi;
    cout << "Nhap buoc loai bo (M): ";
    cin >> buocLoaiBo;

    int nguoiChienThang = josephus(soNguoi, buocLoaiBo);
    cout << "Nguoi chien thang: " << nguoiChienThang << endl;

    return 0;
}
