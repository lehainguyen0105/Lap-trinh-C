#include <stdio.h>

struct DeviceUnoptimized {
    char status;
    int id;
    char errorCode;
    float voltage;
    char isAlert;
    float current;
    float powerMeasured;
    float operatingMinutes;
};

struct DeviceOptimized {
    int id;
    float voltage;
    float current;
    float powerMeasured;
    float operatingMinutes;
    char status;
    char errorCode;
    char isAlert;
};

int main(void) {
    printf("=== SO SANH DUNG LUONG BO NHO (MEMORY ALIGNMENT) ===\n");
    printf("Kich thuoc struct chua toi uu : %lu bytes\n", (unsigned long)sizeof(struct DeviceUnoptimized));
    printf("Kich thuoc struct da toi uu   : %lu bytes\n", (unsigned long)sizeof(struct DeviceOptimized));
    printf("Tiet kiem bo nho              : %lu bytes\n", 
           (unsigned long)(sizeof(struct DeviceUnoptimized) - sizeof(struct DeviceOptimized)));
    printf("====================================================\n\n");

    struct DeviceOptimized dev;
    int statusInput;
    float pCalc;
    float pDiff;
    float kWh;

    printf("Nhap ma thiet bi (ID): ");
    scanf("%d", &dev.id);

    printf("Nhap trang thai thiet bi (0 - Tat, 1 - Bat): ");
    if (scanf("%d", &statusInput) != 1 || (statusInput != 0 && statusInput != 1)) {
        printf("\n[LOI HE THONG] Trang thai khong hop le (chi nhan 0 hoac 1)!\n");
        return 1;
    }
    dev.status = (char)statusInput;

    printf("Nhap dien ap U (Volt): ");
    if (scanf("%f", &dev.voltage) != 1 || dev.voltage <= 0.0f) {
        printf("\n[LOI HE THONG] Dien ap phai lon hon 0!\n");
        return 1;
    }

    printf("Nhap dong dien I (Ampere): ");
    if (scanf("%f", &dev.current) != 1 || dev.current < 0.0f) {
        printf("\n[LOI HE THONG] Dong dien khong duoc nho hon 0!\n");
        return 1;
    }

    printf("Nhap cong suat do tu cam bien (Watt): ");
    if (scanf("%f", &dev.powerMeasured) != 1 || dev.powerMeasured < 0.0f) {
        printf("\n[LOI HE THONG] Cong suat do duoc khong hop le!\n");
        return 1;
    }

    printf("Nhap thoi gian hoat dong (phut): ");
    if (scanf("%f", &dev.operatingMinutes) != 1 || dev.operatingMinutes < 0.0f) {
        printf("\n[LOI HE THONG] Thoi gian hoat dong khong duoc am!\n");
        return 1;
    }

    pCalc = dev.voltage * dev.current;

    printf("\n================ KET QUA GIAM SAT DIEN NANG ================\n");
    printf("Thiet bi ID           : %d\n", dev.id);
    printf("Trang thai            : %s\n", (dev.status == 1) ? "BAT" : "TAT");
    printf("Cong suat tinh toan   : %.2f W\n", pCalc);
    printf("Cong suat do duoc     : %.2f W\n", dev.powerMeasured);

    if (dev.status == 1 && pCalc > 0.0f) {
        pDiff = dev.powerMeasured - pCalc;
        if (pDiff < 0.0f) {
            pDiff = -pDiff;
        }
        if (pDiff > 0.05f * pCalc) {
            printf("[CANH BAO] Cam bien cong suat bao sai lech (> 5%%)!\n");
        }
    }

    if (dev.current > 30.0f || pCalc > 6600.0f) {
        printf("[CANH BAO NGUY HIEM] QUA TAI NGUY HIEM (I > 30A hoac P > 6600W)!\n");
    }

    if (dev.status == 0 && dev.current > 0.05f) {
        printf("[CANH BAO AN TOAN] RO RI DIEN HOAC TAI AN (Thiet bi TAT nhung I = %.3f A)!\n", dev.current);
    }

    if (dev.status == 1) {
        kWh = (pCalc * (dev.operatingMinutes / 60.0f)) / 1000.0f;
    } else {
        kWh = 0.0f;
    }

    printf("Thoi gian hoat dong   : %.1f phut\n", dev.operatingMinutes);
    printf("Dien nang tieu thu    : %.4f kWh\n", kWh);
    printf("============================================================\n");

    return 0;
}
