#include <bits/stdc++.h>
#include <cstring>
using namespace std;

struct Ngay{
    int ngay, thang, nam;
};

struct sinhVien{
    char maSV[8];
    char hoten[50];
    int gioiTinh;
    Ngay ngaysinh;
    char diaChi;
    char lop[12];
    char khoa[7];
};

struct Node{
    sinhVien data;
    Node *link;
};

struct List{
    Node *first = nullptr;
    Node *last = nullptr;
};

void insertStudent(sinhVien &sv) { //Ham nhap sinh vien
    cout << "Nhap ma sinh vien: "; cin >> sv.maSV;
    cout << "Nhap ho ten: "; cin >> sv.hoten;
    cout << "Nhap gioi tinh (Nam=1, Nu=0): "; cin >> sv.gioiTinh;
    cout << "Nhap ngay sinh (ngay thang nam): "; cin >> sv.ngaysinh.ngay >> sv.ngaysinh.thang >> sv.ngaysinh.nam;
    cout << "Nhap dia chi: "; cin >> sv.diaChi;
    cout << "Nhap lop: "; cin >> sv.lop;
    cout << "Nhap khoa: "; cin >> sv.khoa;
}

void printStudent(sinhVien sv) { //Ham in sinh vien
    cout << "Ma SV: " << sv.maSV << ", Ho ten: " << sv.hoten << ", Gioi tinh: " << (sv.gioiTinh ? "Nam" : "Nu") << endl;
    cout << "Ngay sinh: " << sv.ngaysinh.ngay << "/" << sv.ngaysinh.thang << "/" << sv.ngaysinh.nam << ", Dia chi: " << sv.diaChi << endl;
    cout << "Lop: " << sv.lop << ", Khoa: " << sv.khoa << endl;
}

int compare(char a[], char b[]) { //Ham so sanh 2 bien kieu char
    int i = 0;
    while (i < 8) {
        if (a[i] > b[i]) return 1;
        if (a[i] < b[i]) return -1;
        i++;
    }
    return 0; //2 so bang nhau
}

void sortStudent(List &list) { // Ham sap xep sinh vien dung bubble sort
    for (Node *i = list.first; i != nullptr; i = i->link) {
        for (Node *j = i->link; j != nullptr; j = j->link) { //duyet qua tung node trong list, vong 1 bat dau tu node dau tien, vong 2 bat dau node sau i, tim node co sv.mssv nho hon i de thay doi vi tri
            if (compare(i->data.maSV, j->data.maSV) > 0) { //dung ham compare vua viet de so sanh
                sinhVien temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

void printSort(List list) { //Ham in ra danh sach vua sap xep
    Node *current = list.first;
    while (current != nullptr) {
        printStudent(current->data);
        current = current->link;
    }
}

void sameBirth(List list) { //Ham tim va in ra cac sinh vien cung ngay sinh
    bool found = false;
    Node *current = list.first; //duyet qua tung sinh vien trong list
    while (current != nullptr) {
        Node *other = current->link;
        bool sameBirthday = false;
        while (other != nullptr) {
            if (current->data.ngaysinh.ngay == other->data.ngaysinh.ngay &&
                current->data.ngaysinh.thang == other->data.ngaysinh.thang &&
                current->data.ngaysinh.nam == other->data.ngaysinh.nam) {
                if (!sameBirthday) {
                    printStudent(current->data);
                    sameBirthday = true;
                    found = true;
                }
                printStudent(other->data);
            }
            other = other->link;
        }
        current = current->link;
    }
    if (!found) {
        cout << "Khong tim thay sinh vien cung ngay sinh\n";
    }
}

void removeSameBirth(List &list) { //Ham loai bo sinh vien cung ngay sinh
    Node *current = list.first;
    Node *prev = nullptr;

    while (current != nullptr) { //duyet qua tung sinh vien trong list
        Node *innerPrev = current;
        Node *inner = current->link;
        bool duplicateFound = false; //khoi tao bien kiem tra sinh vien trung ngay sinh

        while (inner != nullptr) { //tim sinh vien trung ngay sinh voi current
            if (current->data.ngaysinh.ngay == inner->data.ngaysinh.ngay &&
                current->data.ngaysinh.thang == inner->data.ngaysinh.thang &&
                current->data.ngaysinh.nam == inner->data.ngaysinh.nam) {
                duplicateFound = true; //tim thay sinh vien trung ngay sinh
                Node *toDelete = inner;
                innerPrev->link = inner->link; //loai bo node inner khoi list
                inner = inner->link;
                delete toDelete;
            } else {
                innerPrev = inner;
                inner = inner->link;
            }
        }

        if (duplicateFound) { //xoa node current neu tim thay sinh vien trung ngay sinh
            if (prev == nullptr) { //kiem tra neu current la node dau
                list.first = current->link;
            } else {
                prev->link = current->link;

            }
            Node *toDelete = current;
            current = current->link; //cap nhat current cho node tiep theo
            delete toDelete;
        } else {
            prev = current; //cap nhat prev va current de tiep tuc duyet
            current = current->link;
        }
    }
}

int main() {
    List listSV;
    int n;
    cout << "Nhap so luong sinh vien: ";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        sinhVien sv;
        insertStudent(sv);
        Node *node = new Node{sv, nullptr};
        if (listSV.first == nullptr) {
            listSV.first = listSV.last = node;
        } else {
            listSV.last->link = node;
            listSV.last = node;
        }
    }

    sortStudent(listSV);
    cout << "\nDanh sach SV sau khi sap xep theo MSSV: \n";
    printSort(listSV);
    cout << endl;

    cout << "Cac sinh vien cung ngay sinh: \n";
    sameBirth(listSV);

    cout << "\nLoai bo sinh vien cung ngay sinh...\n";
    removeSameBirth(listSV);
    cout << "Danh sach sinh vien sau khi loai bo sinh vien cung ngay sinh: \n";
    printSort(listSV);

    return 0;
}
