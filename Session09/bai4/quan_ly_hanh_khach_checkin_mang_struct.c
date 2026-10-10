#include <stdio.h>
#include <string.h>

#define MAX_HANH_KHACH 100

struct HanhKhach {
    char maPNR[15];
    char hoTen[50];
    char hangVe[15];
    float canNangHanhLy;
    float phiHanhLy;
};

int main(void) {
    struct HanhKhach danhSach[MAX_HANH_KHACH];
    int soLuong = 0;
    int choice;
    int i;
    int foundIndex;
    char searchPNR[15];
    float kgMienPhi;
    float kgVuot;
    float tongPhi;
    int countBusiness;
    size_t len;

    do {
        printf("\n=== HE THONG CHECK-IN HANG KHONG ===\n");
        printf("1. Them hanh khach check-in\n");
        printf("2. Hien thi danh sach hanh khach\n");
        printf("3. Cap nhat hanh ly theo ma PNR\n");
        printf("4. Thong ke chuyen bay\n");
        printf("5. Thoat\n");
        printf("Lua chon cua ban: ");

        if (scanf("%d", &choice) != 1) {
            printf("Lua chon khong hop le! Vui long nhap so tu 1 den 5.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                if (soLuong >= MAX_HANH_KHACH) {
                    printf("Bo nho day, khong the them hanh khach!\n");
                    break;
                }

                printf("\nNhap ma PNR: ");
                scanf("%14s", danhSach[soLuong].maPNR);
                while (getchar() != '\n');

                printf("Nhap ho ten: ");
                fgets(danhSach[soLuong].hoTen, sizeof(danhSach[soLuong].hoTen), stdin);
                len = strlen(danhSach[soLuong].hoTen);
                if (len > 0 && danhSach[soLuong].hoTen[len - 1] == '\n') {
                    danhSach[soLuong].hoTen[len - 1] = '\0';
                }

                printf("Nhap hang ve (Business/Deluxe/Eco): ");
                scanf("%14s", danhSach[soLuong].hangVe);
                while (getchar() != '\n');

                printf("Nhap so kg hanh ly ky gui: ");
                while (scanf("%f", &danhSach[soLuong].canNangHanhLy) != 1 || danhSach[soLuong].canNangHanhLy < 0.0f) {
                    printf("Khoi luong khong hop le! Nhap lai (>= 0): ");
                    while (getchar() != '\n');
                }
                while (getchar() != '\n');

                if (strcmp(danhSach[soLuong].hangVe, "Business") == 0) {
                    kgMienPhi = 30.0f;
                } else if (strcmp(danhSach[soLuong].hangVe, "Deluxe") == 0) {
                    kgMienPhi = 20.0f;
                } else {
                    kgMienPhi = 0.0f;
                }

                if (danhSach[soLuong].canNangHanhLy > kgMienPhi) {
                    kgVuot = danhSach[soLuong].canNangHanhLy - kgMienPhi;
                } else {
                    kgVuot = 0.0f;
                }
                danhSach[soLuong].phiHanhLy = kgVuot * 50000.0f;

                printf("Them hanh khach thanh cong! Phi hanh ly qua cuoc: %.0f VND\n", danhSach[soLuong].phiHanhLy);
                soLuong++;
                break;

            case 2:
                if (soLuong == 0) {
                    printf("Danh sach hanh khach hien dang rong!\n");
                    break;
                }

                printf("\n-----------------------------------------------------------------------------------------\n");
                printf("| %-5s | %-10s | %-25s | %-12s | %-14s | %-18s|\n",
                       "STT", "Ma PNR", "Ho va Ten", "Hang ve", "Hanh ly (kg)", "Phi Qua Cuoc (VND)");
                printf("-----------------------------------------------------------------------------------------\n");
                tongPhi = 0.0f;
                for (i = 0; i < soLuong; i++) {
                    printf("| %-5d | %-10s | %-25s | %-12s | %-14.1f | %-18.0f|\n",
                           i + 1,
                           danhSach[i].maPNR,
                           danhSach[i].hoTen,
                           danhSach[i].hangVe,
                           danhSach[i].canNangHanhLy,
                           danhSach[i].phiHanhLy);
                    tongPhi += danhSach[i].phiHanhLy;
                }
                printf("-----------------------------------------------------------------------------------------\n");
                printf("Tong tien phi hanh ly da thu: %.0f VND\n", tongPhi);
                break;

            case 3:
                if (soLuong == 0) {
                    printf("Danh sach hanh khach hien dang rong!\n");
                    break;
                }

                printf("Nhap ma PNR can cap nhat: ");
                scanf("%14s", searchPNR);
                while (getchar() != '\n');

                foundIndex = -1;
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(danhSach[i].maPNR, searchPNR) == 0) {
                        foundIndex = i;
                        break;
                    }
                }

                if (foundIndex == -1) {
                    printf("Ma PNR khong ton tai trong he thong!\n");
                } else {
                    printf("Tim thay hanh khach: %s\n", danhSach[foundIndex].hoTen);
                    printf("Nhap so kg hanh ly ky gui moi: ");
                    while (scanf("%f", &danhSach[foundIndex].canNangHanhLy) != 1 || danhSach[foundIndex].canNangHanhLy < 0.0f) {
                        printf("Khoi luong khong hop le! Nhap lai (>= 0): ");
                        while (getchar() != '\n');
                    }
                    while (getchar() != '\n');

                    if (strcmp(danhSach[foundIndex].hangVe, "Business") == 0) {
                        kgMienPhi = 30.0f;
                    } else if (strcmp(danhSach[foundIndex].hangVe, "Deluxe") == 0) {
                        kgMienPhi = 20.0f;
                    } else {
                        kgMienPhi = 0.0f;
                    }

                    if (danhSach[foundIndex].canNangHanhLy > kgMienPhi) {
                        kgVuot = danhSach[foundIndex].canNangHanhLy - kgMienPhi;
                    } else {
                        kgVuot = 0.0f;
                    }
                    danhSach[foundIndex].phiHanhLy = kgVuot * 50000.0f;

                    printf("Cap nhat thanh cong! Phi hanh ly moi: %.0f VND\n", danhSach[foundIndex].phiHanhLy);
                }
                break;

            case 4:
                if (soLuong == 0) {
                    printf("Danh sach hanh khach hien dang rong!\n");
                    break;
                }

                countBusiness = 0;
                tongPhi = 0.0f;
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(danhSach[i].hangVe, "Business") == 0) {
                        countBusiness++;
                    }
                    tongPhi += danhSach[i].phiHanhLy;
                }

                printf("\n=== THONG KE DOANH THU & CHUYEN BAY ===\n");
                printf("1. Tong so hanh khach da check-in : %d\n", soLuong);
                printf("2. So luong hanh khach hang Business : %d\n", countBusiness);
                printf("3. Tong doanh thu phi qua cuoc hanh ly: %.0f VND\n", tongPhi);
                break;

            case 5:
                printf("Thoat chuong trinh thanh cong. Tam biet!\n");
                break;

            default:
                printf("Lua chon khong hop le! Vui long chon tu 1 den 5.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}
