#include <stdio.h>

int main(void) {
    float distance = 0.0f;
    int has_promo = 0;
    float total_fare = 0.0f;

    // 1. Tiep nhan du lieu dau vao tu ban phim
    printf("Nhap quang duong (km): ");
    scanf("%f", &distance);

    printf("Ap dung ma giam gia (1: Co, 0: Khong): ");
    scanf("%d", &has_promo);

    // 2. Kiem soat du lieu dau vao (Input Validation / Defensive Programming)
    if (distance <= 0.0f || (has_promo != 0 && has_promo != 1)) {
        printf("Loi: Du lieu dau vao khong hop le!\n");
        return 0;
    }

    // 3. Tinh cuoc phi tieu chuan theo quang duong (20.000 VND/km)
    total_fare = distance * 20000.0f;

    // 4. Ap dung ma giam gia (giam 20%) va kiem tra muc cuoc san toi thieu (15.000 VND)
    if (has_promo == 1) {
        total_fare = total_fare * 0.8f; // Giam 20% gia tri chuyen xe
        if (total_fare < 15000.0f) {
            total_fare = 15000.0f;      // Ap dung cuoc san toi thieu
        }
    }

    // 5. Hien thi tong cuoc phi thanh toan theo dinh dang chuan
    printf("Tong cuoc phi: %.2f VNÐ\n", total_fare);

    return 0;
}
