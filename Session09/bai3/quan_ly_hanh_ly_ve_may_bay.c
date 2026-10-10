#include <stdio.h>
#include <string.h>

#define MAX_VE 100

struct VeMayBay {
    char maVe[16];
    char tenHanhKhach[51];
    char hangVe[21];
    float canNangHanhLy;
    double cuocHanhLy;
};

int main(void) {
    struct VeMayBay danhSachVe[MAX_VE];
    int soLuong;
    int i;
    double tongCuoc = 0.0;
    int maxIndex = 0;
    char searchPNR[16];
    int foundIndex = -1;
    size_t len;

    printf("Nhap so luong ve may bay: ");
    if (scanf("%d", &soLuong) != 1 || soLuong < 1 || soLuong > MAX_VE) {
        printf("Loi: So luong ve khong hop le (phai tu 1 den %d)!\n", MAX_VE);
        return 0;
    }
    while (getchar() != '\n');

    for (i = 0; i < soLuong; i++) {
        printf("\n--- Nhap thong tin ve thu %d ---\n", i + 1);

        printf("Ma ve PNR: ");
        scanf("%15s", danhSachVe[i].maVe);
        while (getchar() != '\n');

        printf("Ho ten hanh khach: ");
        fgets(danhSachVe[i].tenHanhKhach, sizeof(danhSachVe[i].tenHanhKhach), stdin);
        len = strlen(danhSachVe[i].tenHanhKhach);
        if (len > 0 && danhSachVe[i].tenHanhKhach[len - 1] == '\n') {
            danhSachVe[i].tenHanhKhach[len - 1] = '\0';
        }

        printf("Hang ve (Business/Deluxe/Eco): ");
        scanf("%20s", danhSachVe[i].hangVe);
        while (getchar() != '\n');

        printf("Khoi luong hanh ly ky gui (kg): ");
        while (scanf("%f", &danhSachVe[i].canNangHanhLy) != 1 || danhSachVe[i].canNangHanhLy < 0.0f) {
            printf("Khoi luong hanh ly khong duoc am! Nhap lai (>= 0): ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        if (strcmp(danhSachVe[i].hangVe, "Business") == 0) {
            if (danhSachVe[i].canNangHanhLy <= 20.0f) {
                danhSachVe[i].cuocHanhLy = 0.0;
            } else {
                danhSachVe[i].cuocHanhLy = (danhSachVe[i].canNangHanhLy - 20.0f) * 50000.0;
            }
        } else {
            danhSachVe[i].cuocHanhLy = danhSachVe[i].canNangHanhLy * 50000.0;
        }
    }

    tongCuoc = 0.0;
    maxIndex = 0;
    for (i = 0; i < soLuong; i++) {
        tongCuoc += danhSachVe[i].cuocHanhLy;
        if (danhSachVe[i].canNangHanhLy > danhSachVe[maxIndex].canNangHanhLy) {
            maxIndex = i;
        }
    }

    printf("\n================================== DANH SACH VE MAY BAY CHUYEN BAY ==================================\n");
    printf("%-5s %-12s %-25s %-12s %12s %15s\n",
           "STT", "MA VE", "HO TEN HANH KHACH", "HANG VE", "HANH LY (KG)", "CUOC PHI (VND)");
    printf("----------------------------------------------------------------------------------------------------\n");
    for (i = 0; i < soLuong; i++) {
        printf("%-5d %-12s %-25s %-12s %12.1f %15.0f\n",
               i + 1,
               danhSachVe[i].maVe,
               danhSachVe[i].tenHanhKhach,
               danhSachVe[i].hangVe,
               danhSachVe[i].canNangHanhLy,
               danhSachVe[i].cuocHanhLy);
    }
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("Tong tien cuoc hanh ly toan chuyen: %.0f VND\n", tongCuoc);
    printf("Ve co hanh ly ky gui nang nhat: %s - %s (%.1f kg)\n",
           danhSachVe[maxIndex].maVe,
           danhSachVe[maxIndex].tenHanhKhach,
           danhSachVe[maxIndex].canNangHanhLy);

    printf("\n--- CAP NHAT THONG TIN HANH LY ---\n");
    printf("Nhap ma ve PNR can cap nhat hanh ly: ");
    scanf("%15s", searchPNR);
    while (getchar() != '\n');

    foundIndex = -1;
    for (i = 0; i < soLuong; i++) {
        if (strcmp(danhSachVe[i].maVe, searchPNR) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Khong tim thay ma ve PNR nay trong he thong!\n");
    } else {
        printf("Nhap can nang hanh ly ky gui moi (kg): ");
        while (scanf("%f", &danhSachVe[foundIndex].canNangHanhLy) != 1 || danhSachVe[foundIndex].canNangHanhLy < 0.0f) {
            printf("Khoi luong hanh ly khong duoc am! Nhap lai (>= 0): ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        if (strcmp(danhSachVe[foundIndex].hangVe, "Business") == 0) {
            if (danhSachVe[foundIndex].canNangHanhLy <= 20.0f) {
                danhSachVe[foundIndex].cuocHanhLy = 0.0;
            } else {
                danhSachVe[foundIndex].cuocHanhLy = (danhSachVe[foundIndex].canNangHanhLy - 20.0f) * 50000.0;
            }
        } else {
            danhSachVe[foundIndex].cuocHanhLy = danhSachVe[foundIndex].canNangHanhLy * 50000.0;
        }

        printf("Tim thay ma ve %s. Da cap nhat cuoc hanh ly moi: %.0f VND.\n",
               danhSachVe[foundIndex].maVe, danhSachVe[foundIndex].cuocHanhLy);

        printf("\n================================ DANH SACH VE MAY BAY SAU CAP NHAT ================================\n");
        printf("%-5s %-12s %-25s %-12s %12s %15s\n",
               "STT", "MA VE", "HO TEN HANH KHACH", "HANG VE", "HANH LY (KG)", "CUOC PHI (VND)");
        printf("----------------------------------------------------------------------------------------------------\n");
        for (i = 0; i < soLuong; i++) {
            printf("%-5d %-12s %-25s %-12s %12.1f %15.0f\n",
                   i + 1,
                   danhSachVe[i].maVe,
                   danhSachVe[i].tenHanhKhach,
                   danhSachVe[i].hangVe,
                   danhSachVe[i].canNangHanhLy,
                   danhSachVe[i].cuocHanhLy);
        }
        printf("----------------------------------------------------------------------------------------------------\n");
    }

    return 0;
}
