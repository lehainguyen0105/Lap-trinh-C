#include <stdio.h>
#include <string.h>

#define MAX 50

int main(void) {
    char dsMaPhieu[MAX][20];
    char dsMaSV[MAX][20];
    int dsSoNgay[MAX];
    double dsTienPhat[MAX];
    int dsTrangThai[MAX];
    int soLuong = 0;

    int luaChon;
    int i;
    char maMoi[20];
    char maTimKiem[20];
    int trungLap;
    int pos;
    int thaoTacSua;
    int ngayMoi;
    double daThu;
    double duNo;

    do {
        printf("\n================ HETHONG QUAN LY PHI PHAT (LIBRARY_WMS) ================\n");
        printf("1. Them moi phieu phat qua han\n");
        printf("2. Hien thi danh sach & Thong ke tai chinh\n");
        printf("3. Cap nhat phieu phat\n");
        printf("4. Xoa phieu phat (Da thanh toan)\n");
        printf("5. Thoat\n");
        printf("------------------------------------------------------------------------\n");
        printf("Chon chuc nang (1-5): ");

        if (scanf("%d", &luaChon) != 1) {
            printf("Loi: Lua chon khong hop le. Vui long nhap lai!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (luaChon) {
            case 1:
                printf("\n--- THEM MOI PHIEU PHAT ---\n");
                if (soLuong >= MAX) {
                    printf("Loi: Danh sach da day, khong the them phieu phat moi!\n");
                    break;
                }

                while (1) {
                    printf("Nhap ma phieu muon: ");
                    scanf("%s", maMoi);
                    while (getchar() != '\n');

                    trungLap = 0;
                    for (i = 0; i < soLuong; i++) {
                        if (strcmp(dsMaPhieu[i], maMoi) == 0) {
                            trungLap = 1;
                            break;
                        }
                    }

                    if (trungLap == 1) {
                        printf("Loi: Ma phieu '%s' da ton tai trong he thong. Nhap lai!\n", maMoi);
                    } else {
                        strcpy(dsMaPhieu[soLuong], maMoi);
                        break;
                    }
                }

                printf("Nhap ma sinh vien: ");
                scanf("%s", dsMaSV[soLuong]);
                while (getchar() != '\n');

                while (1) {
                    printf("Nhap so ngay qua han: ");
                    if (scanf("%d", &dsSoNgay[soLuong]) == 1 && dsSoNgay[soLuong] > 0) {
                        while (getchar() != '\n');
                        break;
                    }
                    printf("Loi: So ngay qua han phai la so nguyen > 0. Nhap lai!\n");
                    while (getchar() != '\n');
                }

                if (dsSoNgay[soLuong] <= 7) {
                    dsTienPhat[soLuong] = dsSoNgay[soLuong] * 5000.0;
                } else {
                    dsTienPhat[soLuong] = (7 * 5000.0) + ((dsSoNgay[soLuong] - 7) * 10000.0);
                }

                dsTrangThai[soLuong] = 0;

                printf("\n[Thanh cong] Da them phieu phat %s. Tien phat: %.1f VND. Trang thai: Chua thanh toan.\n",
                       dsMaPhieu[soLuong], dsTienPhat[soLuong]);
                soLuong++;
                break;

            case 2:
                printf("\n============================ DANH SACH PHI PHAT ============================\n");
                if (soLuong == 0) {
                    printf("Danh sach phi phat dang rong!\n");
                } else {
                    printf("STT | Ma Phieu | Ma SV | So Ngay | Tien Phat (VND) | Trang Thai\n");
                    printf("----------------------------------------------------------------------------\n");
                    daThu = 0.0;
                    duNo = 0.0;

                    for (i = 0; i < soLuong; i++) {
                        printf("%d | %s | %s | %d | %.1f | %s\n",
                               i + 1,
                               dsMaPhieu[i],
                               dsMaSV[i],
                               dsSoNgay[i],
                               dsTienPhat[i],
                               (dsTrangThai[i] == 1) ? "Da thanh toan" : "Chua thanh toan");

                        if (dsTrangThai[i] == 1) {
                            daThu += dsTienPhat[i];
                        } else {
                            duNo += dsTienPhat[i];
                        }
                    }
                    printf("----------------------------------------------------------------------------\n");
                    printf("Tong tien phat da thu thanh cong : %.1f VND\n", daThu);
                    printf("Tong tien phat con du no chua thu: %.1f VND\n", duNo);
                }
                break;

            case 3:
                printf("\n--- CAP NHAT PHIEU PHAT ---\n");
                if (soLuong == 0) {
                    printf("Loi: Danh sach phi phat dang rong!\n");
                    break;
                }

                printf("Nhap ma phieu muon can cap nhat: ");
                scanf("%s", maTimKiem);
                while (getchar() != '\n');

                pos = -1;
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(dsMaPhieu[i], maTimKiem) == 0) {
                        pos = i;
                        break;
                    }
                }

                if (pos == -1) {
                    printf("Khong tim thay ma phieu nay trong he thong!\n");
                } else {
                    printf("Tim thay phieu phat cua SV: %s (So ngay: %d, Tien phat: %.1f VND, Trang thai: %s)\n",
                           dsMaSV[pos],
                           dsSoNgay[pos],
                           dsTienPhat[pos],
                           (dsTrangThai[pos] == 1) ? "Da thanh toan" : "Chua thanh toan");

                    printf("Chon thao tac (1: Cap nhat so ngay, 2: Xac nhan thanh toan): ");
                    if (scanf("%d", &thaoTacSua) != 1) {
                        printf("Loi: Thao tac khong hop le!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    while (getchar() != '\n');

                    if (thaoTacSua == 1) {
                        while (1) {
                            printf("Nhap so ngay qua han moi: ");
                            if (scanf("%d", &ngayMoi) == 1 && ngayMoi > 0) {
                                while (getchar() != '\n');
                                dsSoNgay[pos] = ngayMoi;

                                if (dsSoNgay[pos] <= 7) {
                                    dsTienPhat[pos] = dsSoNgay[pos] * 5000.0;
                                } else {
                                    dsTienPhat[pos] = (7 * 5000.0) + ((dsSoNgay[pos] - 7) * 10000.0);
                                }

                                printf("Cap nhat so ngay thanh cong! Tien phat moi: %.1f VND.\n", dsTienPhat[pos]);
                                break;
                            }
                            printf("Loi: So ngay qua han phai > 0. Nhap lai!\n");
                            while (getchar() != '\n');
                        }
                    } else if (thaoTacSua == 2) {
                        if (dsTrangThai[pos] == 1) {
                            printf("Phieu nay da duoc thanh toan truoc do!\n");
                        } else {
                            dsTrangThai[pos] = 1;
                            printf("Xac nhan thanh toan thanh cong cho phieu phat %s!\n", dsMaPhieu[pos]);
                        }
                    } else {
                        printf("Loi: Chi duoc chon thao tac 1 hoac 2!\n");
                    }
                }
                break;

            case 4:
                printf("\n--- XOA PHIEU PHAT (DA THANH TOAN) ---\n");
                if (soLuong == 0) {
                    printf("Loi: Danh sach phi phat dang rong!\n");
                    break;
                }

                printf("Nhap ma phieu muon can xoa: ");
                scanf("%s", maTimKiem);
                while (getchar() != '\n');

                pos = -1;
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(dsMaPhieu[i], maTimKiem) == 0) {
                        pos = i;
                        break;
                    }
                }

                if (pos == -1) {
                    printf("Khong tim thay ma phieu nay trong he thong!\n");
                } else {
                    if (dsTrangThai[pos] == 0) {
                        printf("Khong the xoa phieu phat CHUA thanh toan de tranh meo mo so sach tai chinh!\n");
                    } else {
                        for (i = pos; i < soLuong - 1; i++) {
                            strcpy(dsMaPhieu[i], dsMaPhieu[i + 1]);
                            strcpy(dsMaSV[i], dsMaSV[i + 1]);
                            dsSoNgay[i] = dsSoNgay[i + 1];
                            dsTienPhat[i] = dsTienPhat[i + 1];
                            dsTrangThai[i] = dsTrangThai[i + 1];
                        }
                        soLuong--;
                        printf("Xoa phieu phat thanh cong!\n");
                    }
                }
                break;

            case 5:
                printf("\nCam on ban da su dung phan he tai chinh thu vien. Tam biet!\n");
                break;

            default:
                printf("Loi: Chuc nang khong ton tai. Vui long chon tu 1 den 5!\n");
                break;
        }
    } while (luaChon != 5);

    return 0;
}
