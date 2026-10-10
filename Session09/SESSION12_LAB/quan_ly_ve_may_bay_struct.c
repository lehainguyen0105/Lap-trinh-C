#include <stdio.h>
#include <string.h>

#define MAX_VE 100

struct FlightTicket {
    char pnrCode[15];
    char passengerName[50];
    int ticketClass;
    float baggageWeight;
    float baggageFee;
};

int main(void) {
    struct FlightTicket danhSachVe[MAX_VE];
    int soLuong = 0;
    int choice;
    int i, j;
    int foundIndex;
    char searchPNR[15];
    size_t len;

    do {
        printf("\n=== HE THONG BAN VE VA CHECK-IN MAY BAY ===\n");
        printf("1. Them ve may bay moi\n");
        printf("2. Hien thi danh sach ve\n");
        printf("3. Cap nhat hanh ly theo PNR\n");
        printf("4. Xoa ve theo PNR\n");
        printf("5. Thoat\n");
        printf("Lua chon cua ban: ");

        if (scanf("%d", &choice) != 1) {
            printf("Lua chon khong hop le! Vui long nhap so tu 1 den 5.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                if (soLuong >= MAX_VE) {
                    printf("Danh sach ve da day, khong the them moi!\n");
                    break;
                }

                printf("\nNhap ma PNR: ");
                scanf("%14s", danhSachVe[soLuong].pnrCode);
                while (getchar() != '\n');

                printf("Nhap ho ten hanh khach: ");
                fgets(danhSachVe[soLuong].passengerName, sizeof(danhSachVe[soLuong].passengerName), stdin);
                len = strlen(danhSachVe[soLuong].passengerName);
                if (len > 0 && danhSachVe[soLuong].passengerName[len - 1] == '\n') {
                    danhSachVe[soLuong].passengerName[len - 1] = '\0';
                }

                printf("Nhap hang ve (1-Eco, 2-Deluxe, 3-Business): ");
                while (scanf("%d", &danhSachVe[soLuong].ticketClass) != 1 ||
                       danhSachVe[soLuong].ticketClass < 1 || danhSachVe[soLuong].ticketClass > 3) {
                    printf("Hang ve khong hop le! Nhap lai (1-3): ");
                    while (getchar() != '\n');
                }

                printf("Nhap khoi luong hanh ly (kg): ");
                while (scanf("%f", &danhSachVe[soLuong].baggageWeight) != 1 || danhSachVe[soLuong].baggageWeight < 0.0f) {
                    printf("Khoi luong hanh ly khong hop le! Nhap lai (>= 0): ");
                    while (getchar() != '\n');
                }

                if (danhSachVe[soLuong].ticketClass == 3) {
                    danhSachVe[soLuong].baggageFee = 0.0f;
                } else {
                    if (danhSachVe[soLuong].baggageWeight <= 7.0f) {
                        danhSachVe[soLuong].baggageFee = 0.0f;
                    } else {
                        danhSachVe[soLuong].baggageFee = (danhSachVe[soLuong].baggageWeight - 7.0f) * 50000.0f;
                    }
                }

                printf("=> Them ve thanh cong! Cuoc phat hanh ly qua can: %.0f VND.\n", danhSachVe[soLuong].baggageFee);
                soLuong++;
                break;

            case 2:
                if (soLuong == 0) {
                    printf("Danh sach ve dang rong!\n");
                    break;
                }

                printf("\n========================================================================================\n");
                printf("%-5s | %-10s | %-25s | %-10s | %-14s | %-15s\n",
                       "STT", "Ma PNR", "Ho ten hanh khach", "Hang ve", "Hanh ly (kg)", "Cuoc qua cuoc");
                printf("========================================================================================\n");
                for (i = 0; i < soLuong; i++) {
                    char *tenHangVe;
                    if (danhSachVe[i].ticketClass == 3) {
                        tenHangVe = "Business";
                    } else if (danhSachVe[i].ticketClass == 2) {
                        tenHangVe = "Deluxe";
                    } else {
                        tenHangVe = "Eco";
                    }

                    printf("%-5d | %-10s | %-25s | %-10s | %-14.1f | %.0f VND\n",
                           i + 1,
                           danhSachVe[i].pnrCode,
                           danhSachVe[i].passengerName,
                           tenHangVe,
                           danhSachVe[i].baggageWeight,
                           danhSachVe[i].baggageFee);
                }
                printf("========================================================================================\n");
                break;

            case 3:
                if (soLuong == 0) {
                    printf("Danh sach ve dang rong!\n");
                    break;
                }

                printf("Nhap ma PNR can cap nhat hanh ly: ");
                scanf("%14s", searchPNR);

                foundIndex = -1;
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(danhSachVe[i].pnrCode, searchPNR) == 0) {
                        foundIndex = i;
                        break;
                    }
                }

                if (foundIndex == -1) {
                    printf("Khong tim thay ve co ma PNR da nhap!\n");
                } else {
                    printf("Tim thay hanh khach: %s\n", danhSachVe[foundIndex].passengerName);
                    printf("Nhap trong luong hanh ly moi (kg): ");
                    while (scanf("%f", &danhSachVe[foundIndex].baggageWeight) != 1 || danhSachVe[foundIndex].baggageWeight < 0.0f) {
                        printf("Trong luong khong hop le! Nhap lai (>= 0): ");
                        while (getchar() != '\n');
                    }

                    if (danhSachVe[foundIndex].ticketClass == 3) {
                        danhSachVe[foundIndex].baggageFee = 0.0f;
                    } else {
                        if (danhSachVe[foundIndex].baggageWeight <= 7.0f) {
                            danhSachVe[foundIndex].baggageFee = 0.0f;
                        } else {
                            danhSachVe[foundIndex].baggageFee = (danhSachVe[foundIndex].baggageWeight - 7.0f) * 50000.0f;
                        }
                    }

                    printf("=> Cap nhat thanh cong! Phi hanh ly qua cuoc moi: %.0f VND.\n", danhSachVe[foundIndex].baggageFee);
                }
                break;

            case 4:
                if (soLuong == 0) {
                    printf("Danh sach ve dang rong!\n");
                    break;
                }

                printf("Nhap ma PNR can xoa: ");
                scanf("%14s", searchPNR);

                foundIndex = -1;
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(danhSachVe[i].pnrCode, searchPNR) == 0) {
                        foundIndex = i;
                        break;
                    }
                }

                if (foundIndex == -1) {
                    printf("Khong tim thay ve co ma PNR da nhap!\n");
                } else {
                    for (j = foundIndex; j < soLuong - 1; j++) {
                        danhSachVe[j] = danhSachVe[j + 1];
                    }
                    soLuong--;
                    printf("=> Da xoa thanh cong ve co ma PNR: %s ra khoi he thong.\n", searchPNR);
                }
                break;

            case 5:
                printf("Cam on ban da su dung chuong trinh. Tam biet!\n");
                break;

            default:
                printf("Lua chon khong hop le! Vui long chon tu 1 den 5.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}
