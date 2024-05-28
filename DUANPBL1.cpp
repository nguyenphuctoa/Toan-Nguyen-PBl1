//TK: Toan / Khanh
//MK: 210905 / 071105
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class KhachHang {
protected:
    string ten;
    string soDienThoai;
    int soPhongDat;
public:
    KhachHang(string ten, string soDienThoai, int soPhongDat) : ten(ten), soDienThoai(soDienThoai), soPhongDat(soPhongDat) {}
    virtual ~KhachHang() {}
    string getTen() const {
        return ten;
    }
    string getSoDienThoai() const {
        return soDienThoai;
    }
    int getSoPhongDat() const {
        return soPhongDat;
    }
    virtual void hienThiThongTin() const {
        cout << "Ten: " << ten << endl;
        cout << "So dien thoai: " << soDienThoai << endl;
        cout << "So phong dat: " << soPhongDat << endl;
    }
};

class KhachHangVip : public KhachHang {
private:
    string uuDai;
public:
    KhachHangVip(string ten, string soDienThoai, int soPhongDat, string uuDai)
        : KhachHang(ten, soDienThoai, soPhongDat), uuDai(uuDai) {}
    string getUuDai() const {
        return uuDai;
    }
    void hienThiThongTin() {
        KhachHang::hienThiThongTin();
        cout << "Uu dai: " << uuDai << endl;
    }
};

class KhachSan {
private:
    string tenKhachSan;
    int soPhong;
    vector<int> giaPhong;
    vector<KhachHang*> danhSachKhachHang;
    int tongDoanhThu;
public:
    KhachSan(string ten, int soPhong);
    ~KhachSan();
    void themKhachSan();
    void hienThiThongTin();
    void suaKhachSan();
    void xoaKhachSan();
    void luuDuLieu();
    void docDuLieu();
    void tinhTongDoanhThu();
    void themKhachHang();
    void hienThiDanhSachKhachHang();
    void hienThiDanhSachKhachHangVip();
    void xoaKhachHang();
};

bool dangNhap(string tenDangNhap, string matKhau) {
    if ((tenDangNhap == "Toan" && matKhau == "210905") || (tenDangNhap == "Khanh" && matKhau == "071105")) {
        return true;
    }
    else {
        return false;
    }
}
void print(int n) {
    for (int i = 0; i < n; ++i) cout << "-";
}

KhachSan::KhachSan(string ten, int soPhong) {
    tenKhachSan = ten;
    this->soPhong = soPhong;
    giaPhong.resize(soPhong);
}

KhachSan::~KhachSan() {
    for (KhachHang* kh : danhSachKhachHang) {
        delete kh;
    }
}

void KhachSan::themKhachSan() {
    cout << "Nhap gia phong cho tung loai phong" << endl;
    for (int i = 0; i < soPhong; i++) {
        cout << "Gia phong so " << i + 1 << ": ";
        cin >> giaPhong[i];
    }
    luuDuLieu();
}

void KhachSan::hienThiThongTin() {
    print(42); cout << "\n";
    cout << "| Ten khach san    | " << setw(19) << left << tenKhachSan << " |" << endl;
    cout << "| So luong phong   | " << setw(19) << left << soPhong << " |" << endl;
    cout << "|"; print(18);
    cout << "|"; print(21); cout << "|" << endl;
    cout << "Gia phong tung loai" << endl;
    for (int i = 0; i < soPhong; i++) {
        cout << "Loai " << i + 1 << ": " << giaPhong[i] << endl;
    }
}

void KhachSan::suaKhachSan() {
    cout << "Nhap gia phong moi cho tung loai phong" << endl;
    for (int i = 0; i < soPhong; ++i) {
        cout << "Gia phong loai " << i + 1 << ": ";
        cin >> giaPhong[i];
    }
    luuDuLieu();
}
void KhachSan::xoaKhachSan() {
    int soPhongCanXoa;
    cout << "Nhap so thu tu cua phong can xoa (1-" << soPhong << "): ";
    cin >> soPhongCanXoa;

    if (soPhongCanXoa < 1 || soPhongCanXoa > soPhong) {
        cout << "So phong khong hop le!" << endl;
        return;
    }

    char xacNhan;
    cout << "Ban co chac chan muon xoa phong " << soPhongCanXoa << "?" << endl;
    cout << "(1.Yes/2.No): ";                                          // Xác nh?n v?i ngu?i s? d?ng tru?c khi xóa
    cin >> xacNhan;

    if (xacNhan == '1') {
        giaPhong.erase(giaPhong.begin() + soPhongCanXoa - 1);
        --soPhong;                                                             // Gi?m s? lu?ng phòng

        luuDuLieu();

        cout << "Da xoa phong " << soPhongCanXoa << " thanh cong!" << endl;
    }
    else {
        cout << "Huy thao tac xoa." << endl;
    }
}

void KhachSan::luuDuLieu() {
    ofstream file("khachsan.txt");
    if (!file) {
        cout << "Khong the mo file!" << endl;
        return;
    }

    file << "Ten khach san: " << tenKhachSan << endl;
    file << "So luong phong: " << soPhong << endl;
    for (int i = 0; i < soPhong; i++) {
        file << giaPhong[i] << "  " << endl;
    }
    file << "Tong doanh thu khac san cua ngay hom nay: " << this->tongDoanhThu << endl;
    file << endl;
    file.close();
}

void KhachSan::docDuLieu() {
    ifstream file("khachsan.txt");
    if (!file) {
        cout << "file bi loi!" << endl;
        return;
    }

    file >> tenKhachSan >> soPhong;
    giaPhong.resize(soPhong);
    for (int i = 0; i < soPhong; ++i) {
        file >> giaPhong[i];
    }
    file >> this->tongDoanhThu;
    file.close();
}

void KhachSan::tinhTongDoanhThu() {
    int tongDoanhThu = 0;
    for (const auto& kh : danhSachKhachHang) {
        tongDoanhThu += giaPhong[kh->getSoPhongDat() - 1];
    }
    this->tongDoanhThu = tongDoanhThu;
    cout << "Tong doanh thu cua khach san: " << tongDoanhThu << endl;
    luuDuLieu();
}

void KhachSan::themKhachHang() {
    string ten, soDienThoai;
    int soPhongDat;
    cout << "Nhap ten khach hang: ";
    cin.ignore();
    getline(cin, ten);
    cout << "Nhap so dien thoai: ";
    cin >> soDienThoai;
    cout << "Nhap so phong da dat: ";
    cin >> soPhongDat;

    KhachHang* kh;
    if (giaPhong[soPhongDat - 1] >= 500) {
        kh = new KhachHangVip(ten, soDienThoai, soPhongDat, "Qua Tang Chao Mung");
    }
    else {
        kh = new KhachHang(ten, soDienThoai, soPhongDat);
    }

    danhSachKhachHang.push_back(kh);        // Thêm d?i tu?ng m?i vào vt danh sách
}

void veBang(int doRong, int soCot) {
    for (int i = 0; i < soCot; ++i) {
        cout << "+";
        cout << string(doRong, '-');
    }
    cout << "+" << endl;
}

void cacThongTin(const vector<string>& cols, int doRong) {
    cout << "|";
    for (const auto& col : cols) {
        cout << setw(doRong) << left << col << "|";
    }
    cout << endl;
}

void KhachSan::hienThiDanhSachKhachHang() {
    int doRong = 20;
    int soCot = 3;

    cout << setw(30) << "Danh sach khach hang da dat phong:" << endl;

    veBang(doRong, soCot);
    cacThongTin({ "Ten", "So Dien Thoai", "So Phong Dat" }, doRong);
    veBang(doRong, soCot);

    for (const auto& kh : danhSachKhachHang) {
        cacThongTin({ kh->getTen(), kh->getSoDienThoai(), to_string(kh->getSoPhongDat()) }, doRong);
    }

    veBang(doRong, soCot);
}

void KhachSan::hienThiDanhSachKhachHangVip() {
    int doRong = 20;
    int soCot = 4;

    cout << setw(30) << "Danh sach khach hang VIP:" << endl;

    veBang(doRong, soCot);
    cacThongTin({ "Ten", "So Dien Thoai", "So Phong Dat", "Uu Dai" }, doRong);
    veBang(doRong, soCot);

    for (const auto& kh : danhSachKhachHang) {
        if (KhachHangVip* khVip = dynamic_cast<KhachHangVip*>(kh)) {    
            cacThongTin({ khVip->getTen(), khVip->getSoDienThoai(), to_string(khVip->getSoPhongDat()), khVip->getUuDai() }, doRong);
        }
    }

    veBang(doRong, soCot);
}

void KhachSan::xoaKhachHang() {
    string ten;
    cout << "Nhap ten khach hang can xoa: ";
    cin.ignore();
    getline(cin, ten);

    auto it = remove_if(danhSachKhachHang.begin(), danhSachKhachHang.end(), [ten](KhachHang* kh) {  // remove_if dùng d? tìm ph?n t? trong danh sách khách hàng có tên kh?p v?i tên dã nh?p.
        return kh->getTen() == ten;
        });

    if (it != danhSachKhachHang.end()) {
        delete* it;
        danhSachKhachHang.erase(it, danhSachKhachHang.end());
        cout << "Xoa khach hang thanh cong!" << endl;
    }
    else {
        cout << "Khach hang khong ton tai!" << endl;
    }
}

int main() {
    string pink = "\033[38;5;13m";  // Mã hi?n màu 
    string reset = "\033[0m";       // Mã xoá màu
    string tenDangNhap, matKhau;

    do  {
        cout << setw(37) << internal << "";
        print(46); cout << "-\n";
        cout << setw(37) << char(179) << setw(26) << internal << pink << "Smart Hotel" << reset << setw(21) << internal << " |\n";
        cout << setw(37) << internal << "";
        print(46); cout << "-\n";

        cout << setw(47) << internal << "Tai Khoan :";
        cin >> tenDangNhap;

        cout << setw(47) << internal << "Mat Khau :";
        cin >> matKhau;

        if (!dangNhap(tenDangNhap, matKhau)) {
            cout << setw(50) << "Ten dang nhap hoac mat khau sai. Vui long nhap lai!" << endl;
        }
    } while (!dangNhap(tenDangNhap, matKhau));

    int luaChon;
    KhachSan ks("Khach San THIEN AN", 5);
    ks.docDuLieu();

    system("cls");
    cout << setw(50) << "DANG NHAP THANH CONG!" << endl;
    system("pause");

    do {
        system("cls");
        cout << pink << endl;
        cout << "              MOI BAN LUA CHON               " << "\n";
        cout << "=============================================" << "\n";
        cout << "|                   MENU                    |" << "\n";
        cout << "=============================================" << "\n";
        cout << "|1. Them khach san de quan ly               |" << "\n";
        cout << "|2. Hien thi thong tin khach san            |" << "\n";
        cout << "|3. Them khach hang                         |" << "\n";
        cout << "|4. Hien thi danh sach khach hang dat phong |" << "\n";
        cout << "|5. Sua thong tin khach san                 |" << "\n";
        cout << "|6. Xoa thong tin khach san                 |" << "\n";
        cout << "|7. Xoa thong tin khach hang                |" << "\n";
        cout << "|8. Hien thi danh sach khach hang VIP       |" << "\n";
        cout << "|9. Tinh tong doanh thu                     |" << "\n";
        cout << "|10. Thoat                                  |" << "\n";
        cout << "=============================================" << "\n";
        cout << reset << endl;

        cout << "Chon chuc nang: ";
        cin >> luaChon;

        switch (luaChon) {
        case 1: {
            system("cls");
            string ten;
            int soPhong;
            cout << "Nhap ten khach san: ";
            cin.ignore();
            getline(cin, ten);
            cout << "Nhap so luong phong: ";
            cin >> soPhong;
            ks = KhachSan(ten, soPhong);
            ks.themKhachSan();
            cout << "Them khach san quan ly thanh cong" << endl;
            cin.ignore();
            system("pause");
            break;
        }
        case 2: {
            system("cls");
            cout << "\n----- DANH SACH KHACH SAN ----------------" << endl;
            ks.hienThiThongTin();
            system("pause");
            break;
        }
        case 3: {
            system("cls");
            ks.themKhachHang();
            system("pause");
            break;
        }
        case 4: {
            system("cls");
            ks.hienThiDanhSachKhachHang();
            system("pause");
            break;
        }
        case 5: {
            system("cls");
            ks.suaKhachSan();
            system("pause");
            break;
        }
        case 6: {
            system("cls");
            ks.xoaKhachSan();
            system("pause");
            break;
        }
        case 7: {
            system("cls");
            ks.xoaKhachHang();
            system("pause");
            break;
        }
        case 8: {
            system("cls");
            ks.hienThiDanhSachKhachHangVip();
            system("pause");
            break;
        }
        case 9: {
            system("cls");
            ks.tinhTongDoanhThu();
            system("pause");
            break;
        }
        case 10: {
            system("cls");
            cout << pink;
            cout << "                                                                          " << endl;
            cout << "||||||||||  ||||   ||||    ||||       |||||||  ||||||  ||||||||  |||||||| " << endl;
            cout << "    ||     ||  ||  || ||  || ||       ||    ||   ||    ||           ||    " << endl;
            cout << "    ||    |||||||| ||   ||   ||       |||||||    ||    ||||||       ||    " << endl;
            cout << "    ||    ||    || ||        ||       ||    ||   ||    ||           ||    " << endl;
            cout << "    ||    ||    || ||        ||       |||||||  ||||||  ||||||||     ||    " << endl;
            cout << "                                                                          " << endl;
            cout << reset;
            break;
        }
        default: {
            cout << "Chon sai! Vui long chon lai." << endl;
            break;
        }
        }
    } while (luaChon != 10);

    return 0;
}




