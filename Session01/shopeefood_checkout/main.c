#include <stdio.h>

int main() {
    // 1. Khai bao cac bien dau vao (Input Variables)
    int item_id;
    float unit_price;
    int order_quantity;
    float delivery_distance;
    int is_peak_hour;
    int is_store_open;
    int stock_quantity;
    char account_type;

    // 2. Nhap du lieu dau vao tu ban phim
    printf("Nhap Ma mon an: ");
    scanf("%d", &item_id);

    printf("Nhap Don gia mon an (VND): ");
    scanf("%f", &unit_price);

    printf("Nhap So luong dat mua: ");
    scanf("%d", &order_quantity);

    printf("Nhap Khoang cach giao hang (km): ");
    scanf("%f", &delivery_distance);

    printf("Nhap Trang thai gio cao diem (1: Co, 0: Khong): ");
    scanf("%d", &is_peak_hour);

    printf("Nhap Trang thai cua hang (1: Mo cua, 0: Dong cua): ");
    scanf("%d", &is_store_open);

    printf("Nhap So luong ton kho: ");
    scanf("%d", &stock_quantity);

    // Xu ly troi lenh stdin bang khoang trang truoc %c
    printf("Nhap Xep loai tai khoan (V: VIP, N: Normal): ");
    scanf(" %c", &account_type);

    // 3. Tinh toan tien mon an va phi giao hang co ban
    float subtotal = unit_price * order_quantity;
    float base_shipping_fee = delivery_distance * 5000.0f;

    // 4. Xac thuc dieu kien Freeship bang dai so Boole
    int is_eligible_freeship = ((subtotal >= 100000.0f && delivery_distance <= 5.0f) || 
                               (account_type == 'V' || account_type == 'v'));

    // Chan han muc: Giam gia toi da khong vuot qua Phi giao hang co ban
    int is_cap = (base_shipping_fee < 15000.0f);
    float freeship_discount = (float)is_eligible_freeship * 
                              (is_cap * base_shipping_fee + (!is_cap) * 15000.0f);

    // 5. Tinh phu phi gio cao diem
    float peak_surcharge = (float)(is_peak_hour == 1) * 10000.0f;

    // 6. Kiem tra tinh hop le toan dien cua don hang (Order Validity)
    int is_order_valid = (is_store_open == 1) && 
                         (stock_quantity >= order_quantity) && 
                         (order_quantity > 0) && 
                         (unit_price > 0.0f);

    // 7. Tinh tong thanh toan (Khoa ve 0 VND neu don hang khong hop le)
    float final_amount = (subtotal + base_shipping_fee - freeship_discount + peak_surcharge) * (float)is_order_valid;

    // 8. In hoa don quyet toan he thong ShopeeFood
    printf("\n==================================================\n");
    printf("        SHOPEEFOOD ORDER CHECKOUT SYSTEM          \n");
    printf("==================================================\n");
    printf("Ma mon an           : %d\n", item_id);
    printf("Don gia             : %.2f VND\n", unit_price);
    printf("So luong dat        : %d\n", order_quantity);
    printf("Khoang cach giao    : %.1f km\n", delivery_distance);
    printf("Khung gio cao diem  : %s (%d)\n", (is_peak_hour == 1) ? "Co" : "Khong", is_peak_hour);
    printf("Trang thai quan     : %s (%d)\n", (is_store_open == 1) ? "Mo cua" : "Dong cua", is_store_open);
    printf("So luong ton kho    : %d\n", stock_quantity);
    printf("Loai tai khoan      : %c (%s)\n", account_type, (account_type == 'V' || account_type == 'v') ? "VIP" : "Normal");
    printf("--------------------------------------------------\n");
    printf("TONG TIEN MON AN    : %.2f VND\n", subtotal);
    printf("PHI GIAO HANG CO BAN: %.2f VND\n", base_shipping_fee);
    printf("GIAM GIA FREESHIP   : %.2f VND\n", freeship_discount);
    printf("PHU PHI GIO CAO DIEM: %.2f VND\n", peak_surcharge);
    printf("--------------------------------------------------\n");
    printf("DON HANG HOP LE     : %d (%s)\n", is_order_valid, (is_order_valid == 1) ? "1: HOP LE" : "0: TU CHOI");
    printf("TONG THANH TIEN     : %.2f VND\n", final_amount);
    printf("==================================================\n");

    return 0;
}
