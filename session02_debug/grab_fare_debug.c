#include <stdio.h>

int main(void) {
    float distance;
    int is_raining;
    double total_fare = 0.0;

    printf("Nhap quang duong di chuyen (km): ");
    scanf("%f", &distance);

    printf("Thoi tiet co mua khong (1: Co, 0: Khong): ");
    scanf("%d", &is_raining);

    // Kiem tra du lieu dau vao (Defensive Programming)
    if (distance <= 0.0f) {
        printf("Loi: Quang duong di chuyen phai lon hon 0!\n");
        return 0;
    }

    // 1. Tinh cuoc phi co ban theo quang duong (dung cong thuc luy tien)
    if (distance <= 2.0f) {
        total_fare = 12000.0;
    } else {
        total_fare = 12000.0 + (distance - 2.0f) * 4500.0;
    }

    // 2. Kiem tra phu phi thoi tiet bang toan tu so sanh ==
    if (is_raining == 1) {
        total_fare = total_fare * 1.2;
    }

    // 3. Xuat ket qua cuoc phi
    printf("Tong cuoc phi chuyen xe: %.0f VND\n", total_fare);

    return 0;
}
