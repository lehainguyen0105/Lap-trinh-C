#include <stdio.h>

#define SO_BENH_NHAN 4
#define PHI_GOC 200000

int main() {
    int i; 
    int tuoi_benh_nhan[SO_BENH_NHAN];
    int co_bao_hiem[SO_BENH_NHAN];
    int phi_kham[SO_BENH_NHAN];

    int tong_doanh_thu = 0;
    int tong_ca_uu_tien = 0;

    printf("=== TIEP NHAN DU LIEU 4 BENH NHAN ===\n");
    for (i = 0; i < SO_BENH_NHAN; i++) {
        printf("\nNhap thong tin benh nhan thu %d:\n", i + 1);
        printf("- Tuoi: ");
        scanf("%d", &tuoi_benh_nhan[i]);
        printf("- Co BHYT (1: Co, 0: Khong): ");
        scanf("%d", &co_bao_hiem[i]);
    }

    for (i = 0; i < SO_BENH_NHAN; i++) {
6        if (tuoi_benh_nhan[i] <= 0 || tuoi_benh_nhan[i] > 120) {
            phi_kham[i] = 0;
            continue;
        }

        if (co_bao_hiem[i] != 0 && co_bao_hiem[i] != 1) {
            co_bao_hiem[i] = 0;
        }

        if (co_bao_hiem[i] == 1) {
            phi_kham[i] = PHI_GOC * 20 / 100;
        } else {
            phi_kham[i] = PHI_GOC;
        }

        tong_doanh_thu += phi_kham[i];

        if (tuoi_benh_nhan[i] > 70) {
            tong_ca_uu_tien++;
        }
    }

    printf("\n===============================================================\n");
    printf("%-5s %-10s %-12s %-15s %-15s\n", "STT", "Tuoi", "BHYT", "Phi Kham", "Phan Luong");
    printf("---------------------------------------------------------------\n");

    for (i = 0; i < SO_BENH_NHAN; i++) {
        if (tuoi_benh_nhan[i] <= 0 || tuoi_benh_nhan[i] > 120) {
            printf("%-5d %-10d %-12s %-15d %-15s\n", 
                   i + 1, tuoi_benh_nhan[i], "Khong ro", phi_kham[i], "LOI DU LIEU");
        } else {
            printf("%-5d %-10d %-12s %-15d %-15s\n", 
                   i + 1, 
                   tuoi_benh_nhan[i], 
                   (co_bao_hiem[i] == 1) ? "Co" : "Khong", 
                   phi_kham[i], 
                   (tuoi_benh_nhan[i] > 70) ? "UU TIEN" : "THUONG");
        }
    }

    printf("===============================================================\n");
    printf("Tong doanh thu ca truc : %d VND\n", tong_doanh_thu);
    printf("Tong so ca uu tien     : %d ca\n", tong_ca_uu_tien);

    return 0;
}
