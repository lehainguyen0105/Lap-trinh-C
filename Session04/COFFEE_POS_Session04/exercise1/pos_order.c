#include <stdio.h>

int main(void) {
    int so_luong_ly = 0;
    long long tong_tien = 0;
    int i = 0;
    long long don_gia_co_ban = 0;
    int size_option = 0;

    printf("=== HE THONG POS TINH TIEN COFFEE ===\n");
    printf("Nhap so luong ly trong don hang: ");
    scanf("%d", &so_luong_ly);

    if (so_luong_ly <= 0) {
        printf("\nLoi: So luong ly phai lon hon 0!\n");
        return 0;
    }

    for (i = 1; i <= so_luong_ly; i++) {
        don_gia_co_ban = 30000;
        size_option = 0;

        printf("\n--- Ly thu %d ---\n", i);
        printf("Chon size (1-Size S, 2-Size M, 3-Size L): ");
        scanf("%d", &size_option);

        if (size_option == 2) {
            don_gia_co_ban += 6000;
        } else if (size_option == 3) {
            don_gia_co_ban += 10000;
        }

        tong_tien += don_gia_co_ban;
    }

    printf("\n===================================\n");
    printf("Tong chi phi don hang: %lld VND\n", tong_tien);

    return 0;
}
