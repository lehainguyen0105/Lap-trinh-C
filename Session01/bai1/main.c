#include <stdio.h>

int main() {
    // Khai bao cac thong tin dau vao cua don hang ShopeeFood
    int gia_tri_don;
    float khoang_cach_km;
    int is_vip;
    int is_da_huy;

    // Nhap du lieu mo phong tu ban phim
    printf("Nhap gia tri don hang (VND): ");
    scanf("%d", &gia_tri_don);

    printf("Nhap khoang cach giao hang (km): ");
    scanf("%f", &khoang_cach_km);

    printf("Nhap trang thai VIP (1: Co, 0: Khong): ");
    scanf("%d", &is_vip);

    printf("Nhap trang thai huy don (1: Da huy, 0: Hop le): ");
    scanf("%d", &is_da_huy);

    // Thuc hien kiem tra logic Freeship
    int is_freeship = (gia_tri_don >= 100000 || is_vip == 1) && (khoang_cach_km <= 5.0) && (is_da_huy == 0);

    // In ket qua doi soat
    printf("\n===================================\n");
    printf(" KET QUA KIEM TRA MA FREESHIP \n");
    printf("===================================\n");
    printf("Trang thai Freeship (1: Duoc nhan, 0: Tu choi): %d\n", is_freeship);
    printf("Trang thai don bi huy (1: Da huy, 0: Hop le): %d\n", is_da_huy);

    return 0;
}
