#include <stdio.h>

#define MAX_N 100

// Dinh nghia cau truc luu tru thong tin tai khoan nguoi dung SaaS
struct UserAccount {
    int account_id;     // Ma dinh danh tai khoan
    int plan_type;      // 0: Free, 1: Standard, 2: Premium
    int monthly_fee;    // Phi goi cuoc hang thang (VND)
    int remaining_days; // So ngay con lai (<= 0 nghia la da qua han)
    int active_devices; // So thiet bi dang ket noi dong thoi
};

int main(void) {
    struct UserAccount accounts[MAX_N];
    int n;
    int i, j;
    long long initial_mrr = 0;
    long long audited_mrr = 0;

    // Nhap so luong tai khoan can quan ly (1 <= n <= 100)
    printf("Nhap so luong tai khoan can quan ly (1 - %d): ", MAX_N);
    while (scanf("%d", &n) != 1 || n < 1 || n > MAX_N) {
        printf("So luong khong hop le! Vui long nhap lai (1 - %d): ", MAX_N);
        while (getchar() != '\n');
    }

    // Nhap thong tin chi tiet cho tung tai khoan
    for (i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin tai khoan thu %d ---\n", i + 1);

        printf("Ma tai khoan (account_id): ");
        while (scanf("%d", &accounts[i].account_id) != 1) {
            printf("Ma tai khoan khong hop le! Nhap lai: ");
            while (getchar() != '\n');
        }

        printf("Loai goi cuoc (0: Free, 1: Standard, 2: Premium): ");
        while (scanf("%d", &accounts[i].plan_type) != 1 || accounts[i].plan_type < 0 || accounts[i].plan_type > 2) {
            printf("Goi cuoc khong hop le! Nhap lai (0 - 2): ");
            while (getchar() != '\n');
        }

        printf("Phi goi cuoc nhap vao (monthly_fee): ");
        while (scanf("%d", &accounts[i].monthly_fee) != 1 || accounts[i].monthly_fee < 0) {
            printf("Phi khong hop le! Nhap lai (>= 0): ");
            while (getchar() != '\n');
        }

        printf("So ngay con lai (remaining_days, co the am neu qua han): ");
        while (scanf("%d", &accounts[i].remaining_days) != 1) {
            printf("So ngay khong hop le! Nhap lai: ");
            while (getchar() != '\n');
        }

        printf("So thiet bi ket noi (active_devices): ");
        while (scanf("%d", &accounts[i].active_devices) != 1) {
            printf("So thiet bi khong hop le! Nhap lai: ");
            while (getchar() != '\n');
        }

        // Tinh tong MRR ban dau dua tren du lieu goc nhap vao
        initial_mrr += accounts[i].monthly_fee;
    }

    // BUOC 1: KIEM TOAN & CHUAN HOA DU LIEU (DATA AUDITING & SANITIZATION)
    for (i = 0; i < n; i++) {
        // Xu ly ngoai le 3: So thiet bi bat thuong (<= 0) -> Chuan hoa ve toi thieu la 1
        if (accounts[i].active_devices <= 0) {
            accounts[i].active_devices = 1;
        }

        // Xu ly ngoai le 1: remaining_days <= 0 -> Tu dong ha cap ve goi Free (plan_type = 0)
        if (accounts[i].remaining_days <= 0) {
            accounts[i].plan_type = 0;
            accounts[i].monthly_fee = 0;
            if (accounts[i].remaining_days < 0) {
                accounts[i].remaining_days = 0; // Chuan hoa ve 0 de ghi nhan
            }
        } else {
            // Xu ly ngoai le 2: Chuan hoa monthly_fee theo dung quy chuan doanh nghiep neu con han
            if (accounts[i].plan_type == 1) {
                accounts[i].monthly_fee = 120000;
            } else if (accounts[i].plan_type == 2) {
                accounts[i].monthly_fee = 300000;
            } else {
                accounts[i].monthly_fee = 0;
            }
        }

        // Quy tac cuong che gioi han thiet bi ket noi theo hang goi cuoc hien tai
        if (accounts[i].plan_type == 0 && accounts[i].active_devices > 1) {
            accounts[i].active_devices = 1;
        } else if (accounts[i].plan_type == 1 && accounts[i].active_devices > 2) {
            accounts[i].active_devices = 2;
        } else if (accounts[i].plan_type == 2 && accounts[i].active_devices > 5) {
            accounts[i].active_devices = 5;
        }

        // Cong don doanh thu thuc te sau khi da hoan tat kiem toan chuan hoa
        audited_mrr += accounts[i].monthly_fee;
    }

    // BUOC 2: SAP XEP THEO THU TU UU TIEN (GIAI PHAP A - IN-PLACE STABLE INSERTION SORT)
    // - Cac tai khoan co phi (plan_type > 0) day len dau mang.
    // - Cac tai khoan co phi duoc xep theo monthly_fee giam dan.
    // - Neu bang monthly_fee, giu nguyen thu tu xuat hien ban dau (Stable Sort).
    // - Cac tai khoan Free (plan_type == 0) nam o cuoi mang theo thu tu ban dau.
    for (i = 1; i < n; i++) {
        struct UserAccount key = accounts[i];
        j = i - 1;

        while (j >= 0) {
            int key_is_paid = (key.plan_type > 0) ? 1 : 0;
            int j_is_paid = (accounts[j].plan_type > 0) ? 1 : 0;
            int should_swap = 0;

            if (key_is_paid > j_is_paid) {
                // key la tai khoan tra phi, accounts[j] la Free -> Day key len truoc
                should_swap = 1;
            } else if (key_is_paid == j_is_paid && key_is_paid == 1) {
                // Ca hai deu tra phi: So sanh theo monthly_fee giam dan (chi doi cho neu key lon hon)
                if (key.monthly_fee > accounts[j].monthly_fee) {
                    should_swap = 1;
                }
            }

            if (should_swap) {
                accounts[j + 1] = accounts[j];
                j--;
            } else {
                break;
            }
        }
        accounts[j + 1] = key;
    }

    // BUOC 3: XUAT BANG DANH SACH KET QUA KIEM TOAN
    printf("\n=========================================================================================\\n");
    printf("                  BANG KIEM TOAN VA SAP XEP TAI KHOAN SAAS (CLOUDSYNC)                  \\n");
    printf("=========================================================================================\\n");
    printf("%-5s %-12s %-12s %-18s %-15s %-12s\\n",
           "STT", "MA TK", "GOI CUOC", "PHI THANG (VND)", "NGAY CON LAI", "THIET BI");
    printf("-----------------------------------------------------------------------------------------\\n");

    for (i = 0; i < n; i++) {
        char *plan_name;
        if (accounts[i].plan_type == 2) {
            plan_name = "Premium";
        } else if (accounts[i].plan_type == 1) {
            plan_name = "Standard";
        } else {
            plan_name = "Free";
        }

        printf("%-5d %-12d %-12s %-18d %-15d %-12d\\n",
               i + 1,
               accounts[i].account_id,
               plan_name,
               accounts[i].monthly_fee,
               accounts[i].remaining_days,
               accounts[i].active_devices);
    }

    // BUOC 4: BAO CAO TONG HOP CHENH LECH DOANH THU MRR
    printf("=========================================================================================\\n");
    printf("BAO CAO DOANH THU DINH KY HANG THANG (MRR):\\n");
    printf("- Doanh thu du kien ban dau (chua kiem toan) : %lld VND\\n", initial_mrr);
    printf("- Doanh thu thuc te (sau khi kiem toan ha cap): %lld VND\\n", audited_mrr);
    printf("- Chenh lech that thoat do het han/sai lech : %lld VND\\n", initial_mrr - audited_mrr);
    printf("=========================================================================================\\n");

    return 0;
}
