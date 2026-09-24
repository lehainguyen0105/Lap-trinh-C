#include <stdio.h>

int main(void) {
    int n = 0;
    int i = 0;
    int valid_orders = 0;
    int invalid_orders = 0;
    long long total_shift_revenue = 0;
    long long max_order_value = 0;

    // Cac bien tam de luu tru thong tin tung hoa don
    long long base_price = 0;
    char size_char = ' ';
    int topping_count = 0;
    int is_gold_member = 0;

    long long size_surcharge = 0;
    long long topping_surcharge = 0;
    long long subtotal = 0;
    long long final_order_price = 0;

    printf("====================================================\n");
    printf("     HE THONG COFFEE_POS - CHOT SO DOANH THU CA    \n");
    printf("====================================================\n");

    printf("Nhap tong so hoa don can xu ly trong ca (N): ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("\n[THONG BAO]: Ca lam viec khong co hoa don hop le de xu ly (N <= 0).\n");
    }

    for (i = 1; i <= n; i++) {
        printf("\n----------------------------------------------------\n");
        printf(">>> XU LY HOA DON %d / %d <<<\n", i, n);

        printf("1. Nhap gia niem yet co so (Size S - VND): ");
        scanf("%lld", &base_price);

        printf("2. Nhap size do uong (S, M, L): ");
        scanf(" %c", &size_char);

        printf("3. Nhap so luong topping: ");
        scanf("%d", &topping_count);

        printf("4. Trang thai hoi vien (1: Gold Member, 0: Thuong): ");
        scanf("%d", &is_gold_member);

        if (topping_count < 0) {
            printf("\n[CANH BAO AN NINH]: Phat hien du lieu topping am (%d)!\n", topping_count);
            printf("He thong ngat khan cap ca lam viec, lap tuc dung nhan cac don tiep theo.\n");
            break;
        }

        if (base_price <= 0) {
            printf("[LOI NHAP LIEU]: Gia co so (%lld VND) khong hop le! Bo qua don hang nay.\n", base_price);
            invalid_orders++;
            continue;
        }

        if (size_char == 'S' || size_char == 's') {
            size_surcharge = 0;
        } else if (size_char == 'M' || size_char == 'm') {
            size_surcharge = 6000;
        } else if (size_char == 'L' || size_char == 'l') {
            size_surcharge = 10000;
        } else {
            printf("[LOI NHAP LIEU]: Ky tu size '%c' khong ton tai! Bo qua don hang nay.\n", size_char);
            invalid_orders++;
            continue;
        }

        topping_surcharge = (long long)topping_count * 8000;

        subtotal = base_price + size_surcharge + topping_surcharge;

        if (is_gold_member == 1) {
            final_order_price = subtotal - (long long)(subtotal * 0.10);
        } else {
            final_order_price = subtotal;
        }

        valid_orders++;
        total_shift_revenue += final_order_price;

        if (final_order_price > max_order_value) {
            max_order_value = final_order_price;
        }

        printf("=> Thanh toan thanh cong: %lld VND (Goc: %lld, Phu thu Size: %lld, Topping: %lld)\n",
               final_order_price, base_price, size_surcharge, topping_surcharge);
    }

    printf("\n====================================================\n");
    printf("         BAO CAO TONG HOP DOANH THU CA LAM VIEC     \n");
    printf("====================================================\n");
    printf("Tong so don hop le da thanh toan : %d don\n", valid_orders);
    printf("Tong so don loi / bi huy bo      : %d don\n", invalid_orders);
    printf("Tong doanh thu thuc te trong ca   : %lld VND\n", total_shift_revenue);
    printf("Gia tri don hang lon nhat trong ca: %lld VND\n", max_order_value);
    printf("====================================================\n");

    return 0;
}
