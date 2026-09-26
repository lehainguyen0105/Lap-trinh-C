#include <stdio.h>

int main() {
    int queue_numbers[4] = {1001, 1002, 1003, 1004};

    int patient_position = 4; // Benh nhan vi tri thu 4 (1-based index)
    int new_queue_number = 1099;

    queue_numbers[patient_position - 1] = new_queue_number;

    printf("--- DANH SACH SO THU TU KHAM BENH ---\n");
    printf("Benh nhan 1 (Index 0): %d\n", queue_numbers[0]);
    printf("Benh nhan 2 (Index 1): %d\n", queue_numbers[1]);
    printf("Benh nhan 3 (Index 2): %d\n", queue_numbers[2]);
    printf("Benh nhan 4 (Index 3): %d\n", queue_numbers[3]);

    return 0;
}
