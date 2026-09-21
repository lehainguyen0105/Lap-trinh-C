#include <stdio.h>

int main(void) {
    // 1. Khai bao cac bien luu tru thong tin giao dich
    int maPhim = 0;
    int tuoi = 0;
    int loaiGhe = 0;
    int doiTuong = 0;

    int gia_co_ban = 80000;
    int phu_thu = 0;
    int tong_truoc_giam = 0;
    double tien_giam = 0.0;
    double tong_tien_thanh_toan = 0.0;

    // 2. Hien thi giao dien va tiep nhan du lieu dau vao tu ban phim
    printf("=== H? TH?NG BÁN VÉ PHIM CGV / LOTTE ===\n");
    printf("Nh?p m? lo?i phim (1: Phim P, 2: Phim C18): ");
    scanf("%d", &maPhim);

    printf("Nh?p tu?i c?a khán gi?: ");
    scanf("%d", &tuoi);

    printf("Nh?p lo?i gh? (1: Gh? Thý?ng, 2: Gh? VIP): ");
    scanf("%d", &loaiGhe);

    printf("Nh?p ð?i tý?ng (1: Khách thông thý?ng, 2: HSSV): ");
    scanf("%d", &doiTuong);

    // 3. Kiem duyet do tuoi xem phim C18 (Guard Clause)
    if (maPhim == 2 && tuoi < 18) {
        printf("\n[THÔNG BÁO] T? ch?i bán vé: Khán gi? chýa ð? 18 tu?i ð? xem phim mác C18!\n");
        return 0;
    }

    // 4. Tinh phu thu loai ghe bang cau truc switch-case
    switch (loaiGhe) {
        case 1:
            phu_thu = 0;
            break;
        case 2:
            phu_thu = 15000;
            break;
        default:
            printf("\n[L?I] M? lo?i gh? không h?p l?! Vui l?ng ch?n 1 (Thý?ng) ho?c 2 (VIP).\n");
            return 0;
    }

    // 5. Tinh toan tong truoc giam va tien giam theo doi tuong (cau truc if - else)
    tong_truoc_giam = gia_co_ban + phu_thu;

    if (doiTuong == 2) {
        // Hoc sinh / Sinh vien duoc giam 20% tong chi phi
        tien_giam = tong_truoc_giam * 0.20;
    } else {
        tien_giam = 0.0;
    }

    // Tinh tong tien thanh toan cuoi cung
    tong_tien_thanh_toan = tong_truoc_giam - tien_giam;

    // 6. In hoa don thanh toan chi tiet ra man hinh console
    printf("\n=== HÓA ÐÕN THANH TOÁN VÉ PHIM ===\n");
    printf("Giá vé chu?n: %d VNÐ\n", gia_co_ban);
    if (loaiGhe == 2) {
        printf("Ph? thu gh? VIP: %d VNÐ\n", phu_thu);
    }
    printf("T?ng phí d?ch v?: %d VNÐ\n", tong_truoc_giam);
    if (doiTuong == 2) {
        printf("Gi?m giá HSSV (20%%): %.0f VNÐ\n", tien_giam);
    }
    printf("-----------------------------------\n");
    printf("T?NG TI?N PH?I THANH TOÁN: %.0f VNÐ\n", tong_tien_thanh_toan);

    return 0;
}
