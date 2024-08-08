#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

typedef struct KhachHang {
    char maKH[10];
    char tenKH[50];
    char diaChi[100];
    char soDienThoai[15];
    struct KhachHang* next;
} KhachHang;

typedef struct HangHoa {
    char maHH[10];
    char tenHH[50];
    double donGia;
    int soLuongTon;
    struct HangHoa* next;
} HangHoa;

typedef struct HoaDon {
    char maHD[10];
    char maKH[10];
    char ngayLap[20];
    double tongTien;
    struct HoaDon* next;
} HoaDon;

typedef struct ChiTietHoaDon {
    char maHD[10];
    char maHH[10];
    int soLuong;
    double donGia;
    double thanhTien;
    struct ChiTietHoaDon* next;
} ChiTietHoaDon;

KhachHang* khachHangList = NULL;
HangHoa* hangHoaList = NULL;
HoaDon* hoaDonList = NULL;
ChiTietHoaDon* chiTietHoaDonList = NULL;

int soLuongKhachHang = 0;
int soLuongHangHoa = 0;
int soLuongHoaDon = 0;
int soLuongChiTietHoaDon = 0;

// Thêm vào danh sách
void themVaoDanhSachKhachHang(KhachHang* kh) {
    kh->next = khachHangList;
    khachHangList = kh;
}

void themVaoDanhSachHangHoa(HangHoa* hh) {
    hh->next = hangHoaList;
    hangHoaList = hh;
}

void themVaoDanhSachHoaDon(HoaDon* hd) {
    hd->next = hoaDonList;
    hoaDonList = hd;
}

void themVaoDanhSachChiTietHoaDon(ChiTietHoaDon* cthd) {
    cthd->next = chiTietHoaDonList;
    chiTietHoaDonList = cthd;
}

// Hàm liệt kê hóa đơn theo mã khách hàng
void lietKeHoaDonTheoMaKH(HoaDon* head, const char* maKH) {
    HoaDon* current = head;
    printf("Danh sach hoa don theo Ma KH %s:\n", maKH);
    while (current != NULL) {
        if (strcmp(current->maKH, maKH) == 0) {
            printf("So HD: %s, Ngay Lap: %s, Tong Tien: %.2f\n",
                current->maHD, current->ngayLap, current->tongTien);
        }
        current = current->next;
    }
}


// Ghi vào file
void ghiKhachHang(const char* filename, KhachHang* kh) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Khong the mo file %s\n", filename);
        return;
    }
    fprintf(file, "%s %s %s %s\n", kh->maKH, kh->tenKH, kh->diaChi, kh->soDienThoai);
    fclose(file);
}

//void ghiHangHoa(const char* filename, HangHoa* hh) {
//    FILE* file = fopen(filename, "a");
//    if (file == NULL) {
//        printf("Khong the mo file %s\n", filename);
//        return;
//    }
//    fprintf(file, "%s %s %.2f %d\n", hh->maHH, hh->tenHH, hh->donGia, hh->soLuongTon);
//    fclose(file);
//}

void ghiHangHoa(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Khong the mo file %s\n", filename);
        return;
    }

    HangHoa* current = hangHoaList;
    while (current != NULL) {
        fprintf(file, "%s %s %.2f %d\n", current->maHH, current->tenHH, current->donGia, current->soLuongTon);
        current = current->next;
    }
    fclose(file);
}


void ghiHoaDon(const char* filename, HoaDon* hd) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Khong the mo file %s\n", filename);
        return;
    }
    fprintf(file, "%s %s %s %.2f\n", hd->maHD, hd->maKH, hd->ngayLap, hd->tongTien);
    fclose(file);
}

//void ghiChiTietHoaDon(const char* filename, ChiTietHoaDon* cthd) {
//    FILE* file = fopen(filename, "a");
//    if (file == NULL) {
//        printf("Khong the mo file %s\n", filename);
//        return;
//    }
//    fprintf(file, "%s %s %d %.2f %.2f\n", cthd->maHD, cthd->maHH, cthd->soLuong, cthd->donGia, cthd->thanhTien);
//    fclose(file);
//}


void ghiChiTietHoaDon(const char* filename, ChiTietHoaDon* cthd) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Khong the mo file %s\n", filename);
        return;
    }
    fprintf(file, "%s %s %d %.2f %.2f\n", cthd->maHD, cthd->maHH, cthd->soLuong, cthd->donGia, cthd->thanhTien);
    fclose(file);
}


// Đọc từ file
void docKhachHang(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Khong the mo file %s\n", filename);
        return;
    }

    while (!feof(file)) {
        KhachHang* kh = (KhachHang*)malloc(sizeof(KhachHang));
        if (fscanf(file, "%s %s %s %s\n", kh->maKH, kh->tenKH, kh->diaChi, kh->soDienThoai) != EOF) {
            themVaoDanhSachKhachHang(kh);
        }
        else {
            free(kh);
            break;
        }
    }

    fclose(file);
}

void docHangHoa(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Khong the mo file %s\n", filename);
        return;
    }

    while (!feof(file)) {
        HangHoa* hh = (HangHoa*)malloc(sizeof(HangHoa));
        if (fscanf(file, "%s %s %lf %d\n", hh->maHH, hh->tenHH, &hh->donGia, &hh->soLuongTon) != EOF) {
            themVaoDanhSachHangHoa(hh);
        }
        else {
            free(hh);
            break;
        }
    }

    fclose(file);
}

void docHoaDon(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Khong the mo file %s\n", filename);
        return;
    }

    while (!feof(file)) {
        HoaDon* hd = (HoaDon*)malloc(sizeof(HoaDon));
        if (fscanf(file, "%s %s %s %lf\n", hd->maHD, hd->maKH, hd->ngayLap, &hd->tongTien) != EOF) {
            themVaoDanhSachHoaDon(hd);
        }
        else {
            free(hd);
            break;
        }
    }

    fclose(file);
}

void docChiTietHoaDon(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Khong the mo file %s\n", filename);
        return;
    }

    while (!feof(file)) {
        ChiTietHoaDon* cthd = (ChiTietHoaDon*)malloc(sizeof(ChiTietHoaDon));
        if (fscanf(file, "%s %s %d %lf %lf\n", cthd->maHD, cthd->maHH, &cthd->soLuong, &cthd->donGia, &cthd->thanhTien) != EOF) {
            themVaoDanhSachChiTietHoaDon(cthd);
        }
        else {
            free(cthd);
            break;
        }
    }

    fclose(file);
}

// Hàm kiểm tra tồn tại
int kiemTraKhachHang(const char* maKH) {
    KhachHang* current = khachHangList;
    while (current != NULL) {
        if (strcmp(current->maKH, maKH) == 0) {
            return 1; // Tồn tại
        }
        current = current->next;
    }
    return 0; // Không tồn tại
}

int kiemTraHangHoa(const char* maHH) {
    HangHoa* current = hangHoaList;
    while (current != NULL) {
        if (strcmp(current->maHH, maHH) == 0) {
            return 1; // Tồn tại
        }
        current = current->next;
    }
    return 0; // Không tồn tại
}

int kiemTraHoaDon(const char* maHD) {
    HoaDon* current = hoaDonList;
    while (current != NULL) {
        if (strcmp(current->maHD, maHD) == 0) {
            return 1; // Tồn tại
        }
        current = current->next;
    }
    return 0; // Không tồn tại
}

// Nhập thông tin mới
void nhapThongTinKhachHang() {
    KhachHang* kh = (KhachHang*)malloc(sizeof(KhachHang));
    printf("Nhap ma KH: ");
    scanf("%s", kh->maKH);

    if (kiemTraKhachHang(kh->maKH)) {
        printf("Khach hang da ton tai.\n");
        free(kh);
        return;
    }

    printf("Nhap ten KH: ");
    scanf(" %[^\n]s", kh->tenKH);
    printf("Nhap dia chi: ");
    scanf(" %[^\n]s", kh->diaChi);
    printf("Nhap so dien thoai: ");
    scanf("%s", kh->soDienThoai);

    ghiKhachHang("KhachHang.txt", kh);
    themVaoDanhSachKhachHang(kh);
    printf("Da them khach hang moi.\n");
}
//void nhapHoaDonVaChiTiet() {
//    char maKH[10];
//    printf("Nhap ma KH: ");
//    scanf("%s", maKH);
//
//    if (!kiemTraKhachHang(maKH)) {
//        KhachHang* kh = (KhachHang*)malloc(sizeof(KhachHang));
//        strcpy(kh->maKH, maKH);
//        printf("Nhap ten KH: ");
//        scanf(" %[^\n]s", kh->tenKH);
//        printf("Nhap dia chi: ");
//        scanf(" %[^\n]s", kh->diaChi);
//        printf("Nhap so dien thoai: ");
//        scanf("%s", kh->soDienThoai);
//        themVaoDanhSachKhachHang(kh);
//        ghiKhachHang("KhachHang.txt", kh);
//        printf("Da them khach hang moi.\n");
//    }
//
//    HoaDon* hd = (HoaDon*)malloc(sizeof(HoaDon));
//    printf("Nhap ma HD: ");
//    scanf("%s", hd->maHD);
//
//    if (kiemTraHoaDon(hd->maHD)) {
//        printf("Hoa don da ton tai.\n");
//        free(hd);
//        return;
//    }
//
//    strcpy(hd->maKH, maKH);
//    printf("Nhap ngay lap (YYYY-MM-DD): ");
//    scanf("%s", hd->ngayLap);
//    hd->tongTien = 0.0;
//
//    int soMatHang;
//    printf("Nhap so mat hang: ");
//    scanf("%d", &soMatHang);
//
//    for (int i = 0; i < soMatHang; i++) {
//        ChiTietHoaDon* cthd = (ChiTietHoaDon*)malloc(sizeof(ChiTietHoaDon));
//        strcpy(cthd->maHD, hd->maHD);
//
//        printf("Nhap ma HH: ");
//        scanf("%s", cthd->maHH);
//
//        HangHoa* hh = timHangHoa(cthd->maHH);
//        if (!hh) {
//            printf("Ma HH khong ton tai.\n");
//            free(cthd);
//            continue;
//        }
//
//        printf("Nhap so luong: ");
//        scanf("%d", &cthd->soLuong);
//
//        if (cthd->soLuong > hh->soLuongTon) {
//            printf("So luong khong du. So luong ton: %d\n", hh->soLuongTon);
//            free(cthd);
//            continue;
//        }
//
//        cthd->donGia = hh->donGia;
//        cthd->thanhTien = cthd->soLuong * cthd->donGia;
//        hd->tongTien += cthd->thanhTien;
//
//        hh->soLuongTon -= cthd->soLuong;  // Giảm số lượng tồn kho
//        ghiChiTietHoaDon("ChiTietHoaDon.txt", cthd);
//        themVaoDanhSachChiTietHoaDon(cthd);
//    }
//
//    ghiHoaDon("HoaDon.txt", hd);
//    themVaoDanhSachHoaDon(hd);
//    ghiHangHoa("HangHoa.txt");  // Cập nhật tồn kho vào tệp
//    printf("Da them hoa don moi.\n");
//}


void nhapThongTinHangHoa() {
    HangHoa* hh = (HangHoa*)malloc(sizeof(HangHoa));
    printf("Nhap ma HH: ");
    scanf("%s", hh->maHH);

    if (kiemTraHangHoa(hh->maHH)) {
        printf("Hang hoa da ton tai.\n");
        free(hh);
        return;
    }

    printf("Nhap ten HH: ");
    scanf(" %[^\n]s", hh->tenHH);
    printf("Nhap don gia: ");
    scanf("%lf", &hh->donGia);
    printf("Nhap so luong ton: ");
    scanf("%d", &hh->soLuongTon);

    ghiHangHoa("HangHoa.txt");
    themVaoDanhSachHangHoa(hh);
    printf("Da them hang hoa moi.\n");
}

void nhapThongTinKhachHangMoi(char* maKH) {
    KhachHang* kh = (KhachHang*)malloc(sizeof(KhachHang));

    if (maKH == NULL) {
        printf("Nhap ma KH: ");
        scanf("%s", kh->maKH);
    }
    else {
        strcpy(kh->maKH, maKH);
    }

    if (kiemTraKhachHang(kh->maKH)) {
        printf("Khach hang da ton tai.\n");
        free(kh);
        return;
    }

    printf("Nhap ten KH: ");
    scanf(" %[^\n]s", kh->tenKH);
    printf("Nhap dia chi: ");
    scanf(" %[^\n]s", kh->diaChi);
    printf("Nhap so dien thoai: ");
    scanf("%s", kh->soDienThoai);

    ghiKhachHang("KhachHang.txt", kh);
    themVaoDanhSachKhachHang(kh);
    printf("Da them khach hang moi.\n");


}

void nhapThongTinHoaDon() {
    HoaDon* hd = (HoaDon*)malloc(sizeof(HoaDon));
    printf("Nhap ma HD: ");
    scanf("%s", hd->maHD);

    if (kiemTraHoaDon(hd->maHD)) {
        printf("Hoa don da ton tai.\n");
        free(hd);
        return;
    }

    printf("Nhap ma KH: ");
    scanf("%s", hd->maKH);

    // Kiểm tra khách hàng, nếu không tồn tại, thêm khách hàng mới
    if (!kiemTraKhachHang(hd->maKH)) {
        printf("Ma KH khong ton tai. Dang tao khach hang moi.\n");
        nhapThongTinKhachHangMoi(hd->maKH);
    }

    printf("Nhap ngay lap (YYYY-MM-DD): ");
    scanf("%s", hd->ngayLap);

    // Tính tổng tiền
    hd->tongTien = 0.0;
    ChiTietHoaDon* cthd = chiTietHoaDonList;
    while (cthd != NULL) {
        if (strcmp(cthd->maHD, hd->maHD) == 0) {
            hd->tongTien += cthd->thanhTien;
        }
        cthd = cthd->next;
    }

    ghiHoaDon("HoaDon.txt", hd);
    themVaoDanhSachHoaDon(hd);
    printf("Da them hoa don moi.\n");


}



void nhapThongTinChiTietHoaDon() {
    ChiTietHoaDon* cthd = (ChiTietHoaDon*)malloc(sizeof(ChiTietHoaDon));
    printf("Nhap ma HD: ");
    scanf("%s", cthd->maHD);

    if (!kiemTraHoaDon(cthd->maHD)) {
        printf("Ma HD khong ton tai.\n");
        free(cthd);
        return;
    }

    printf("Nhap ma HH: ");
    scanf("%s", cthd->maHH);
    if (!kiemTraHangHoa(cthd->maHH)) {
        printf("Ma HH khong ton tai.\n");
        free(cthd);
        return;
    }

    printf("Nhap so luong: ");
    scanf("%d", &cthd->soLuong);
    printf("Nhap don gia: ");
    scanf("%lf", &cthd->donGia);

    cthd->thanhTien = cthd->soLuong * cthd->donGia;

    ghiChiTietHoaDon("ChiTietHoaDon.txt", cthd);
    themVaoDanhSachChiTietHoaDon(cthd);
    printf("Da them chi tiet hoa don moi.\n");
}



// In thông tin
void inKhachHang() {
    printf("********************************************************************************************************************************\n");
    printf("| Ma KH       | Ten KH                        | Dia Chi                                      | So Dien Thoai                   |\n");
    printf("********************************************************************************************************************************\n");

    KhachHang* current = khachHangList;
    while (current != NULL) {
        printf("| %-10s | %-30s | %-45s | %-30s |\n",
            current->maKH, current->tenKH, current->diaChi, current->soDienThoai);
        current = current->next;
    }


    printf("********************************************************************************************************************************\n");
}

void inHangHoa() {
    printf("+----------+-------------------------------+---------------+--------------------+\n");
    printf("| Ma HH    | Ten HH                        | Don Gia       | So Luong Ton       |\n");
    printf("+----------+-------------------------------+---------------+--------------------+\n");

    HangHoa* current = hangHoaList;
    while (current != NULL) {
        printf("| %-8s | %-30s | %9.2f | %19d |\n",
            current->maHH, current->tenHH, current->donGia, current->soLuongTon);
        current = current->next;
    }

    printf("+----------+-------------------------------+-----------+------------------------+\n");
}

void inHoaDon() {
    printf("+----------+----------+------------+--------------+\n");
    printf("| Ma HD    | Ma KH    | Ngay Lap   | Tong Tien    |\n");
    printf("+----------+----------+------------+--------------+\n");

    HoaDon* current = hoaDonList;
    while (current != NULL) {
        printf("| %-8s | %-8s | %-10s | %12.2f |\n",
            current->maHD, current->maKH, current->ngayLap, current->tongTien);
        current = current->next;
    }

    printf("+----------+----------+------------+--------------+\n");
}

void inChiTietHoaDon() {
    printf("+----------+----------+-----------+-----------+-------------+\n");
    printf("| Ma HD    | Ma HH    | So Luong  | Don Gia   | Thanh Tien  |\n");
    printf("+----------+----------+-----------+-----------+-------------+\n");

    ChiTietHoaDon* current = chiTietHoaDonList;
    while (current != NULL) {
        printf("| %-8s | %-8s | %9d | %9.2f | %11.2f |\n",
            current->maHD, current->maHH, current->soLuong, current->donGia, current->thanhTien);
        current = current->next;
    }

    printf("+----------+----------+-----------+-----------+-------------+\n");
}

HangHoa* timHangHoa(const char* maHH) {
    HangHoa* current = hangHoaList;
    while (current != NULL) {
        if (strcmp(current->maHH, maHH) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

//tìm hóa đơn theo mã hóa đơn
HoaDon* timHoaDon(const char* maHD) {
    HoaDon* current = hoaDonList;
    while (current != NULL) {
        if (strcmp(current->maHD, maHD) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

ChiTietHoaDon* timChiTietHoaDon(const char* maHD, const char* maHH) {
    ChiTietHoaDon* current = chiTietHoaDonList;
    while (current != NULL) {
        if (strcmp(current->maHD, maHD) == 0 && strcmp(current->maHH, maHH) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

//SỬA FILE
void suaThongTinKhachHang(const char* filename) {
    KhachHang* current = khachHangList;
    char maKH[10];
    int found = 0;

    printf("Nhap ma KH can sua: ");
    scanf("%s", maKH);

    while (current != NULL) {
        if (strcmp(current->maKH, maKH) == 0) {
            found = 1;
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("Khach hang voi ma KH %s khong ton tai.\n", maKH);
        return;
    }

    // Nhập thông tin mới
    printf("Nhap ten KH moi: ");
    scanf(" %[^\n]s", current->tenKH);
    printf("Nhap dia chi moi: ");
    scanf(" %[^\n]s", current->diaChi);
    printf("Nhap so dien thoai moi: ");
    scanf("%s", current->soDienThoai);

    // Ghi lại toàn bộ danh sách vào file
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Khong the mo file %s\n", filename);
        return;
    }

    current = khachHangList;
    while (current != NULL) {
        fprintf(file, "%s %s %s %s\n", current->maKH, current->tenKH, current->diaChi, current->soDienThoai);
        current = current->next;
    }

    fclose(file);
    printf("Da cap nhat thong tin khach hang.\n");
}

void suaHangHoa(const char* maHH) {
    HangHoa* hh = timHangHoa(maHH);
    if (hh == NULL) {
        printf("Hang hoa voi ma %s khong ton tai.\n", maHH);
        return;
    }

    printf("Nhap thong tin moi cho hang hoa:\n");
    printf("Ten hang hoa: ");
    scanf(" %[^\n]%*c", hh->tenHH);
    printf("Gia: ");
    scanf("%lf", &hh->donGia);
    printf("So luong ton kho: ");
    scanf("%d", &hh->soLuongTon);

    // Ghi lại thông tin vào file
    FILE* file = fopen("hanghoa.txt", "w");
    if (file == NULL) {
        printf("Khong the mo file hanghoa.txt\n");
        return;
    }
    HangHoa* current = hangHoaList;
    while (current != NULL) {
        fprintf(file, "%s %s %.2f %d\n", current->maHH, current->tenHH, current->donGia, current->soLuongTon);
        current = current->next;
    }
    fclose(file);
}

void suaHoaDon(const char* maHD) {
    HoaDon* hd = timHoaDon(maHD);
    if (hd == NULL) {
        printf("Hoa don voi ma %s khong ton tai.\n", maHD);
        return;
    }

    printf("Nhap thong tin moi cho hoa don:\n");
    printf("Ma khach hang (maKH): ");
    scanf("%s", hd->maKH);
    printf("Ngay lap (yyyy-mm-dd): ");
    scanf("%s", hd->ngayLap);  // Nhập ngày lập dưới dạng chuỗi
    printf("Tong tien: ");
    scanf("%lf", &hd->tongTien);

    // Cập nhật vào file
    FILE* file = fopen("hoadon.txt", "w");
    if (file == NULL) {
        printf("Khong the mo file hoadon.txt\n");
        return;
    }
    HoaDon* current = hoaDonList;
    while (current != NULL) {
        fprintf(file, "%s %s %s %.2f\n", current->maHD, current->maKH, current->ngayLap, current->tongTien);
        current = current->next;
    }
    fclose(file);
}

void suaChiTietHoaDon(const char* maHD, const char* maHH) {
    ChiTietHoaDon* cthd = timChiTietHoaDon(maHD, maHH);
    if (cthd == NULL) {
        printf("Chi tiet hoa don voi ma hoa don %s va ma hang hoa %s khong ton tai.\n", maHD, maHH);
        return;
    }

    printf("Nhap thong tin moi cho chi tiet hoa don:\n");
    printf("So luong: ");
    scanf("%d", &cthd->soLuong);
    printf("Don gia: ");
    scanf("%lf", &cthd->donGia);
    cthd->thanhTien = cthd->soLuong * cthd->donGia;

    // Ghi lại thông tin vào file
    FILE* file = fopen("chitiethoadon.txt", "w");
    if (file == NULL) {
        printf("Khong the mo file chitiethoadon.txt\n");
        return;
    }
    ChiTietHoaDon* current = chiTietHoaDonList;
    while (current != NULL) {
        fprintf(file, "%s %s %d %.2f %.2f\n", current->maHD, current->maHH, current->soLuong, current->donGia, current->thanhTien);
        current = current->next;
    }
    fclose(file);
}

//XÓA FILE
void xoaKhachHang(const char* maKH) {
    KhachHang* current = khachHangList;
    KhachHang* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->maKH, maKH) == 0) {
            if (prev == NULL) {  // Xóa phần tử đầu danh sách
                khachHangList = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current);
            printf("Da xoa khach hang voi ma KH: %s\n", maKH);
            // Cập nhật lại file
            FILE* file = fopen("KhachHang.txt", "w");
            if (file == NULL) {
                printf("Khong the mo file KhachHang.txt\n");
                return;
            }
            current = khachHangList;
            while (current != NULL) {
                fprintf(file, "%s %s %s %s\n", current->maKH, current->tenKH, current->diaChi, current->soDienThoai);
                current = current->next;
            }
            fclose(file);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Khach hang voi ma KH %s khong ton tai.\n", maKH);
}

void xoaHangHoa(const char* maHH) {
    HangHoa* current = hangHoaList;
    HangHoa* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->maHH, maHH) == 0) {
            if (prev == NULL) {  // Xóa phần tử đầu danh sách
                hangHoaList = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current);
            printf("Da xoa hang hoa voi ma HH: %s\n", maHH);
            // Cập nhật lại file
            FILE* file = fopen("HangHoa.txt", "w");
            if (file == NULL) {
                printf("Khong the mo file HangHoa.txt\n");
                return;
            }
            current = hangHoaList;
            while (current != NULL) {
                fprintf(file, "%s %s %.2f %d\n", current->maHH, current->tenHH, current->donGia, current->soLuongTon);
                current = current->next;
            }
            fclose(file);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Hang hoa voi ma HH %s khong ton tai.\n", maHH);
}

void xoaHoaDon(const char* maHD) {
    HoaDon* current = hoaDonList;
    HoaDon* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->maHD, maHD) == 0) {
            if (prev == NULL) {  // Xóa phần tử đầu danh sách
                hoaDonList = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current);

            // Xóa các chi tiết hóa đơn liên quan
            ChiTietHoaDon* cthd = chiTietHoaDonList;
            ChiTietHoaDon* cthdPrev = NULL;
            while (cthd != NULL) {
                if (strcmp(cthd->maHD, maHD) == 0) {
                    if (cthdPrev == NULL) {  // Xóa phần tử đầu danh sách chi tiết hóa đơn
                        chiTietHoaDonList = cthd->next;
                    }
                    else {
                        cthdPrev->next = cthd->next;
                    }
                    free(cthd);
                    cthd = (cthdPrev == NULL) ? chiTietHoaDonList : cthdPrev->next;
                }
                else {
                    cthdPrev = cthd;
                    cthd = cthd->next;
                }
            }

            printf("Da xoa hoa don voi ma HD: %s\n", maHD);
            // Cập nhật lại file
            FILE* file = fopen("HoaDon.txt", "w");
            if (file == NULL) {
                printf("Khong the mo file HoaDon.txt\n");
                return;
            }
            current = hoaDonList;
            while (current != NULL) {
                fprintf(file, "%s %s %s %.2f\n", current->maHD, current->maKH, current->ngayLap, current->tongTien);
                current = current->next;
            }
            fclose(file);

            file = fopen("ChiTietHoaDon.txt", "w");
            if (file == NULL) {
                printf("Khong the mo file ChiTietHoaDon.txt\n");
                return;
            }
            cthd = chiTietHoaDonList;
            while (cthd != NULL) {
                fprintf(file, "%s %s %d %.2f %.2f\n", cthd->maHD, cthd->maHH, cthd->soLuong, cthd->donGia, cthd->thanhTien);
                cthd = cthd->next;
            }
            fclose(file);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Hoa don voi ma HD %s khong ton tai.\n", maHD);
}

void xoaChiTietHoaDon(const char* maHD, const char* maHH) {
    ChiTietHoaDon* current = chiTietHoaDonList;
    ChiTietHoaDon* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->maHD, maHD) == 0 && strcmp(current->maHH, maHH) == 0) {
            if (prev == NULL) {  // Xóa phần tử đầu danh sách
                chiTietHoaDonList = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current);
            printf("Da xoa chi tiet hoa don voi ma HD: %s va ma HH: %s\n", maHD, maHH);
            // Cập nhật lại file
            FILE* file = fopen("ChiTietHoaDon.txt", "w");
            if (file == NULL) {
                printf("Khong the mo file ChiTietHoaDon.txt\n");
                return;
            }
            current = chiTietHoaDonList;
            while (current != NULL) {
                fprintf(file, "%s %s %d %.2f %.2f\n", current->maHD, current->maHH, current->soLuong, current->donGia, current->thanhTien);
                current = current->next;
            }
            fclose(file);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Chi tiet hoa don voi ma HD %s va ma HH %s khong ton tai.\n", maHD, maHH);
}

//Sắp xếp các Hóa đơn giảm dần theo Tổng tiền.
void sapXepHoaDonGiamDanTheoTongTien() {
    if (hoaDonList == NULL || hoaDonList->next == NULL) {
        return;
    }

    HoaDon* i;
    HoaDon* j;
    double tempTongTien;
    char tempMaHD[10];
    char tempMaKH[10];
    char tempNgayLap[20];

    for (i = hoaDonList; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->tongTien < j->tongTien) {
                // Hoán đổi tổng tiền
                tempTongTien = i->tongTien;
                i->tongTien = j->tongTien;
                j->tongTien = tempTongTien;

                // Hoán đổi mã hóa đơn
                strcpy(tempMaHD, i->maHD);
                strcpy(i->maHD, j->maHD);
                strcpy(j->maHD, tempMaHD);

                // Hoán đổi mã khách hàng
                strcpy(tempMaKH, i->maKH);
                strcpy(i->maKH, j->maKH);
                strcpy(j->maKH, tempMaKH);

                // Hoán đổi ngày lập
                strcpy(tempNgayLap, i->ngayLap);
                strcpy(i->ngayLap, j->ngayLap);
                strcpy(j->ngayLap, tempNgayLap);
            }
        }
    }
}

//Sắp xếp các Hóa đơn tăng dần theo Mã khách hàng.
void sapXepHoaDonTangDanTheoMaKH() {
    if (hoaDonList == NULL || hoaDonList->next == NULL) {
        return;
    }

    HoaDon* i;
    HoaDon* j;
    char tempMaHD[10];
    char tempMaKH[10];
    char tempNgayLap[20];
    double tempTongTien;

    for (i = hoaDonList; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->maKH, j->maKH) > 0) {
                // Hoán đổi mã hóa đơn
                strcpy(tempMaHD, i->maHD);
                strcpy(i->maHD, j->maHD);
                strcpy(j->maHD, tempMaHD);

                // Hoán đổi mã khách hàng
                strcpy(tempMaKH, i->maKH);
                strcpy(i->maKH, j->maKH);
                strcpy(j->maKH, tempMaKH);

                // Hoán đổi ngày lập
                strcpy(tempNgayLap, i->ngayLap);
                strcpy(i->ngayLap, j->ngayLap);
                strcpy(j->ngayLap, tempNgayLap);

                // Hoán đổi tổng tiền
                tempTongTien = i->tongTien;
                i->tongTien = j->tongTien;
                j->tongTien = tempTongTien;
            }
        }
    }
}

// in hóa đơn có tổng tiền lớn nhất
void inHoaDonTongTienLonNhat() {
    if (hoaDonList == NULL) {
        printf("Khong co hoa don nao trong danh sach.\n");
        return;
    }

    HoaDon* current = hoaDonList;
    HoaDon* hoaDonMax = current;

    while (current != NULL) {
        if (current->tongTien > hoaDonMax->tongTien) {
            hoaDonMax = current;
        }
        current = current->next;
    }

    printf("Hoa don co tong tien lon nhat:\n");
    printf("+----------+----------+------------+--------------+\n");
    printf("| Ma HD    | Ma KH    | Ngay Lap   | Tong Tien    |\n");
    printf("+----------+----------+------------+--------------+\n");
    printf("| %-8s | %-8s | %-10s | %12.2f |\n",
        hoaDonMax->maHD, hoaDonMax->maKH, hoaDonMax->ngayLap, hoaDonMax->tongTien);
    printf("+----------+----------+------------+--------------+\n");
}

// Tìm hóa đơn và chi tiết hóa đơn theo mã
void timHoaDonVaChiTiet(const char* maHD) {
    HoaDon* hd = hoaDonList;
    while (hd != NULL) {
        if (strcmp(hd->maHD, maHD) == 0) {
            printf("Hoa Don:\n");
            printf("Ma HD: %s, Ma KH: %s, Ngay Lap: %s, Tong Tien: %.2f\n",
                hd->maHD, hd->maKH, hd->ngayLap, hd->tongTien);
            printf("Chi Tiet Hoa Don:\n");

            ChiTietHoaDon* cthd = chiTietHoaDonList;
            while (cthd != NULL) {
                if (strcmp(cthd->maHD, maHD) == 0) {
                    printf("Ma HH: %s, So Luong: %d, Don Gia: %.2f, Thanh Tien: %.2f\n",
                        cthd->maHH, cthd->soLuong, cthd->donGia, cthd->thanhTien);
                }
                cthd = cthd->next;
            }
            return;
        }
        hd = hd->next;
    }
    printf("Khong tim thay hoa don voi ma HD: %s\n", maHD);
}

// In hóa đơn theo mã khách hàng
void inHoaDonTheoMaKH(const char* maKH) {
    HoaDon* hd = hoaDonList;
    while (hd != NULL) {
        if (strcmp(hd->maKH, maKH) == 0) {
            printf("Hoa Don:\n");
            printf("Ma HD: %s, Ngay Lap: %s, Tong Tien: %.2f\n",
                hd->maHD, hd->ngayLap, hd->tongTien);
        }
        hd = hd->next;
    }
}

// Thống kê doanh thu
void thongKeDoanhThuTheoNgay(const char* ngay) {
    HoaDon* hd = hoaDonList;
    double tongTien = 0.0;

    while (hd != NULL) {
        if (strcmp(hd->ngayLap, ngay) == 0) {
            tongTien += hd->tongTien;
        }
        hd = hd->next;
    }

    printf("Doanh thu ngay %s: %.2f\n", ngay, tongTien);
}

void thongKeDoanhThuTheoThang(const char* thang) {
    HoaDon* hd = hoaDonList;
    double tongTien = 0.0;

    while (hd != NULL) {
        if (strncmp(hd->ngayLap, thang, 7) == 0) { // Giả định định dạng ngày là YYYY-MM-DD
            tongTien += hd->tongTien;
        }
        hd = hd->next;
    }

    printf("Doanh thu thang %s: %.2f\n", thang, tongTien);
}

void thongKeDoanhThuTheoQuy(int quy, int nam) {
    HoaDon* hd = hoaDonList;
    double tongTien = 0.0;
    int thangBatDau, thangKetThuc;

    switch (quy) {
    case 1: thangBatDau = 1; thangKetThuc = 3; break;
    case 2: thangBatDau = 4; thangKetThuc = 6; break;
    case 3: thangBatDau = 7; thangKetThuc = 9; break;
    case 4: thangBatDau = 10; thangKetThuc = 12; break;
    default: printf("Quy khong hop le.\n"); return;
    }

    char thang[8];
    for (int i = thangBatDau; i <= thangKetThuc; i++) {
        snprintf(thang, sizeof(thang), "%d-%02d", nam, i);
        while (hd != NULL) {
            if (strncmp(hd->ngayLap, thang, 7) == 0) {
                tongTien += hd->tongTien;
            }
            hd = hd->next;
        }
    }

    printf("Doanh thu quy %d nam %d: %.2f\n", quy, nam, tongTien);
}

void thongKeDoanhThuTheoNam(int nam) {
    HoaDon* hd = hoaDonList;
    double tongTien = 0.0;
    char namStr[5];

    snprintf(namStr, sizeof(namStr), "%d", nam);
    while (hd != NULL) {
        if (strncmp(hd->ngayLap, namStr, 4) == 0) {
            tongTien += hd->tongTien;
        }
        hd = hd->next;
    }

    printf("Doanh thu nam %d: %.2f\n", nam, tongTien);
}

int main() {
    int chon;
    char maHD[10], maKH[10], ngay[20], thang[8], maHH[10];
    int quy, nam;

    // Doc du lieu tu file
    docKhachHang("KhachHang.txt");
    docHangHoa("HangHoa.txt");
    docHoaDon("HoaDon.txt");
    docChiTietHoaDon("ChiTietHoaDon.txt");

    while (1) {
        printf("  ++====================================================================++\n");
        printf("  ||                          LUA CHON CHUONG TRINH                     ||\n");
        printf("  ||********************************************************************||\n");
        printf("  ||             1. Xem va cap nhat thong tin                           ||\n");
        printf("  ||             2. Them thong tin hang hoa                             ||\n");
        printf("  ||             3. Them hoa don va chi tiet hoa don                    ||\n");
        printf("  ||             4. Sap xep hoa don                                     ||\n");
        printf("  ||             5. Tim kiem hoa don                                    ||\n");
        printf("  ||             6. Liet ke hoa don theo ma khach hang                  ||\n");
        printf("  ||             7. Thong tin cac hoa don co tong tien lon nhat         ||\n");
        printf("  ||             8. Thong ke doanh thu theo ngay                        ||\n");
        printf("  ||             9. Thong ke doanh thu theo thang                       ||\n");
        printf("  ||             10. Thong ke doanh thu theo quy                        ||\n");
        printf("  ||             11. Thong ke doanh thu theo nam                        ||\n");
        printf("  ||             0. Thoat                                               ||\n");
        printf("  ++====================================================================++\n");
        printf("Chon mot so (0-11): ");
        scanf("%d", &chon);

        switch (chon) {
        case 1:
            while (1) {
                printf("+====================================================================+\n");
                printf("|                             XEM THONG TIN                          |\n");
                printf("+====================================================================+\n");
                printf("|                   1. Xem thong tin khach hang                      |\n");
                printf("|                   2. Xem thong tin hang hoa                        |\n");
                printf("|                   3. Xem thong tin hoa don                         |\n");
                printf("|                   4. Xem thong tin chi tiet hoa don                |\n");
                printf("|                   0. Tro ve menu chinh                             |\n");
                printf("+====================================================================+\n");
                printf("Chon mot so (0-4): ");
                scanf("%d", &chon);
                switch (chon) {
                case 1:
                    inKhachHang();
                    while (1) {
                        printf("+============================================+\n");
                        printf("|               CAP NHAT KHACH HANG          |\n");
                        printf("+============================================+\n");
                        printf("|                1. Them                     |\n");
                        printf("|                2. Xoa                      |\n");
                        printf("|                3. Sua                      |\n");
                        printf("|                0. Tro ve menu chinh        |\n");
                        printf("+============================================+\n");
                        printf("Chon mot so (0-3): ");
                        scanf("%d", &chon);
                        switch (chon) {
                        case 1:
                            nhapThongTinKhachHang();
                            inKhachHang();
                            break;
                        case 2:
                            printf("Nhap ma KH can xoa: ");
                            scanf("%s", maKH);
                            xoaKhachHang(maKH);
                            inKhachHang();
                            break;
                        case 3:
                            suaThongTinKhachHang("KhachHang.txt");
                            inKhachHang();
                            break;
                        case 0:
                            goto mainMenu;
                        default:
                            printf("Chon khong hop le. Vui long chon tu 0 den 3.\n");
                        }
                    }
                case 2:
                    inHangHoa();
                    while (1) {
                        printf("+============================================+\n");
                        printf("|               CAP NHAT HANG HOA            |\n");
                        printf("+============================================+\n");
                        printf("|                1. Them                     |\n");
                        printf("|                2. Xoa                      |\n");
                        printf("|                3. Sua                      |\n");
                        printf("|                0. Tro ve menu chinh        |\n");
                        printf("+============================================+\n");
                        printf("Chon mot so (0-3): ");
                        scanf("%d", &chon);
                        switch (chon) {
                        case 1:
                            nhapThongTinHangHoa();
                            inHangHoa();
                            break;
                        case 2:
                            printf("Nhap ma HH can xoa: ");
                            scanf("%s", maHH);
                            xoaHangHoa(maHH);
                            inHangHoa();
                            break;
                        case 3:
                            printf("Nhap ma hang hoa can sua: ");
                            scanf("%s", maHH);
                            suaHangHoa(maHH);
                            inHangHoa();
                            break;
                        case 0:
                            goto mainMenu;
                        default:
                            printf("Chon khong hop le. Vui long chon tu 0 den 3.\n");
                        }
                    }
                case 3:
                    inHoaDon();
                    while (1) {
                        printf("+============================================+\n");
                        printf("|               CAP NHAT HOA DON             |\n");
                        printf("+============================================+\n");
                        printf("|                1. Them                     |\n");
                        printf("|                2. Xoa                      |\n");
                        printf("|                3. Sua                      |\n");
                        printf("|                0. Tro ve menu chinh        |\n");
                        printf("+============================================+\n");
                        printf("Chon mot so (0-3): ");
                        scanf("%d", &chon);
                        switch (chon) {
                        case 1:
                            nhapThongTinHoaDon();
                            inHoaDon();
                            break;
                        case 2:
                            printf("Nhap ma HD can xoa: ");
                            scanf("%s", maHD);
                            xoaHoaDon(maHD);
                            inHoaDon();
                            break;
                        case 3:
                            printf("Nhap ma hoa don can sua: ");
                            scanf("%s", maHD);
                            suaHoaDon(maHD);
                            inHoaDon();
                            break;
                        case 0:
                            goto mainMenu;
                        default:
                            printf("Chon khong hop le. Vui long chon tu 0 den 3.\n");
                        }
                    }
                case 4:
                    inChiTietHoaDon();
                    while (1) {
                        printf("+============================================+\n");
                        printf("|           CAP NHAT CHI TIET HOA DON        |\n");
                        printf("+============================================+\n");
                        printf("|                1. Them                     |\n");
                        printf("|                2. Xoa                      |\n");
                        printf("|                3. Sua                      |\n");
                        printf("|                0. Tro ve menu chinh        |\n");
                        printf("+============================================+\n");
                        printf("Chon mot so (0-3): ");
                        scanf("%d", &chon);
                        switch (chon) {
                        case 1:
                            nhapThongTinChiTietHoaDon();
                            inChiTietHoaDon();
                            break;
                        case 2:
                            printf("Nhap ma HD can xoa: ");
                            scanf("%s", maHD);
                            printf("Nhap ma HH can xoa: ");
                            scanf("%s", maHH);
                            xoaChiTietHoaDon(maHD, maHH);
                            inChiTietHoaDon();
                            break;
                        case 3:
                            printf("Nhap ma hoa don can sua: ");
                            scanf("%s", maHD);
                            printf("Nhap ma hang hoa can sua: ");
                            scanf("%s", maHH);
                            suaChiTietHoaDon(maHD, maHH);
                            inChiTietHoaDon();
                            break;
                        case 0:
                            goto mainMenu;
                        default:
                            printf("Chon khong hop le. Vui long chon tu 0 den 3.\n");
                        }
                    }
                case 0:
                    goto mainMenu;
                default:
                    printf("Chon khong hop le. Vui long chon tu 0 den 4.\n");
                }
            }
        case 2:
            printf("Nhap thong tin hang hoa moi:\n");
            nhapThongTinHangHoa();
            inHangHoa();
            break;
        case 3:
            printf("Nhap thong tin hoa don moi:\n");
            nhapThongTinHoaDon();
            /*nhapThongTinHoaDon();*/
            printf("Nhap thong tin chi tiet hoa don:\n");
            nhapThongTinChiTietHoaDon();
            /*nhapHoaDonVaChiTiet();*/
            inHoaDon();
            inChiTietHoaDon();
           
            break;
        case 4:
            printf("Sap xep hoa don theo:\n");
            printf("1. Tong tien giam dan\n");
            printf("2. Ma khach hang tang dan\n");
            printf("Chon mot so (1-2): ");
            scanf("%d", &chon);
            switch (chon) {
            case 1:
                sapXepHoaDonGiamDanTheoTongTien();
                inHoaDon();
                break;
            case 2:
                sapXepHoaDonTangDanTheoMaKH();
                inHoaDon();
                break;
            default:
                printf("Chon khong hop le. Vui long chon tu 1 den 2.\n");
            }
            break;
        case 5:
            printf("Nhap ma hoa don can tim: ");
            scanf("%s", maHD);
            timHoaDon(maHD);
            break;
        case 6:
            printf("Nhap ma khach hang can liet ke hoa don: ");
            scanf("%s", maKH);
            lietKeHoaDonTheoMaKH(hoaDonList, maKH);
            break;
        case 7:
            inHoaDonTongTienLonNhat();
            break;
        case 8:
            printf("Nhap ngay can thong ke: ");
            scanf("%s", ngay);
            thongKeDoanhThuTheoNgay(ngay);
            break;
        case 9:
            printf("Nhap thang can thong ke (yyyy-mm): ");
            scanf("%s", thang);
            thongKeDoanhThuTheoThang(thang);
            break;
        case 10:
            printf("Nhap quy can thong ke: ");
            scanf("%d", &quy);
            printf("Nhap nam: ");
            scanf("%d", &nam);
            thongKeDoanhThuTheoQuy(quy, nam);
            break;
        case 11:
            printf("Nhap nam can thong ke: ");
            scanf("%d", &nam);
            thongKeDoanhThuTheoNam(nam);
            break;
        case 0:
            printf("Ket thuc chuong trinh.\n");
            exit(0);
        default:
            printf("Chon khong hop le. Vui long chon tu 0 den 11.\n");
        }
    mainMenu:;
    }
    return 0;
}
