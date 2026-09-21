#include <stdio.h>

int main(void) {
    // 1. Khai bao bien luu tru du lieu dau vao va ket qua tinh toan
    int tuoi = 0;
    int ma_phim = 0;
    int ma_ghe = 0;
    int ma_doi_tuong = 0;

    const float GIA_VE_GOC = 80000.0f;
    float phu_thu_ghe = 0.0f;
    float giam_gia = 0.0f;
    float gia_sau_giam = 0.0f;
    float tong_tien = 0.0f;

    // 2. Tiep nhan du lieu tu ban phim
    printf("--- HE THONG BAN VE PHIM CGV ---\n");
    printf("Nhap tuoi khang gia: ");
    scanf("%d", &tuoi);

    printf("Nhap ma loai phim (1-P, 2-T18): ");
    scanf("%d", &ma_phim);

    printf("Nhap ma loai ghe (1-Thuong, 2-VIP, 3-Couple): ");
    scanf("%d", &ma_ghe);

    printf("Nhap ma doi tuong (1-Thuong, 2-HS/SV): ");
    scanf("%d", &ma_doi_tuong);

    // Yeu cau 1: Kiem chuan du lieu dau vao (Input Validation)
    if (tuoi <= 0 || 
        (ma_phim != 1 && ma_phim != 2) || 
        (ma_ghe != 1 && ma_ghe != 2 && ma_ghe != 3) || 
        (ma_doi_tuong != 1 && ma_doi_tuong != 2)) {
        printf("\nLOI: Du lieu nhap vao khong hop le!\n");
        return 0;
    }

    // Yeu cau 2: Kiem tra quy dinh gioi han do tuoi xem phim T18
    if (ma_phim == 2 && tuoi < 18) {
        printf("\nTU CHOI BAN VE: Khang gia chua du 18 tuoi de xem phim T18!\n");
        return 0;
    }

    // Yeu cau 3: Tinh toan phu thu loai ghe (Bat buoc dung switch-case)
    switch (ma_ghe) {
        case 1:
            phu_thu_ghe = 0.0f;
            break;
        case 2:
            phu_thu_ghe = 15000.0f;
            break;
        case 3:
            phu_thu_ghe = 30000.0f;
            break;
        default:
            break;
    }

    // Yeu cau 3: Tinh toan chiet khau theo doi tuong (Bat buoc dung if - else)
    if (ma_doi_tuong == 2) {
        // Giam 20% tren gia ve co ban (80.000 * 0.20 = 16.000 VND)
        giam_gia = GIA_VE_GOC * 0.20f;
    } else {
        giam_gia = 0.0f;
    }

    // Cong thuc tinh toan tai chinh
    gia_sau_giam = GIA_VE_GOC - giam_gia;
    tong_tien = gia_sau_giam + phu_thu_ghe;

    // Yeu cau 4: Hien thi hoa don chi tiet theo dung mau console
    printf("\n--- HOA DON THANH TOAN ---\n");
    if (ma_doi_tuong == 2) {
        printf("Doi tuong: Hoc sinh / Sinh vien\n");
    } else {
        printf("Doi tuong: Khach thong thuong\n");
    }

    if (ma_ghe == 1) {
        printf("Loai ghe: Thuong\n");
    } else if (ma_ghe == 2) {
        printf("Loai ghe: VIP\n");
    } else {
        printf("Loai ghe: Couple\n");
    }

    printf("Gia ve goc: %.0f VND\n", GIA_VE_GOC);
    printf("Giam gia uu dai: %.0f VND\n", giam_gia);
    printf("Phu thu ghe: %.0f VND\n", phu_thu_ghe);
    printf("Tong tien thanh toan: %.0f VND\n", tong_tien);

    return 0;
}
