#include <stdio.h>
#include <string.h>

struct SmartDevice {
    int id;
    char name[30];
    int status;
    float powerWatt;
};

struct EnergySensor {
    float voltage;
    float current;
    int unoccupancyMinutes;
};

struct PowerReport {
    float totalPowerWatt;
    float totalCurrentAmp;
    float totalKWh;
    int isOverloaded;
};

int main(void) {
    struct SmartDevice ac;
    ac.id = 101;
    strcpy(ac.name, "Dieu hoa nhiet do");
    ac.status = 1;
    ac.powerWatt = 2200.0f;

    struct SmartDevice light;
    light.id = 102;
    strcpy(light.name, "He thong den chieu sang");
    light.status = 1;
    light.powerWatt = 150.0f;

    struct EnergySensor sensor;
    sensor.voltage = 220.0f;
    sensor.current = 10.68f;
    sensor.unoccupancyMinutes = 20;

    struct PowerReport report;
    report.totalPowerWatt = 0.0f;
    report.totalCurrentAmp = 0.0f;
    report.totalKWh = 0.0f;
    report.isOverloaded = 0;

    float operatingHours = 4.0f;

    if (sensor.unoccupancyMinutes > 15) {
        if (ac.status == 1) {
            ac.status = 0;
            ac.powerWatt = 0.0f;
        }
    }

    report.totalPowerWatt = 0.0f;
    if (ac.status == 1) {
        report.totalPowerWatt += ac.powerWatt;
    }
    if (light.status == 1) {
        report.totalPowerWatt += light.powerWatt;
    }

    if (sensor.voltage > 0.0f) {
        report.totalCurrentAmp = report.totalPowerWatt / sensor.voltage;
    } else {
        report.totalCurrentAmp = 0.0f;
    }

    if (report.totalCurrentAmp > 30.0f) {
        report.isOverloaded = 1;
    } else {
        report.isOverloaded = 0;
    }

    report.totalKWh = (report.totalPowerWatt * operatingHours) / 1000.0f;

    printf("====================================================================\n");
    printf("           SMART HOME CENTRAL GATEWAY - DASHBOARD MONITOR           \n");
    printf("====================================================================\n");
    printf("1. THONG TIN THIET BI PHONG KHACH:\n");
    printf("   [ID: %d] %-25s | Trang thai: %-3s | Cong suat: %7.1f W\n",
           ac.id, ac.name, (ac.status == 1 ? "ON" : "OFF"), ac.powerWatt);
    printf("   [ID: %d] %-25s | Trang thai: %-3s | Cong suat: %7.1f W\n",
           light.id, light.name, (light.status == 1 ? "ON" : "OFF"), light.powerWatt);
    printf("--------------------------------------------------------------------\n");
    printf("2. CHI SO CAM BIEN TRUNG TAM (REAL-TIME SENSOR):\n");
    printf("   - Dien ap hoat dong           : %.1f V\n", sensor.voltage);
    printf("   - Dong dien do duoc           : %.2f A\n", sensor.current);
    printf("   - Thoi gian phong trong       : %d phut\n", sensor.unoccupancyMinutes);
    if (sensor.unoccupancyMinutes > 15) {
        printf("   >> [KICH BAN TU DONG] Phong trong > 15 phut: Da tat Dieu hoa!\n");
    }
    printf("--------------------------------------------------------------------\n");
    printf("3. BAO CAO TONG HOP NANG LUONG (POWER REPORT):\n");
    printf("   - Tong cong suat dang tai     : %.1f W\n", report.totalPowerWatt);
    printf("   - Tong dong dien tinh toan    : %.2f A\n", report.totalCurrentAmp);
    printf("   - Dien nang tieu thu (%.1fh)    : %.3f kWh\n", operatingHours, report.totalKWh);
    printf("   - Canh bao an toan (> 30A)    : %s\n",
           (report.isOverloaded == 1 ? "NGUY HIEM: QUA TAI NGUON DIEN!" : "AN TOAN"));
    printf("====================================================================\n");

    return 0;
}
