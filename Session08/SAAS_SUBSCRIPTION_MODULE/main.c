#include <stdio.h>
#include <string.h>

#define MAX_SUBSCRIPTIONS 50

struct Subscription {
    int user_id;
    char account_name[31];
    int plan_type;
    int active_devices;
    int max_devices;
    int days_overdue;
    int account_status;
    int is_device_violated;
};

int main(void) {
    struct Subscription list[MAX_SUBSCRIPTIONS];
    int n;
    int i;
    int downgraded_count = 0;
    int violated_device_count = 0;

    printf("====================================================================\n");
    printf("   HE THONG RA SOAT & HA CAP DANG KY SAAS (STREAMFLIX AUDITOR)      \n");
    printf("====================================================================\n");
    printf("Nhap so luong tai khoan can ra soat (1 - %d): ", MAX_SUBSCRIPTIONS);
    
    while (scanf("%d", &n) != 1 || n < 1 || n > MAX_SUBSCRIPTIONS) {
        printf("So luong khong hop le! Vui long nhap lai (1 - %d): ", MAX_SUBSCRIPTIONS);
        while (getchar() != '\n');
    }

    for (i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin tai khoan thu %d ---\n", i + 1);

        printf("Ma tai khoan (user_id): ");
        while (scanf("%d", &list[i].user_id) != 1) {
            printf("Ma tai khoan khong hop le! Nhap lai: ");
            while (getchar() != '\n');
        }

        printf("Ten tai khoan / Email: ");
        scanf("%30s", list[i].account_name);

        printf("Hang goi dich vu (1: Free, 2: Individual, 3: Family): ");
        while (scanf("%d", &list[i].plan_type) != 1 || list[i].plan_type < 1 || list[i].plan_type > 3) {
            printf("Hang goi khong hop le! Nhap lai (1 - 3): ");
            while (getchar() != '\n');
        }

        printf("So thiet bi dang ket noi (active_devices >= 0): ");
        while (scanf("%d", &list[i].active_devices) != 1 || list[i].active_devices < 0) {
            printf("So thiet bi khong hop le! Nhap lai: ");
            while (getchar() != '\n');
        }

        printf("So ngay cham thanh toan cuoc (days_overdue >= 0): ");
        while (scanf("%d", &list[i].days_overdue) != 1 || list[i].days_overdue < 0) {
            printf("So ngay no khong hop le! Nhap lai: ");
            while (getchar() != '\n');
        }

        if (list[i].plan_type == 3) {
            list[i].max_devices = 5;
        } else {
            list[i].max_devices = 1;
        }
        list[i].account_status = 1;
        list[i].is_device_violated = 0;

        if (list[i].days_overdue > 3) {
            if (list[i].plan_type != 1) {
                downgraded_count++;
            }
            list[i].plan_type = 1;
            list[i].max_devices = 1;
            list[i].account_status = 0;
        }

        if (list[i].active_devices > list[i].max_devices) {
            list[i].is_device_violated = 1;
            violated_device_count++;
        }
    }

    printf("\n=========================================================================================================\n");
    printf("                               BANG TONG HOP TAI KHOAN SAU RA SOAT                                      \n");
    printf("=========================================================================================================\n");
    printf("%-8s %-20s %-15s %-18s %-12s %-15s %-12s\n",
           "USER ID", "ACCOUNT NAME", "PLAN TYPE", "DEVICES (ACT/MAX)", "DAYS OVERDUE", "ACCOUNT STATUS", "CANH BAO");
    printf("---------------------------------------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        char *plan_str;
        if (list[i].plan_type == 3) {
            plan_str = "Family";
        } else if (list[i].plan_type == 2) {
            plan_str = "Individual";
        } else {
            plan_str = "Free";
        }

        char device_info[20];
        sprintf(device_info, "%d / %d", list[i].active_devices, list[i].max_devices);

        printf("%-8d %-20s %-15s %-18s %-12d %-15s %-12s\n",
               list[i].user_id,
               list[i].account_name,
               plan_str,
               device_info,
               list[i].days_overdue,
               (list[i].account_status == 1 ? "Active" : "Downgraded"),
               (list[i].is_device_violated == 1 ? "VUOT THIET BI" : "HOP LE"));
    }

    printf("=========================================================================================================\n");
    printf("                                 BAO CAO THONG KE VAN HANH                                               \n");
    printf("=========================================================================================================\n");
    printf("1. Tong so tai khoan da ra soat                                          : %d\n", n);
    printf("2. So luong tai khoan bi tu dong ha cap ve goi Free (No cuoc > 3 ngay)   : %d\n", downgraded_count);
    printf("3. So luong tai khoan dang vi pham vuot qua so thiet bi cho phep        : %d\n", violated_device_count);
    printf("=========================================================================================================\n");

    return 0;
}
