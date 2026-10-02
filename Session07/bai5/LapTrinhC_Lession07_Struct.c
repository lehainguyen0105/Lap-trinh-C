#include <stdio.h>

struct EnvironmentSensor {
    int sensor_id;
    char room_name[50];
    float temperature;
    float humidity;
    int battery_level;
};

int main(void) {
    struct EnvironmentSensor sensor;

    if (scanf("%d", &sensor.sensor_id) != 1) {
        return 0;
    }
    if (scanf("%49s", sensor.room_name) != 1) {
        return 0;
    }
    if (scanf("%f", &sensor.temperature) != 1) {
        return 0;
    }
    if (scanf("%f", &sensor.humidity) != 1) {
        return 0;
    }
    if (scanf("%d", &sensor.battery_level) != 1) {
        return 0;
    }

    if (sensor.battery_level < 0 || sensor.battery_level > 100) {
        printf("Loi: Dung luong pin khong hop le!\n");
        return 0;
    }

    printf("--- HE THONG MONITORING SMART_HOME_IOT ---\n");
    printf("Ma cam bien: %d\n", sensor.sensor_id);
    printf("Phong: %s\n", sensor.room_name);
    printf("Nhiet do: %.2f C\n", sensor.temperature);
    printf("Do am: %.2f %%\n", sensor.humidity);
    printf("Dung luong pin: %d %%\n", sensor.battery_level);

    if (sensor.battery_level < 10 || sensor.temperature > 60.0f) {
        printf("Trang thai: CRITICAL\n");
    } else if ((sensor.battery_level >= 10 && sensor.battery_level <= 20) ||
               (sensor.temperature >= 40.0f && sensor.temperature <= 60.0f) ||
               (sensor.humidity > 85.0f)) {
        printf("Trang thai: WARNING\n");
    } else {
        printf("Trang thai: SAFE\n");
    }

    return 0;
}
