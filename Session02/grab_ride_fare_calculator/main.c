#include <stdio.h>

int main(void) {
    int vehicle_type = 0;
    double distance = 0.0;
    int is_peak_or_rain = 0;
    double base_fare = 0.0;
    double surcharge = 0.0;
    double total_fare = 0.0;

    // 1. Tiep nhan du lieu dau vao tu ban phim
    printf("--- HE THONG TINH CUOC CHUYEN XE GRABRIDE ---\n");
    printf("Nhap ma loai phuong tien (1: GrabBike, 2: GrabCar): ");
    scanf("%d", &vehicle_type);

    printf("Nhap quang duong di chuyen (km): ");
    scanf("%lf", &distance);

    printf("Thoi tiet/gio cao diem (1: Co phu phi, 0: Binh thuong): ");
    scanf("%d", &is_peak_or_rain);

    // 2. Kiem soat va chan cac loi du lieu bien nguy hiem (Input Validation)
    // Kiem tra cu ly bat thuong (Loi thuong gap 1)
    if (distance <= 0.0 || distance > 300.0) {
        printf("\n[LOI BIEN DICH / DU LIEU]: Cu ly %.2f km khong hop le! "
               "(Khoang cach phai > 0 va <= 300 km).\n", distance);
        printf("Giao dich bi huy bo.\n");
        return 0;
    }

    // Kiem tra ma loai xe hop le (Loi thuong gap 2)
    if (vehicle_type != 1 && vehicle_type != 2) {
        printf("\n[LOI BIEN DICH / DU LIEU]: Ma phuong tien %d khong ton tai trong he thong! "
               "(Chi chap nhan 1: GrabBike hoac 2: GrabCar).\n", vehicle_type);
        printf("Giao dich bi huy bo.\n");
        return 0;
    }

    // Kiem tra trang thai phu phi hop le (Loi thuong gap 2)
    if (is_peak_or_rain != 0 && is_peak_or_rain != 1) {
        printf("\n[LOI BIEN DICH / DU LIEU]: Trang thai phu phi %d khong hop le! "
               "(Chi chap nhan 0: Khong, 1: Co).\n", is_peak_or_rain);
        printf("Giao dich bi huy bo.\n");
        return 0;
    }

    // 3. Tinh toan cuoc phi co so (Base Fare) theo loai xe va nguong quang duong
    if (vehicle_type == 1) {
        // Dich vu GrabBike
        if (distance <= 2.0) {
            // Nguong toi thieu 2 km dau tien (Loi thuong gap 3)
            base_fare = 12000.0;
        } else {
            base_fare = 12000.0 + (distance - 2.0) * 4500.0;
        }
    } else if (vehicle_type == 2) {
        // Dich vu GrabCar
        if (distance <= 2.0) {
            // Nguong toi thieu 2 km dau tien (Loi thuong gap 3)
            base_fare = 25000.0;
        } else {
            base_fare = 25000.0 + (distance - 2.0) * 10000.0;
        }
    }

    // 4. Tinh toan phu phi bien doi thoi gian thuc (Dynamic Surcharge)
    if (is_peak_or_rain == 1) {
        // Ap dung he so 1.2x (tang 20% tren cuoc co so)
        surcharge = base_fare * 0.20;
    } else {
        surcharge = 0.0;
    }

    // 5. Tong cuoc phi thanh toan cuoi cung
    total_fare = base_fare + surcharge;

    // 6. Xuat hoa don chi tiet ra man hinh
    printf("\n========================================\n");
    printf("         HOA DON CHUYEN XE GRABRIDE     \n");
    printf("========================================\n");
    printf("Loai dich vu       : %s\n", (vehicle_type == 1) ? "GrabBike" : "GrabCar");
    printf("Quang duong        : %.2f km\n", distance);
    printf("Trang thai phu phi : %s\n", (is_peak_or_rain == 1) ? "Cao diem/Thoi tiet xau (+20%)" : "Khong");
    printf("----------------------------------------\n");
    printf("Cuoc phi co so     : %.0f VND\n", base_fare);
    printf("Phu phi bien doi   : %.0f VND\n", surcharge);
    printf("----------------------------------------\n");
    printf("TONG TIEN CUOC     : %.0f VND\n", total_fare);
    printf("========================================\n");

    return 0;
}
