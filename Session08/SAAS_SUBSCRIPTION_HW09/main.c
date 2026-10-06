#include <stdio.h>
#include <string.h>

#define MAX_ACCOUNTS 100

struct Account {
    int user_id;
    char username[50];
    int plan_type;
    int days_overdue;
    int active_devices;
    long long final_fee;
    int was_downgraded;
};

int main(void) {
    struct Account accounts[MAX_ACCOUNTS];
    int n;
    int i;
    int downgraded_count = 0;
    long long total_revenue = 0;

    printf("Nhap so luong tai khoan (1 - %d): ", MAX_ACCOUNTS);
    while (scanf("%d", &n) != 1 || n < 1 || n > MAX_ACCOUNTS) {
        printf("So luong khong hop le! Vui long nhap lai (1 - %d): ", MAX_ACCOUNTS);
        while (getchar() != '\n');
    }

    for (i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin tai khoan thu %d ---\n", i + 1);

        printf("Nhap Ma TK (user_id): ");
        while (scanf("%d", &accounts[i].user_id) != 1) {
            printf("Ma TK khong hop le! Nhap lai: ");
            while (getchar() != '\n');
        }

        printf("Nhap Ten TK (username): ");
        scanf("%49s", accounts[i].username);

        printf("Nhap Loai goi (1: Free, 2: Personal, 3: Family): ");
        while (scanf("%d", &accounts[i].plan_type) != 1 || accounts[i].plan_type < 1 || accounts[i].plan_type > 3) {
            printf("Loai goi khong hop le! Nhap lai (1 - 3): ");
            while (getchar() != '\n');
        }

        printf("Nhap So ngay no cuoc (days_overdue >= 0): ");
        while (scanf("%d", &accounts[i].days_overdue) != 1 || accounts[i].days_overdue < 0) {
            printf("So ngay no cuoc khong duoc am! Nhap lai: ");
            while (getchar() != '\n');
        }

        printf("Nhap So thiet bi dang ket noi (active_devices >= 0): ");
        while (scanf("%d", &accounts[i].active_devices) != 1 || accounts[i].active_devices < 0) {
            printf("So thiet bi khong duoc am! Nhap lai: ");
            while (getchar() != '\n');
        }

        accounts[i].was_downgraded = 0;
        accounts[i].final_fee = 0;

        if (accounts[i].days_overdue >= 3) {
            if (accounts[i].plan_type != 1) {
                accounts[i].was_downgraded = 1;
                downgraded_count++;
            }
            accounts[i].plan_type = 1;
            accounts[i].final_fee = 0;
        } else {
            if (accounts[i].plan_type == 1) {
                accounts[i].final_fee = 0;
            } else if (accounts[i].plan_type == 2) {
                accounts[i].final_fee = 120000;
                if (accounts[i].active_devices > 1) {
                    accounts[i].final_fee += (long long)(accounts[i].active_devices - 1) * 30000;
                }
            } else if (accounts[i].plan_type == 3) {
                accounts[i].final_fee = 250000;
            }
        }

        total_revenue += accounts[i].final_fee;
    }

    printf("\n========================================================================================\n");
    printf("                  BANG DOI SOAT & XU LY NO CUOC KHACH HANG (STREAMFLOW)                 \n");
    printf("========================================================================================\n");
    printf("%-8s %-15s %-10s %-12s %-12s %-18s %-10s\n", 
           "MA TK", "TEN TK", "MA GOI", "THIET BI", "NGAY NO", "PHI THUC THU(VND)", "GHI CHU");
    printf("----------------------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-8d %-15s %-10d %-12d %-12d %-18lld %-10s\n",
               accounts[i].user_id,
               accounts[i].username,
               accounts[i].plan_type,
               accounts[i].active_devices,
               accounts[i].days_overdue,
               accounts[i].final_fee,
               accounts[i].was_downgraded ? "HA CAP" : "BINH THUONG");
    }

    printf("----------------------------------------------------------------------------------------\n");
    printf("Tong so tai khoan bi ha cap ve goi Free: %d\n", downgraded_count);
    printf("Tong doanh thu thuc thu trong ky       : %lld VND\n", total_revenue);
    printf("========================================================================================\n");

    return 0;
}
