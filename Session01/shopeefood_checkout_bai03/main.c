#include <stdio.h>

int main(void) {
    // 1. Khai bao cac bien dau vao (Inputs)
    int order_id;
    int subtotal;
    float distance_km;
    int booking_hour;
    int is_store_open;
    int inventory_qty;

    // 2. Nhap du lieu dau vao tu ban phim
    printf("Nhap ma don hang (order_id): ");
    scanf("%d", &order_id);

    printf("Nhap tien mon an (subtotal - VND): ");
    scanf("%d", &subtotal);

    printf("Nhap khoang cach giao (distance_km): ");
    scanf("%f", &distance_km);

    printf("Nhap gio dat hang (booking_hour [0-23]): ");
    scanf("%d", &booking_hour);

    printf("Nhap trang thai quan (1: Mo, 0: Dong): ");
    scanf("%d", &is_store_open);

    printf("Nhap so luong ton kho (inventory_qty): ");
    scanf("%d", &inventory_qty);

    // 3. Kiem tra tinh hop le toan dien bang bieu thuc Boole (chan du lieu sai)
    int is_valid_order = (is_store_open == 1) &&
                         (inventory_qty > 0) &&
                         (distance_km > 0.0f) &&
                         (distance_km <= 15.0f) &&
                         (booking_hour >= 0) &&
                         (booking_hour <= 23) &&
                         (subtotal > 0);

    // 4. Tach trang thai nghiep vu (Giai phap A - Bien co phan ra)
    // Gio cao diem: 11h-13h hoac 18h-20h
    int is_peak_hour = ((booking_hour >= 11 && booking_hour <= 13) ||
                        (booking_hour >= 18 && booking_hour <= 20));

    // Uu dai Freeship: Don tu 100,000 VND tro len
    int is_freeship = (subtotal >= 100000);

    // 5. Tinh toan cuoc phi thanh phan (khong dung if/else)
    int base_fee = 15000;
    int surcharge = is_peak_hour * 10000;
    int discount = is_freeship * 15000;

    // 6. Tinh phi giao va tong thanh toan (neu don khong hop le thi triet tieu ve 0)
    int final_delivery_fee = (base_fee + surcharge - discount) * is_valid_order;
    int total_payment = (subtotal + final_delivery_fee) * is_valid_order;

    // 7. In phieu doi soat ShopeeFood theo de bai
    printf("\n==================================================\n");
    printf("           SHOPEEFOOD ORDER RECEIPT               \n");
    printf("==================================================\n");
    printf("Ma don hang         : #%d\n", order_id);
    printf("Tien mon an         : %d VND\n", subtotal);
    printf("Khoang cach giao    : %.2f km\n", distance_km);
    printf("Gio dat hang        : %dh00\n", booking_hour);
    printf("Trang thai gio      : %d (1: Cao diem, 0: Thuong)\n", is_peak_hour);
    printf("Trang thai quan     : %d (1: Mo cua, 0: Dong cua)\n", is_store_open);
    printf("Ton kho kha dung    : %d\n", inventory_qty);
    printf("--------------------------------------------------\n");
    printf("Cuoc phi co ban     : %d VND\n", base_fee);
    printf("Phu phi gio cao diem: %d VND\n", surcharge);
    printf("Giam gia van chuyen : %d VND\n", discount);
    printf("Phi giao thuc te    : %d VND\n", final_delivery_fee);
    printf("--------------------------------------------------\n");
    printf("TRANG THAI DON HANG : %d (1: HOP LE / 0: TU CHOI)\n", is_valid_order);
    printf("TONG TIEN THANH TOAN: %d VND\n", total_payment);
    printf("==================================================\n");

    return 0;
}
