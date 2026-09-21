# Báo Cáo Phân Tích & Thiết Kế Phân Hệ Tính Cước Chuyến Xe Đa Yếu Tố GrabRide

## 1. Phân Tích Bài Toán (I/O Analysis)

### Dữ Liệu Đầu Vào (Input)
* `vehicle_type` (Kiểu `int`): Mã phân loại loại hình phương tiện dịch vụ.
  * Hợp lệ: `1` (GrabBike) hoặc `2` (GrabCar).
* `distance` (Kiểu `double`): Cự ly quãng đường di chuyển (km).
  * Hợp lệ: $0.0 < \text{distance} \le 300.0$.
* `is_peak_or_rain` (Kiểu `int`): Cờ trạng thái điều kiện thời tiết hoặc khung giờ cao điểm.
  * Hợp lệ: `0` (Bình thường) hoặc `1` (Có phụ phí cao điểm / trời mưa).

### Dữ Liệu Đầu Ra (Output)
* Thông báo lỗi cụ thể và dừng chương trình ngay khi phát hiện dữ liệu nhập vào vi phạm quy tắc an toàn.
* Hóa đơn chi tiết hiển thị trên console khi dữ liệu hợp lệ:
  * Loại phương tiện (`GrabBike` hoặc `GrabCar`).
  * Quãng đường di chuyển (`%.2f km`).
  * Cước phí cơ sở (`%.0f VND`).
  * Phụ phí thời tiết/cao điểm (`%.0f VND`).
  * Tổng tiền cước thanh toán cuối cùng (`%.0f VND`).

---

## 2. Đề Xuất Giải Pháp & Tư Duy Rẽ Nhánh

Chương trình áp dụng kỹ thuật **Lập trình phòng thủ (Defensive Programming)** và cấu trúc điều khiển rẽ nhánh đa tầng:
1. **Tầng lọc dữ liệu (Validation Guard):**
   * Sử dụng câu lệnh `if` kiểm tra tính hợp lệ của `vehicle_type`, `distance`, `is_peak_or_rain`.
   * Nếu bất kỳ dữ liệu nào nằm ngoài miền giá trị cho phép, in cảnh báo lỗi và kết thúc thực thi ngay lập tức (`Early Exit` qua `return 0;`), không thực hiện tính toán tài chính.
2. **Tầng tính cước cơ sở (Base Fare Calculation):**
   * Dùng `if (vehicle_type == 1)` để rẽ nhánh GrabBike và `else if (vehicle_type == 2)` để rẽ nhánh GrabCar.
   * Trong mỗi nhánh phương tiện, lồng cấu trúc `if (distance <= 2.0)` để giữ nguyên cước trần tối thiểu của 2 km đầu (tránh lỗi chia nhỏ cước với quãng đường ngắn) và `else` để cộng thêm đơn giá lũy tiến cho phần vượt ngưỡng 2 km (`distance - 2.0`).
3. **Tầng tính phụ phí & tổng tiền (Dynamic Surcharge Calculation):**
   * Sử dụng cấu trúc `if (is_peak_or_rain == 1)` để áp dụng tỷ lệ phụ phí 20% trên cước cơ sở (`surcharge = base_fare * 0.2`).
   * Tổng cước cuối cùng: `total_fare = base_fare + surcharge`.

---

## 3. Các Bước Xử Lý Tuần Tự (Algorithm & Workflow)

1. **Bước 1 (Tiếp nhận dữ liệu):** Nhập tuần tự `vehicle_type`, `distance`, `is_peak_or_rain` từ bàn phím qua hàm `scanf`.
2. **Bước 2 (Kiểm soát lỗi biên & Tính toàn vẹn dữ liệu):**
   * Kiểm tra nếu `distance <= 0.0` hoặc `distance > 300.0`: Báo lỗi cự ly bất thường và thoát.
   * Kiểm tra nếu `vehicle_type != 1` và `vehicle_type != 2`: Báo lỗi mã phương tiện và thoát.
   * Kiểm tra nếu `is_peak_or_rain != 0` và `is_peak_or_rain != 1`: Báo lỗi trạng thái phụ phí và thoát.
3. **Bước 3 (Xác định cước cơ sở):**
   * Nếu `vehicle_type == 1`:
     * Nếu `distance <= 2.0`: `base_fare = 12000.0`.
     * Ngược lại: `base_fare = 12000.0 + (distance - 2.0) * 4500.0`.
   * Nếu `vehicle_type == 2`:
     * Nếu `distance <= 2.0`: `base_fare = 25000.0`.
     * Ngược lại: `base_fare = 25000.0 + (distance - 2.0) * 10000.0`.
4. **Bước 4 (Xác định phụ phí biến đổi):**
   * Nếu `is_peak_or_rain == 1`: `surcharge = base_fare * 0.2`.
   * Ngược lại: `surcharge = 0.0`.
5. **Bước 5 (Quyết toán & Hiển thị):**
   * `total_fare = base_fare + surcharge`.
   * Xuất chi tiết hóa đơn thanh toán lên màn hình.

---

## 4. Bảng Test Cases Kiểm Thử Nghiệp Vụ

| STT | Kịch bản kiểm thử | Input (`vehicle_type`, `distance`, `is_peak_or_rain`) | Kết quả mong đợi |
| :--- | :--- | :--- | :--- |
| 1 | Chuyến GrabBike dưới 2 km, trời tạnh | `1`, `1.5`, `0` | Cước cơ sở: 12.000, Phụ phí: 0, Tổng: **12.000 VND** |
| 2 | Chuyến GrabBike 5 km, trời mưa | `1`, `5.0`, `1` | Base: $12000 + 3 \times 4500 = 25500$, Surcharge: 5100, Tổng: **30.600 VND** |
| 3 | Chuyến GrabCar 10 km, giờ cao điểm | `2`, `10.0`, `1` | Base: $25000 + 8 \times 10000 = 105000$, Surcharge: 21000, Tổng: **126.000 VND** |
| 4 | Khoảng cách âm hoặc bằng 0 | `1`, `-2.5`, `0` | In cảnh báo cự ly bất thường, hủy giao dịch |
| 5 | Khoảng cách vượt 300 km | `2`, `350.0`, `1` | In cảnh báo cự ly bất thường, hủy giao dịch |
| 6 | Nhập mã phương tiện không tồn tại | `3`, `5.0`, `0` | In cảnh báo mã phương tiện không hợp lệ, hủy giao dịch |
| 7 | Nhập trạng thái phụ phí sai | `1`, `5.0`, `2` | In cảnh báo trạng thái phụ phí không hợp lệ, hủy giao dịch |

---

## 5. Hướng Dẫn Biên Dịch & Chạy Thử

```bash
# Di chuyển vào thư mục bài tập
cd grab_ride_fare_calculator

# Biên dịch bằng GCC với các cờ cảnh báo chuẩn C11
gcc -Wall -Wextra -std=c11 main.c -o main

# Thực thi chương trình
./main
