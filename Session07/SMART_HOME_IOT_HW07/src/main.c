#include <stdio.h>
#include <string.h>

struct SmartDevice {
    int deviceID;
    char deviceName[50];
    int status;
    float ratedPowerKW;
};

struct EnergySensor {
    float voltageVolts;
    float currentAmperes;
    int unoccupancyMinutes;
};

int main(void) {
    struct SmartDevice dev;
    struct EnergySensor sensor;
    float operatingHours;
    float totalKWh;
    float totalBill = 0.0f;
    float remainKWh;
    size_t len;

    printf("=== NHAP THONG TIN THIET BI (SMART DEVICE) ===\n");
    printf("Nhap ma thiet bi (ID): ");
    scanf("%d", &dev.deviceID);
    while (getchar() != '\n');

    printf("Nhap ten thiet bi: ");
    fgets(dev.deviceName, sizeof(dev.deviceName), stdin);
    len = strlen(dev.deviceName);
    if (len > 0 && dev.deviceName[len - 1] == '\n') {
        dev.deviceName[len - 1] = '\0';
    }

    printf("Nhap trang thai ban dau (1 - Bat, 0 - Tat): ");
    scanf("%d", &dev.status);

    printf("Nhap cong suat dinh muc (kW): ");
    scanf("%f", &dev.ratedPowerKW);
    while (getchar() != '\n');

    printf("\n=== NHAP THONG SO CAM BIEN (ENERGY SENSOR) ===\n");
    printf("Nhap dien ap do duoc (V): ");
    scanf("%f", &sensor.voltageVolts);

    printf("Nhap dong dien do duoc (A): ");
    scanf("%f", &sensor.currentAmperes);

    printf("Nhap thoi gian vang nguoi (phut): ");
    scanf("%d", &sensor.unoccupancyMinutes);

    printf("\n=== NHAP THOI GIAN HOAT DONG TRONG THANG ===\n");
    printf("Nhap so gio van hanh (0 < gio <= 744): ");
    scanf("%f", &operatingHours);
    while (getchar() != '\n');

    if (sensor.voltageVolts < 0 || sensor.currentAmperes < 0 || sensor.unoccupancyMinutes < 0) {
        printf("\n[LOI HE THONG] Thong so cam bien bat thuong (< 0). Phat hien hong hoc phan cung!\n");
        return 1;
    }

    if (dev.ratedPowerKW <= 0) {
        printf("\n[LOI HE THONG] Cong suat dinh muc cua thiet bi phai lon hon 0!\n");
        return 1;
    }

    if (operatingHours <= 0 || operatingHours > 744.0f) {
        printf("\n[LOI HE THONG] Thoi gian van hanh khong hop le (phai > 0 va <= 744 gio trong thang)!\n");
        return 1;
    }

    printf("\n================ KET QUA XU LY DIEU KHIEN ================\n");

    if (sensor.currentAmperes > 30.0f) {
        dev.status = 0;
        printf("[CANH BAO NGUY HIEM] Dong dien vuot nguong 30A (%.1f A)!\n", sensor.currentAmperes);
        printf("-> Kich hoat ngat khan cap de phong chong chay no.\n");
    } else if (dev.status == 1 && sensor.unoccupancyMinutes >= 15) {
        dev.status = 0;
        printf("[TIET KIEM NANG LUONG] Phong trong %d phut (>= 15 phut).\n", sensor.unoccupancyMinutes);
        printf("-> Tu dong ngat thiet bi de tiet kiem dien.\n");
    }

    printf("Trang thai hoat dong sau cung cua thiet bi: %s\n", dev.status == 1 ? "BAT" : "TAT");

    totalKWh = dev.ratedPowerKW * operatingHours;
    remainKWh = totalKWh;

    if (remainKWh > 200.0f) {
        totalBill += (remainKWh - 200.0f) * 2729.0f;
        remainKWh = 200.0f;
    }
    if (remainKWh > 100.0f) {
        totalBill += (remainKWh - 100.0f) * 2167.0f;
        remainKWh = 100.0f;
    }
    if (remainKWh > 50.0f) {
        totalBill += (remainKWh - 50.0f) * 1866.0f;
        remainKWh = 50.0f;
    }
    if (remainKWh > 0.0f) {
        totalBill += remainKWh * 1806.0f;
    }

    printf("----------------------------------------------------------\n");
    printf("Thiet bi                    : %s (ID: %d)\n", dev.deviceName, dev.deviceID);
    printf("Cong suat dinh muc          : %.2f kW\n", dev.ratedPowerKW);
    printf("Thoi gian hoat dong du kien : %.1f gio\n", operatingHours);
    printf("Tong san luong dien tieu thu: %.2f kWh\n", totalKWh);
    printf("Tien dien EVN (chua VAT)    : %.0f VND\n", totalBill);
    printf("==========================================================\n");

    return 0;
}
