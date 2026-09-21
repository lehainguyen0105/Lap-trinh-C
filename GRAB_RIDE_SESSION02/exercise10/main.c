#include <stdio.h>

int main(void) {
    double distance_km = 0.0;
    int is_surge = 0;
    double base_fare = 0.0;
    double total_fare = 0.0;

    printf("========================================\n");
    printf("   TRIP FARE ENGINE - GRABRIDE (C11)   \n");
    printf("========================================\n");

    // 1. Tiep nhan du lieu dau vao tu nguoi dung
    printf("Nhap quang duong di chuyen (km): ");
    if (scanf("%lf", &distance_km) != 1) {
        printf("\n[LOI]: Dinh dang quang duong nhap vao khong hop le!\n");
        return 0;
    }

    printf("Trang thai phu phi (0: Binh thuong, 1: Mua/Cao diem): ");
    if (scanf("%d", &is_surge) != 1) {
        printf("\n[LOI]: Dinh dang trang thai phu phi khong hop le!\n");
        return 0;
    }

    // 2. GUARD CLAUSES: Chan dung va loai bo toan bo du lieu sai lech bien
    if (distance_km <= 0.0) {
        printf("\n[LOI BIEN]: Quang duong %.2f km khong hop le! "
               "(Cu ly di chuyen bat buoc phai > 0.0 km).\n", distance_km);
        printf("He thong tu choi giao dich va dung xu ly.\n");
        return 0;
    }

    if (is_surge != 0 && is_surge != 1) {
        printf("\n[LOI BIEN]: Trang thai phu phi %d khong hop le! "
               "(Chi chap nhan gia tri 0 hoac 1).\n", is_surge);
        printf("He thong tu choi giao dich va dung xu ly.\n");
        return 0;
    }

    // 3. STEP 1: Tinh cuoc co ban theo quang duong (Base Fare)
    if (distance_km <= 2.0) {
        // Nguong tron goi cho 2.0 km dau tien
        base_fare = 12000.0;
    } else {
        // Tinh cuoc luy tien cho quang duong vuot nguong 2.0 km
        base_fare = 12000.0 + (distance_km - 2.0) * 4500.0;
    }

    // 4. STEP 2: Ap dung he so phu phi thoi tiet / cao diem (Dynamic Surcharge)
    if (is_surge == 1) {
        total_fare = base_fare * 1.2;
    } else {
        total_fare = base_fare;
    }

    // 5. STEP 3: Xuat hoa don chi tiet ra man hinh
    printf("\n----------------------------------------\n");
    printf("            HOA DON THANH TOAN          \n");
    printf("----------------------------------------\n");
    printf("Quang duong thuc te : %.2f km\n", distance_km);
    printf("Cuoc phi co ban     : %.0f VND\n", base_fare);
    printf("He so phu phi       : %s\n", (is_surge == 1) ? "x1.2 (Thoi tiet xau/Cao diem)" : "1.0 (Khong ap dung)");
    printf("----------------------------------------\n");
    printf("TONG TIEN THANH TOAN: %.0f VND\n", total_fare);
    printf("========================================\n");

    return 0;
}
