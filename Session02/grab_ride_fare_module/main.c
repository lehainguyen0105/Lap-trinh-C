
#include <stdio.h>

int main(void) {
    // Khai bao bien voi kieu du lieu nguyen thuy
    double distance = 0.0;
    int is_peak_or_rain = 0;
    double base_fare = 0.0;
    double surcharge_fare = 0.0;
    double total_fare = 0.0;

    printf("========================================\n");
    printf("   GRABRIDE - DYNAMIC PRICING ENGINE   \n");
    printf("========================================\n");

    // 1. Nhap du lieu dau vao tu ban phim
    printf("Nhap quang duong di chuyen (km): ");
    scanf("%lf", &distance);

    printf("Thoi tiet co mua hoac gio cao diem khong? (1: Co, 0: Khong): ");
    scanf("%d", &is_peak_or_rain);

    // 2. Kiem tra tinh toan ven du lieu (Chan khoang cach khong hop le)
    if (distance <= 0.0) {
        printf("\n[CANH BAO]: Quang duong di chuyen khong hop le (%.2f km)!\n", distance);
        printf("He thong tu choi xu ly chuyen di nay.\n");
        return 0;
    }

    // 3. Tinh toan cuoc phi co ban (chi su dung if / else co ban)
    if (distance <= 2.0) {
        // Gia mo cua co dinh cho 2 km dau tien
        base_fare = 12000.0;
    } else {
        // Tu km thu 3 tro di: 12.000 + (phan vuot qua 2 km) * 4.500
        base_fare = 12000.0 + (distance - 2.0) * 4500.0;
    }

    // 4. Tinh toan phu phi bien doi (Dynamic Surcharge 1.2x = tang 20%)
    if (is_peak_or_rain == 1) {
        surcharge_fare = base_fare * 0.20;
    } else {
        surcharge_fare = 0.0;
    }

    // 5. Tinh tong chi phi cuoi cung
    total_fare = base_fare + surcharge_fare;

    // 6. Xuat chi tiet hoa don ra man hinh
    printf("\n----------------------------------------\n");
    printf("         CHI TIET HOA DON CHUYEN DI     \n");
    printf("----------------------------------------\n");
    printf("Quang duong thuc te : %.2f km\n", distance);
    printf("Cuoc phi co ban     : %.0f VND\n", base_fare);
    printf("Tien phu phi phat sinh: %.0f VND\n", surcharge_fare);
    printf("----------------------------------------\n");
    printf("TONG TIEN THANH TOAN: %.0f VND\n", total_fare);
    printf("========================================\n");

    return 0;
}
