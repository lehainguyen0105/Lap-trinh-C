#include <stdio.h>
#include <string.h>

#define MAX_VE 50

struct VeMayBay {
    char maPNR[10];
    char tenHanhKhach[50];
    char hangVe[15];
    float trongLuongHanhLy;
    long phiPhuThu;
};

int main(void) {
    struct VeMayBay dsVe[MAX_VE];
    int n;
    int i;
    char searchPNR[10];
    int foundIndex = -1;
    size_t len;

    printf("=== HE THONG CHECK-IN VE MAY BAY ===\n");
    printf("Nhap so luong ve (1 - 50): ");
    while (scanf("%d", &n) != 1 || n < 1 || n > MAX_VE) {
        printf("So luong khong hop le! Vui long nhap lai (1 - 50): ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    for (i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin ve thu %d ---\n", i + 1);

        printf("Nhap ma PNR: ");
        fgets(dsVe[i].maPNR, sizeof(dsVe[i].maPNR), stdin);
        len = strlen(dsVe[i].maPNR);
        if (len > 0 && dsVe[i].maPNR[len - 1] == '\n') {
            dsVe[i].maPNR[len - 1] = '\0';
        }

        printf("Nhap ho ten hanh khach: ");
        fgets(dsVe[i].tenHanhKhach, sizeof(dsVe[i].tenHanhKhach), stdin);
        len = strlen(dsVe[i].tenHanhKhach);
        if (len > 0 && dsVe[i].tenHanhKhach[len - 1] == '\n') {
            dsVe[i].tenHanhKhach[len - 1] = '\0';
        }

        printf("Nhap hang ve (Eco/Deluxe/Business): ");
        fgets(dsVe[i].hangVe, sizeof(dsVe[i].hangVe), stdin);
        len = strlen(dsVe[i].hangVe);
        if (len > 0 && dsVe[i].hangVe[len - 1] == '\n') {
            dsVe[i].hangVe[len - 1] = '\0';
        }

        printf("Nhap trong luong hanh ly (kg): ");
        while (scanf("%f", &dsVe[i].trongLuongHanhLy) != 1 || dsVe[i].trongLuongHanhLy < 0) {
            printf("Trong luong khong hop le! Nhap lai: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        if (dsVe[i].trongLuongHanhLy > 7.0f) {
            dsVe[i].phiPhuThu = (long)((dsVe[i].trongLuongHanhLy - 7.0f) * 50000.0f);
        } else {
            dsVe[i].phiPhuThu = 0;
        }
    }

    printf("\n=== DANH SACH VE MAY BAY CHUYEN BAY ===\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("%-5s %-10s %-25s %-12s %-15s %-18s\n",
           "STT", "MA PNR", "HO TEN HANH KHACH", "HANG VE", "HANH LY(KG)", "PHI PHU THU(VND)");
    printf("-----------------------------------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%-5d %-10s %-25s %-12s %-15.1f %-18ld\n",
               i + 1,
               dsVe[i].maPNR,
               dsVe[i].tenHanhKhach,
               dsVe[i].hangVe,
               dsVe[i].trongLuongHanhLy,
               dsVe[i].phiPhuThu);
    }
    printf("-----------------------------------------------------------------------------------------\n");

    printf("\n=== CAP NHAT THONG TIN HANH LY ===\n");
    printf("Nhap ma PNR can cap nhat: ");
    fgets(searchPNR, sizeof(searchPNR), stdin);
    len = strlen(searchPNR);
    if (len > 0 && searchPNR[len - 1] == '\n') {
        searchPNR[len - 1] = '\0';
    }

    foundIndex = -1;
    for (i = 0; i < n; i++) {
        if (strcmp(dsVe[i].maPNR, searchPNR) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Khong tim thay ma PNR hop le trong he thong!\n");
    } else {
        printf("Tim thay ve cua hanh khach: %s\n", dsVe[foundIndex].tenHanhKhach);
        printf("Nhap trong luong hanh ly moi (kg): ");
        while (scanf("%f", &dsVe[foundIndex].trongLuongHanhLy) != 1 || dsVe[foundIndex].trongLuongHanhLy < 0) {
            printf("Trong luong khong hop le! Nhap lai: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        if (dsVe[foundIndex].trongLuongHanhLy > 7.0f) {
            dsVe[foundIndex].phiPhuThu = (long)((dsVe[foundIndex].trongLuongHanhLy - 7.0f) * 50000.0f);
        } else {
            dsVe[foundIndex].phiPhuThu = 0;
        }

        printf("Cap nhat thanh cong! Phi phu thu moi: %ld VND\n", dsVe[foundIndex].phiPhuThu);

        printf("\n=== DANH SACH VE MAY BAY SAU CAP NHAT ===\n");
        printf("-----------------------------------------------------------------------------------------\n");
        printf("%-5s %-10s %-25s %-12s %-15s %-18s\n",
           "STT", "MA PNR", "HO TEN HANH KHACH", "HANG VE", "HANH LY(KG)", "PHI PHU THU(VND)");
        printf("-----------------------------------------------------------------------------------------\n");
        for (i = 0; i < n; i++) {
            printf("%-5d %-10s %-25s %-12s %-15.1f %-18ld\n",
                   i + 1,
                   dsVe[i].maPNR,
                   dsVe[i].tenHanhKhach,
                   dsVe[i].hangVe,
                   dsVe[i].trongLuongHanhLy,
                   dsVe[i].phiPhuThu);
        }
        printf("-----------------------------------------------------------------------------------------\n");
    }

    return 0;
}
