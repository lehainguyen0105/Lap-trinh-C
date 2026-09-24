#include <stdio.h>

int main(void) {
    int n = 0;
    int i = 0;

    int successful_orders = 0;
    int skipped_orders = 0;
    long long total_revenue = 0;

    int drink_code = 0;
    int size_code = 0;
    int topping_count = 0;
    int is_gold_member = 0;

    long long base_price = 0;
    long long size_surcharge = 0;
    long long topping_surcharge = 0;
    long long item_total = 0;

    printf("====================================================\n");
    printf("     HIGHLANDS POS - SHIFT REVENUE AUDIT ENGINE     \n");
    printf("====================================================\n");

    printf("Nhap tong so giao dich can kiem toan trong ca (N): ");
    if (scanf("%d", &n) != 1) {
        printf("[LOI HE THONG]: Dinh dang nhap N khong hop le!\n");
        return 0;
    }

    if (n <= 0) {
        printf("\n[CANH BAO NGHIEP VU]: So luong giao dich khong hop le (N = %d)!\n", n);
        printf("He thong tu choi xu ly va dong ca lap tuc.\n");
        return 0;
    }

    for (i = 1; i <= n; i++) {
        printf("\n----------------------------------------------------\n");
        printf(">>> GIAO DICH %d / %d <<<\n", i, n);
        printf("Nhap ma do uong (-1: Ngat khan cap, 0: Huy don, 1-3: Chon mon): ");
        scanf("%d", &drink_code);

        if (drink_code == -1) {
            printf("\n[NGAT KHAN CAP]: Phat hien su co an ninh/phan cung tai giao dich %d!\n", i);
            printf("He thong dung toan bo tien trinh ca va chot so ngay tai thoi diem nay.\n");
            break;
        }

        if (drink_code == 0) {
            printf("[THONG BAO]: Khach hang yeu cau huy don. Bo qua giao dich nay.\n");
            skipped_orders++;
            continue;
        }

        if (drink_code < 1 || drink_code > 3) {
            printf("[LOI DU LIEU]: Ma do uong %d khong hop le! Bo qua giao dich.\n", drink_code);
            skipped_orders++;
            continue;
        }

        if (drink_code == 1) {
            base_price = 29000;
        } else if (drink_code == 2) {
            base_price = 39000;
        } else {
            base_price = 49000;
        }

        printf("Nhap size (1: Size S, 2: Size M, 3: Size L): ");
        scanf("%d", &size_code);

        printf("Nhap so luong topping (0 - 5 phan): ");
        scanf("%d", &topping_count);

        printf("Trang thai the Gold (1: Co the, 0: Khong): ");
        scanf("%d", &is_gold_member);

        if (size_code < 1 || size_code > 3 || topping_count < 0 || topping_count > 5) {
            printf("[LOI DU LIEU]: Size hoac so luong Topping ngoai nguong hop le! Bo qua giao dich.\n");
            skipped_orders++;
            continue;
        }

        if (size_code == 1) {
            size_surcharge = 0;
        } else if (size_code == 2) {
            size_surcharge = 6000;
        } else {
            size_surcharge = 10000;
        }

        topping_surcharge = (long long)topping_count * 8000;

        item_total = base_price + size_surcharge + topping_surcharge;

        if (is_gold_member == 1) {
            item_total = (item_total * 90) / 100;
        }

        total_revenue += item_total;
        successful_orders++;

        printf("=> Giao dich thanh cong! Thanh tien: %lld VND\n", item_total);
    }

    printf("\n====================================================\n");
    printf("         KET QUA KIEM TOAN DOANH THU CA LAM VIEC    \n");
    printf("====================================================\n");
    printf("Tong so giao dich hop le thanh cong : %d giao dich\n", successful_orders);
    printf("Tong so giao dich loi/huy bi bo qua : %d giao dich\n", skipped_orders);
    printf("Tong doanh thu chot so thuc te      : %lld VND\n", total_revenue);
    printf("====================================================\n");

    return 0;
}
