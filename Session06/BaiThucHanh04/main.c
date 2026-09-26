#include <stdio.h>
#include <string.h>

#define MAX 100
#define PHI_PHAT_MOI_NGAY 5000

int main(void) {
    char maSach[MAX][20];
    char tenSach[MAX][100];
    int tongSoLuong[MAX];
    int dangMuon[MAX];
    float giaBia[MAX];
    int soLuong = 0;

    int luaChon;
    int i;
    char maMoi[20];
    char maTimKiem[20];
    int trungLap;
    int pos;
    size_t len;

    int thaoTacMuonTra;
    int slMuon;
    int slTra;
    int ngayQuaHan;
    int tienPhat;

    int tongBanSach;
    int tongDangMuon;
    float tongGiaTriTaiSan;

    do {
        printf("\n================ HET HONG QUAN LY KHO SACH ================\n");
        printf("1. Them dau sach moi vao kho\n");
        printf("2. Hien thi danh sach kho sach\n");
        printf("3. Ghi nhan Muon / Tra sach va tinh phi phat\n");
        printf("4. Xoa dau sach khoi he thong kho\n");
        printf("5. Thong ke tong gia tri tai san kho sach\n");
        printf("0. Thoat chuong trinh\n");
        printf("===========================================================\n");
        printf("Lua chon cua ban: ");

        if (scanf("%d", &luaChon) != 1) {
            printf("Lua chon khong hop le. Vui long thu lai!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (luaChon) {
            case 1:
                printf("\n=== Them dau sach moi ===\n");
                if (soLuong >= MAX) {
                    printf("Loi: Kho day, khong the them dau sach moi!\n");
                    break;
                }

                printf("Nhap ma sach: ");
                scanf("%s", maMoi);
                while (getchar() != '\n');

                trungLap = 0;
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(maSach[i], maMoi) == 0) {
                        trungLap = 1;
                        break;
                    }
                }

                if (trungLap == 1) {
                    printf("Loi: Ma sach '%s' da ton tai trong he thong!\n", maMoi);
                    break;
                }

                strcpy(maSach[soLuong], maMoi);

                printf("Nhap ten sach: ");
                fgets(tenSach[soLuong], sizeof(tenSach[soLuong]), stdin);
                len = strlen(tenSach[soLuong]);
                if (len > 0 && tenSach[soLuong][len - 1] == '\n') {
                    tenSach[soLuong][len - 1] = '\0';
                }

                while (1) {
                    printf("Nhap tong so luong: ");
                    if (scanf("%d", &tongSoLuong[soLuong]) == 1 && tongSoLuong[soLuong] > 0) {
                        while (getchar() != '\n');
                        break;
                    }
                    printf("Loi: Tong so luong phai la so nguyen > 0. Nhap lai!\n");
                    while (getchar() != '\n');
                }

                while (1) {
                    printf("Nhap gia bia (VND): ");
                    if (scanf("%f", &giaBia[soLuong]) == 1 && giaBia[soLuong] > 0) {
                        while (getchar() != '\n');
                        break;
                    }
                    printf("Loi: Gia bia phai > 0. Nhap lai!\n");
                    while (getchar() != '\n');
                }

                dangMuon[soLuong] = 0;
                soLuong++;
                printf("Them dau sach moi thanh cong!\n");
                break;

            case 2:
                printf("\n=== Danh sach kho sach ===\n");
                if (soLuong == 0) {
                    printf("Kho sach hien dang rong!\n");
                } else {
                    printf("--------------------------------------------------------------------------------------------------\n");
                    printf("STT | Ma Sach | Ten Sach | Tong SL | Dang Muon | Kha Dung | Gia Bia (VND)\n");
                    printf("--------------------------------------------------------------------------------------------------\n");
                    for (i = 0; i < soLuong; i++) {
                        int khaDung = tongSoLuong[i] - dangMuon[i];
                        printf("%d | %s | %s | %d | %d | %d | %.2f\n",
                               i + 1,
                               maSach[i],
                               tenSach[i],
                               tongSoLuong[i],
                               dangMuon[i],
                               khaDung,
                               giaBia[i]);
                    }
                    printf("--------------------------------------------------------------------------------------------------\n");
                }
                break;

            case 3:
                printf("\n=== Muon / Tra sach ===\n");
                if (soLuong == 0) {
                    printf("Kho sach hien dang rong!\n");
                    break;
                }

                printf("Nhap ma sach can thao tac: ");
                scanf("%s", maTimKiem);
                while (getchar() != '\n');

                pos = -1;
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(maSach[i], maTimKiem) == 0) {
                        pos = i;
                        break;
                    }
                }

                if (pos == -1) {
                    printf("Loi: Khong tim thay ma sach '%s' trong he thong!\n", maTimKiem);
                } else {
                    printf("Tim thay sach: %s (Dang muon: %d, Kha dung: %d)\n",
                           tenSach[pos], dangMuon[pos], tongSoLuong[pos] - dangMuon[pos]);
                    printf("Chon thao tac (1 - Muon sach, 2 - Tra sach): ");
                    if (scanf("%d", &thaoTacMuonTra) != 1) {
                        printf("Thao tac khong hop le!\n");
                        while (getchar() != '\n');
                        break;
                    }
                    while (getchar() != '\n');

                    if (thaoTacMuonTra == 1) {
                        int khaDung = tongSoLuong[pos] - dangMuon[pos];
                        if (khaDung <= 0) {
                            printf("Loi: Sach nay da het, khong con ban kha dung de muon!\n");
                            break;
                        }

                        printf("Nhap so luong muon: ");
                        if (scanf("%d", &slMuon) == 1 && slMuon > 0 && slMuon <= khaDung) {
                            while (getchar() != '\n');
                            dangMuon[pos] += slMuon;
                            printf("Muon sach thanh cong! So luong dang muon hien tai: %d\n", dangMuon[pos]);
                        } else {
                            printf("Loi: So luong muon khong hop le hoac vuot qua so luong kha dung (%d)!\n", khaDung);
                            while (getchar() != '\n');
                        }
                    } else if (thaoTacMuonTra == 2) {
                        if (dangMuon[pos] == 0) {
                            printf("Loi: Sach nay hien tai khong co ban nao dang duoc muon!\n");
                            break;
                        }

                        printf("Nhap so luong tra: ");
                        if (scanf("%d", &slTra) == 1 && slTra > 0 && slTra <= dangMuon[pos]) {
                            while (getchar() != '\n');

                            while (1) {
                                printf("Nhap so ngay qua han (0 neu dung han): ");
                                if (scanf("%d", &ngayQuaHan) == 1 && ngayQuaHan >= 0) {
                                    while (getchar() != '\n');
                                    break;
                                }
                                printf("Loi: So ngay qua han phai la so nguyen >= 0. Nhap lai!\n");
                                while (getchar() != '\n');
                            }

                            dangMuon[pos] -= slTra;
                            printf("\n--- BIEN NHAN TRA SACH ---\n");
                            printf("Tra thanh cong: %d quyen.\n", slTra);

                            if (ngayQuaHan > 0) {
                                tienPhat = slTra * ngayQuaHan * PHI_PHAT_MOI_NGAY;
                                printf("Phat hien qua han: %d ngay.\n", ngayQuaHan);
                                printf("Tien phat qua han (5.000 VND/quyen/ngay): %d VND.\n", tienPhat);
                            } else {
                                printf("Tra sach dung han. Tien phat: 0 VND.\n");
                            }
                        } else {
                            printf("Loi: So luong tra khong hop le hoac vuot qua so luong dang muon (%d)!\n", dangMuon[pos]);
                            while (getchar() != '\n');
                        }
                    } else {
                        printf("Loi: Thao tac chi chon 1 hoac 2!\n");
                    }
                }
                break;

            case 4:
                printf("\n=== Xoa dau sach khoi he thong ===\n");
                if (soLuong == 0) {
                    printf("Kho sach hien dang rong!\n");
                    break;
                }

                printf("Nhap ma sach can xoa: ");
                scanf("%s", maTimKiem);
                while (getchar() != '\n');

                pos = -1;
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(maSach[i], maTimKiem) == 0) {
                        pos = i;
                        break;
                    }
                }

                if (pos == -1) {
                    printf("Loi: Khong tim thay ma sach '%s' can xoa!\n", maTimKiem);
                } else {
                    if (dangMuon[pos] > 0) {
                        printf("Loi: Sach dang cho muon (%d quyen), khong the xoa khoi he thong!\n", dangMuon[pos]);
                    } else {
                        for (i = pos; i < soLuong - 1; i++) {
                            strcpy(maSach[i], maSach[i + 1]);
                            strcpy(tenSach[i], tenSach[i + 1]);
                            tongSoLuong[i] = tongSoLuong[i + 1];
                            dangMuon[i] = dangMuon[i + 1];
                            giaBia[i] = giaBia[i + 1];
                        }
                        soLuong--;
                        printf("Xoa dau sach thanh cong khoi he thong!\n");
                    }
                }
                break;

            case 5:
                printf("\n=== Thong ke tong gia tri tai san kho sach ===\n");
                if (soLuong == 0) {
                    printf("Kho sach hien dang rong!\n");
                } else {
                    tongBanSach = 0;
                    tongDangMuon = 0;
                    tongGiaTriTaiSan = 0.0f;

                    for (i = 0; i < soLuong; i++) {
                        tongBanSach += tongSoLuong[i];
                        tongDangMuon += dangMuon[i];
                        tongGiaTriTaiSan += tongSoLuong[i] * giaBia[i];
                    }

                    printf("Tong so dau sach quan ly       : %d\n", soLuong);
                    printf("Tong so luong ban sach trong kho : %d quyen\n", tongBanSach);
                    printf("Tong so sach dang cho muon       : %d quyen\n", tongDangMuon);
                    printf("Tong so sach con kha dung        : %d quyen\n", tongBanSach - tongDangMuon);
                    printf("Tong gia tri tai san kho sach    : %.2f VND\n", tongGiaTriTaiSan);
                }
                break;

            case 0:
                printf("\nCam on ban da su dung phan he quan ly kho sach. Tam biet!\n");
                break;

            default:
                printf("Loi: Chuc nang khong ton tai. Vui long chon tu 0 den 5!\n");
                break;
        }
    } while (luaChon != 0);

    return 0;
}
