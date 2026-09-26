#include <stdio.h>

#define MAX_PATIENTS 100
#define BASE_FEE 150000

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main(void) {
    int i;
    int queue_ids[MAX_PATIENTS];
    int ages[MAX_PATIENTS];
    int has_insurance[MAX_PATIENTS];
    int fees[MAX_PATIENTS];

    int n = 0;
    int cancel_index = -1;
    int total_revenue = 0;
    int priority_count = 0;

    while (1) {
        printf("Nhap so luong benh nhan ban dau (0 - %d): ", MAX_PATIENTS);
        if (scanf("%d", &n) == 1 && n >= 0 && n <= MAX_PATIENTS) {
            break;
        }
        printf("Loi: So luong khong hop le. Vui long nhap lai!\n");
        clear_input_buffer();
    }

    for (i = 0; i < n; i++) {
        printf("\n--- Nhap benh nhan thu %d ---\n", i + 1);

        printf("Ma so thu tu kham (Queue ID): ");
        while (scanf("%d", &queue_ids[i]) != 1) {
            printf("Ma khong hop le, nhap lai: ");
            clear_input_buffer();
        }

        while (1) {
            printf("Tuoi (1 - 120): ");
            if (scanf("%d", &ages[i]) == 1 && ages[i] >= 1 && ages[i] <= 120) {
                break;
            }
            printf("Tuoi khong hop le. Vui long nhap lai!\n");
            clear_input_buffer();
        }

        while (1) {
            printf("Trang thai BHYT (1: Co, 0: Khong): ");
            if (scanf("%d", &has_insurance[i]) == 1 && (has_insurance[i] == 0 || has_insurance[i] == 1)) {
                break;
            }
            printf("Trang thai BHYT chi nhan gia tri 0 hoac 1. Nhap lai!\n");
            clear_input_buffer();
        }

        if (has_insurance[i] == 1) {
            fees[i] = (BASE_FEE * 20) / 100;
        } else {
            fees[i] = BASE_FEE;
        }

        total_revenue += fees[i];
        if (ages[i] >= 70) {
            priority_count++;
        }
    }

    printf("\n========================================================================\n");
    printf("                  DANH SACH HANG CHO KHAM BAN DAU                       \n");
    printf("========================================================================\n");
    printf("%-7s %-10s %-8s %-12s %-15s %-12s\n", "Chi So", "Queue ID", "Tuoi", "BHYT", "Phi Kham (VND)", "Phan Loai");
    printf("------------------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%-7d %-10d %-8d %-12s %-15d %-12s\n",
               i,
               queue_ids[i],
               ages[i],
               (has_insurance[i] == 1) ? "Co" : "Khong",
               fees[i],
               (ages[i] >= 70) ? "UU TIEN" : "Thuong");
    }
    printf("------------------------------------------------------------------------\n");
    printf("Tong doanh thu du kien : %d VND\n", total_revenue);
    printf("Tong ca uu tien        : %d ca\n", priority_count);
    printf("========================================================================\n");

    if (n == 0) {
        printf("\nHang cho rong, khong co luot kham de huy.\n");
        return 0;
    }

    while (1) {
        printf("\nNhap chi so K can huy (0 <= K < %d): ", n);
        if (scanf("%d", &cancel_index) == 1 && cancel_index >= 0 && cancel_index < n) {
            break;
        }
        printf("Loi: Chi so K nam ngoai pham vi hang cho active. Nhap lai!\n");
        clear_input_buffer();
    }

    total_revenue -= fees[cancel_index];
    if (ages[cancel_index] >= 70) {
        priority_count--;
    }

    for (i = cancel_index; i < n - 1; i++) {
        queue_ids[i] = queue_ids[i + 1];
        ages[i] = ages[i + 1];
        has_insurance[i] = has_insurance[i + 1];
        fees[i] = fees[i + 1];
    }
    n--;

    printf("\n========================================================================\n");
    printf("             DANH SACH HANG CHO SAU KHI HUY VI TRI %d                   \n", cancel_index);
    printf("========================================================================\n");
    if (n == 0) {
        printf("Hang cho hien tai da het benh nhan.\n");
    } else {
        printf("%-7s %-10s %-8s %-12s %-15s %-12s\n", "Chi So", "Queue ID", "Tuoi", "BHYT", "Phi Kham (VND)", "Phan Loai");
        printf("------------------------------------------------------------------------\n");
        for (i = 0; i < n; i++) {
            printf("%-7d %-10d %-8d %-12s %-15d %-12s\n",
                   i,
                   queue_ids[i],
                   ages[i],
                   (has_insurance[i] == 1) ? "Co" : "Khong",
                   fees[i],
                   (ages[i] >= 70) ? "UU TIEN" : "Thuong");
        }
    }
    printf("------------------------------------------------------------------------\n");
    printf("Tong doanh thu cap nhat : %d VND\n", total_revenue);
    printf("Tong ca uu tien con lai : %d ca\n", priority_count);
    printf("========================================================================\n");

    return 0;
}
