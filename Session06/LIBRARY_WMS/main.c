#include <stdio.h>
#include <string.h>

#define MAX 100
#define HAN_MUC_CHUAN 14
#define PHI_PHAT_MOI_NGAY 5000

int main(void) {
    char maPhieu[MAX][15];
    char tenSach[MAX][50];
    int soNgayMuon[MAX];
    int tienPhat[MAX];
    int soLuong = 0;

    int luaChon;
    int i;
    char maTimKiem[15];
    int viTri;
    int ngayMoi;
    int tongTienPhat;
    int demQuaHan;
    size_t len;

    do {
        printf("\n================ HE THONG QUAN LY MUON TRA SACH (LIBRARY_WMS) ================\n");
        printf("1. Them luot muon sach moi\n");
        printf("2. Hien thi danh sach muon sach\n");
        printf("3. Cap nhat so ngay muon theo Ma phieu\n");
        printf("4. Xoa luot muon sach theo Ma phieu\n");
        printf("5. Thong ke danh sach phieu muon bi phat (Qua han > 14 ngay)\n");
        printf("6. Thoat chuong trinh\n");
        printf("==============================================================================\n");
        printf("Lua chon cua ban: ");

        if (scanf("%d", &luaChon) != 1) {
            printf("Lua chon khong hop le. Vui long thu lai!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (luaChon) {
            case 1:
                printf("\n=== THEM LUOT MUON SACH MOI ===\n");
                if (soLuong >= MAX) {
                    printf("He thong day, khong the them phieu muon moi!\n");
                    break;
                }

                while (1) {
                    int trungLap = 0;
                    printf("Nhap ma phieu muon: ");
                    scanf("%s", maPhieu[soLuong]);
                    while (getchar() != '\n');

                    for (i = 0; i < soLuong; i++) {
                        if (strcmp(maPhieu[i], maPhieu[soLuong]) == 0) {
                            trungLap = 1;
                            break;
                        }
                    }

                    if (trungLap) {
                        printf("Loi: Ma phieu '%s' da ton tai tren he thong. Vui long nhap lai!\n", maPhieu[soLuong]);
                    } else {
                        break;
                    }
                }

                printf("Nhap ten sach: ");
                fgets(tenSach[soLuong], sizeof(tenSach[soLuong]), stdin);
                len = strlen(tenSach[soLuong]);
                if (len > 0 && tenSach[soLuong][len - 1] == '\n') {
                    tenSach[soLuong][len - 1] = '\0';
                }

                while (1) {
                    printf("Nhap so ngay muon thuc te: ");
                    if (scanf("%d", &soNgayMuon[soLuong]) == 1 && soNgayMuon[soLuong] > 0) {
                        while (getchar() != '\n');
                        break;
                    }
                    printf("Loi: So ngay muon phai la so nguyen lon hon 0. Nhap lai!\n");
                    while (getchar() != '\n');
                }

                if (soNgayMuon[soLuong] > HAN_MUC_CHUAN) {
                    tienPhat[soLuong] = (soNgayMuon[soLuong] - HAN_MUC_CHUAN) * PHI_PHAT_MOI_NGAY;
                } else {
                    tienPhat[soLuong] = 0;
                }

                printf("\n--> Tien phat tu dong tinh: %d VND\n", tienPhat[soLuong]);
                printf("--> Them luot muon sach thanh cong!\n");
                soLuong++;
                break;

            case 2:
                printf("\n================ DANH SACH MUON SACH ================\n");
                if (soLuong == 0) {
                    printf("Danh sach muon sach hien dang rong!\n");
                } else {
                    printf("STT | Ma Phieu | Ten Sach | So Ngay | Tien Phat (VND)\n");
                    printf("------------------------------------------------------\n");
                    tongTienPhat = 0;
                    for (i = 0; i < soLuong; i++) {
                        printf("%d | %s | %s | %d | %d VND\n",
                               i + 1,
                               maPhieu[i],
                               tenSach[i],
                               soNgayMuon[i],
                               tienPhat[i]);
                        tongTienPhat += tienPhat[i];
                    }
                    printf("------------------------------------------------------\n");
                    printf("Tong tien phat toan he thong: %d VND\n", tongTienPhat);
                }
                break;

            case 3:
                printf("\n=== CAP NHAT SO NGAY MUON ===\n");
                if (soLuong == 0) {
                    printf("Danh sach muon sach hien dang rong!\n");
                    break;
                }

                printf("Nhap ma phieu muon can cap nhat: ");
                scanf("%s", maTimKiem);
                while (getchar() != '\n');

                viTri = -1;
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], maTimKiem) == 0) {
                        viTri = i;
                        break;
                    }
                }

                if (viTri == -1) {
                    printf("Khong tim thay phieu muon co ma: %s\n", maTimKiem);
                } else {
                    printf("Tim thay phieu muon cua sach: %s (So ngay hien tai: %d)\n", tenSach[viTri], soNgayMuon[viTri]);
                    while (1) {
                        printf("Nhap so ngay muon thuc te moi: ");
                        if (scanf("%d", &ngayMoi) == 1 && ngayMoi > 0) {
                            while (getchar() != '\n');
                            soNgayMuon[viTri] = ngayMoi;
                            if (soNgayMuon[viTri] > HAN_MUC_CHUAN) {
                                tienPhat[viTri] = (soNgayMuon[viTri] - HAN_MUC_CHUAN) * PHI_PHAT_MOI_NGAY;
                            } else {
                                tienPhat[viTri] = 0;
                            }
                            printf("\n--> Tien phat moi: %d VND\n", tienPhat[viTri]);
                            printf("--> Cap nhat so ngay muon thanh cong!\n");
                            break;
                        }
                        printf("Loi: So ngay muon phai la so nguyen lon hon 0. Nhap lai!\n");
                        while (getchar() != '\n');
                    }
                }
                break;

            case 4:
                printf("\n=== XOA LUOT MUON SACH ===\n");
                if (soLuong == 0) {
                    printf("Danh sach muon sach hien dang rong!\n");
                    break;
                }

                printf("Nhap ma phieu muon can xoa: ");
                scanf("%s", maTimKiem);
                while (getchar() != '\n');

                viTri = -1;
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], maTimKiem) == 0) {
                        viTri = i;
                        break;
                    }
                }

                if (viTri == -1) {
                    printf("Khong tim thay phieu muon co ma: %s\n", maTimKiem);
                } else {
                    for (i = viTri; i < soLuong - 1; i++) {
                        strcpy(maPhieu[i], maPhieu[i + 1]);
                        strcpy(tenSach[i], tenSach[i + 1]);
                        soNgayMuon[i] = soNgayMuon[i + 1];
                        tienPhat[i] = tienPhat[i + 1];
                    }
                    soLuong--;
                    printf("Xoa phieu muon thanh cong!\n");
                }
                break;

            case 5:
                printf("\n=== DANH SACH PHIEU MUON BI PHAT (QUA HAN > 14 NGAY) ===\n");
                if (soLuong == 0) {
                    printf("Danh sach muon sach hien dang rong!\n");
                    break;
                }

                demQuaHan = 0;
                for (i = 0; i < soLuong; i++) {
                    if (soNgayMuon[i] > HAN_MUC_CHUAN) {
                        if (demQuaHan == 0) {
                            printf("STT | Ma Phieu | Ten Sach | So Ngay | Tien Phat (VND)\n");
                            printf("------------------------------------------------------\n");
                        }
                        printf("%d | %s | %s | %d | %d VND\n",
                               demQuaHan + 1,
                               maPhieu[i],
                               tenSach[i],
                               soNgayMuon[i],
                               tienPhat[i]);
                        demQuaHan++;
                    }
                }

                if (demQuaHan == 0) {
                    printf("Khong co luot muon nao bi qua han phat!\n");
                } else {
                    printf("------------------------------------------------------\n");
                    printf("Tong so phieu qua han: %d phieu\n", demQuaHan);
                }
                break;

            case 6:
                printf("\nCam on ban da su dung he thong LIBRARY_WMS. Tam biet!\n");
                break;

            default:
                printf("Lua chon khong hop le. Vui long thu lai!\n");
                break;
        }
    } while (luaChon != 6);

    return 0;
}
