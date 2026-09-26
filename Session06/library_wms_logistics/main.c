#include <stdio.h>
#include <string.h>

#define MAX 100
#define HAN_MUC_CHUAN 14
#define PHI_PHAT_MOI_NGAY 5000

int main(void) {
    char maPhieu[MAX][20];
    char maSach[MAX][20];
    int soNgayMuon[MAX];
    int soLuong = 0;

    int luaChon;
    int i;
    char maMoi[20];
    char maTimKiem[20];
    int trungLap;
    int pos;
    int ngayMoi;
    int ngayQuaHan;
    int tienPhat;

    do {
        printf("\n================ HE THONG QUAN LY MUON TRA SACH (LOGISTICS) ================\n");
        printf("1. Them moi phieu muon sach (Create)\n");
        printf("2. Hien thi danh sach phieu muon & Tien phat qua han (Read)\n");
        printf("3. Cap nhat so ngay muon sach (Update)\n");
        printf("4. Xac nhan tra sach / Xoa phieu muon (Delete)\n");
        printf("5. Thoat chuong trinh\n");
        printf("===========================================================================\n");
        printf("Lua chon cua ban (1-5): ");

        if (scanf("%d", &luaChon) != 1) {
            printf("Lua chon khong hop le, vui long chon lai!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (luaChon) {
            case 1:
                printf("\n--- THEM MOI PHIEU MUON ---\n");
                if (soLuong >= MAX) {
                    printf("Bo nho danh sach da day, khong the them moi!\n");
                    break;
                }

                printf("Nhap ma phieu: ");
                scanf("%s", maMoi);
                while (getchar() != '\n');

                trungLap = 0;
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], maMoi) == 0) {
                        trungLap = 1;
                        break;
                    }
                }

                if (trungLap == 1) {
                    printf("Ma phieu da ton tai trong he thong!\n");
                    break;
                }

                strcpy(maPhieu[soLuong], maMoi);

                printf("Nhap ma sach: ");
                scanf("%s", maSach[soLuong]);
                while (getchar() != '\n');

                while (1) {
                    printf("Nhap so ngay muon: ");
                    if (scanf("%d", &soNgayMuon[soLuong]) == 1 && soNgayMuon[soLuong] > 0) {
                        while (getchar() != '\n');
                        break;
                    }
                    printf("Loi: So ngay muon phai lon hon 0. Vui long nhap lai!\n");
                    while (getchar() != '\n');
                }

                soLuong++;
                printf("Them moi phieu muon thanh cong!\n");
                break;

            case 2:
                printf("\n================================ DANH SACH PHIEU MUON ================================\n");
                if (soLuong == 0) {
                    printf("Danh sach phieu muon hien dang rong!\n");
                } else {
                    printf("STT\tMA PHIEU\tMA SACH\t\tSO NGAY\tTRANG THAI\tTIEN PHAT (VND)\n");
                    for (i = 0; i < soLuong; i++) {
                        if (soNgayMuon[i] > HAN_MUC_CHUAN) {
                            ngayQuaHan = soNgayMuon[i] - HAN_MUC_CHUAN;
                            tienPhat = ngayQuaHan * PHI_PHAT_MOI_NGAY;
                            printf("%d\t%s\t\t%s\t\t%d\tQUA HAN\t\t%d\n",
                                   i + 1,
                                   maPhieu[i],
                                   maSach[i],
                                   soNgayMuon[i],
                                   tienPhat);
                        } else {
                            printf("%d\t%s\t\t%s\t\t%d\tDUNG HAN\t0\n",
                                   i + 1,
                                   maPhieu[i],
                                   maSach[i],
                                   soNgayMuon[i]);
                        }
                    }
                }
                printf("======================================================================================\n");
                break;

            case 3:
                printf("\n--- CAP NHAT SO NGAY MUON ---\n");
                if (soLuong == 0) {
                    printf("Danh sach phieu muon hien dang rong!\n");
                    break;
                }

                printf("Nhap ma phieu can cap nhat: ");
                scanf("%s", maTimKiem);
                while (getchar() != '\n');

                pos = -1;
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], maTimKiem) == 0) {
                        pos = i;
                        break;
                    }
                }

                if (pos == -1) {
                    printf("Khong tim thay ma phieu trong he thong!\n");
                } else {
                    printf("So ngay muon hien tai cua phieu %s la: %d\n", maPhieu[pos], soNgayMuon[pos]);
                    while (1) {
                        printf("Nhap so ngay muon moi: ");
                        if (scanf("%d", &ngayMoi) == 1 && ngayMoi > 0) {
                            while (getchar() != '\n');
                            soNgayMuon[pos] = ngayMoi;
                            printf("Cap nhat so ngay muon thanh cong!\n");
                            break;
                        }
                        printf("Loi: So ngay muon phai lon hon 0. Vui long nhap lai!\n");
                        while (getchar() != '\n');
                    }
                }
                break;

            case 4:
                printf("\n--- XAC NHAN TRA SACH / XOA PHIEU MUON ---\n");
                if (soLuong == 0) {
                    printf("Danh sach phieu muon hien dang rong!\n");
                    break;
                }

                printf("Nhap ma phieu xac nhan tra/xoa: ");
                scanf("%s", maTimKiem);
                while (getchar() != '\n');

                pos = -1;
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], maTimKiem) == 0) {
                        pos = i;
                        break;
                    }
                }

                if (pos == -1) {
                    printf("Khong tim thay ma phieu can xoa!\n");
                } else {
                    for (i = pos; i < soLuong - 1; i++) {
                        strcpy(maPhieu[i], maPhieu[i + 1]);
                        strcpy(maSach[i], maSach[i + 1]);
                        soNgayMuon[i] = soNgayMuon[i + 1];
                    }
                    soLuong--;
                    printf("Xac nhan tra sach va xoa phieu muon thanh cong!\n");
                }
                break;

            case 5:
                printf("\nCam on ban da su dung he thong. Tam biet!\n");
                break;

            default:
                printf("Lua chon khong hop le, vui long chon lai!\n");
                break;
        }
    } while (luaChon != 5);

    return 0;
}
