#include <iostream>
using namespace std;

struct Node {
    int heSo;
    int soMu;
    Node* next;

    Node(int hs = 0, int sm = 0) : heSo(hs), soMu(sm), next(nullptr) {}
};

struct DaThuc {
    Node* dau = nullptr;
};

void khoiTaoDaThuc(DaThuc& daThuc) {
    daThuc.dau = nullptr;
}

void themNode(DaThuc& daThuc, int heSo, int soMu) {
    Node* nodeMoi = new Node(heSo, soMu);
    if (!daThuc.dau) {
        daThuc.dau = nodeMoi;
    } else {
        Node* current = daThuc.dau;
        while (current->next) {
            current = current->next;
        }
        current->next = nodeMoi;
    }
}

void inDaThuc(const DaThuc& daThuc) {
    Node* current = daThuc.dau;
    while (current) {
        cout << current->heSo << ".x^" << current->soMu;
        current = current->next;
        if (current) cout << " + ";
    }
    cout << endl;
}

DaThuc congDaThuc(DaThuc& daThuc1, DaThuc& daThuc2) {
    DaThuc ketQua;
    khoiTaoDaThuc(ketQua);

    Node** cuoi = &ketQua.dau;
    Node* n1 = daThuc1.dau;
    Node* n2 = daThuc2.dau;

    while (n1 || n2) {
        if (n1 && (!n2 || n1->soMu > n2->soMu)) {
            *cuoi = n1;
            n1 = n1->next;
        } else if (n2 && (!n1 || n2->soMu > n1->soMu)) {
            *cuoi = n2;
            n2 = n2->next;
        } else if (n1 && n2 && n1->soMu == n2->soMu) {
            n1->heSo += n2->heSo;
            if (n1->heSo != 0) {
                *cuoi = n1;
                cuoi = &((*cuoi)->next);
            }
            Node* canXoa = n2;
            n1 = n1->next;
            n2 = n2->next;
            delete canXoa;
            continue;
        }
        cuoi = &((*cuoi)->next);
    }

    *cuoi = nullptr;
    daThuc1.dau = nullptr;
    daThuc2.dau = nullptr;

    return ketQua;
}

int main() {
    DaThuc daThuc1, daThuc2;
    khoiTaoDaThuc(daThuc1);
    khoiTaoDaThuc(daThuc2);

    int soHang, heSo, soMu;

    cout << "Nhap so luong hang tu cho da thuc thu nhat: ";
    cin >> soHang;
    for (int i = 0; i < soHang; i++) {
        cout << "Nhap he so va so mu cho hang tu thu " << i + 1 << ": ";
        cin >> heSo >> soMu;
        themNode(daThuc1, heSo, soMu);
    }

    cout << "Nhap so luong hang tu cho da thuc thu hai: ";
    cin >> soHang;
    for (int i = 0; i < soHang; i++) {
        cout << "Nhap he so va so mu cho hang tu thu " << i + 1 << ": ";
        cin >> heSo >> soMu;
        themNode(daThuc2, heSo, soMu);
    }

    cout << "f(x)= ";
    inDaThuc(daThuc1);
    cout << "g(x)= ";
    inDaThuc(daThuc2);

    DaThuc ketQua = congDaThuc(daThuc1, daThuc2);
    cout << "f(x)+g(x)=h(x)= ";
    inDaThuc(ketQua);

    return 0;
}
