# Báo Cáo Kỹ Thuật: Phân Tích Trade-off & Tái Cấu Trúc Hệ Thống TripFareEngine (GrabRide)

## 1. Phân Tích Bài Toán (I/O Analysis)

### Dữ Liệu Đầu Vào (Input)
* `distance_km` (kiểu `double`): Quãng đường di chuyển thực tế của chuyến đi (km).
  * Ràng buộc nghiệp vụ: Bắt buộc `distance_km > 0.0`.
* `is_surge` (kiểu `int`): Trạng thái phụ phí thời tiết xấu hoặc khung giờ cao điểm.
  * Ràng buộc nghiệp vụ: Chỉ nhận giá trị `0` (Bình thường) hoặc `1` (Thời tiết xấu / Cao điểm).

### Dữ Liệu Đầu Ra (Output)
* Cảnh báo lỗi chi tiết và hủy giao dịch ngay lập tức (Early Exit) nếu dữ liệu nhập vào vi phạm điều kiện an toàn.
* Hóa đơn chi tiết hiển thị trên màn hình console khi dữ liệu hợp lệ:
  * Quãng đường di chuyển thực tế (`%.2f km`).
  * Cước phí cơ bản theo khoảng cách (`%.0f VND`).
  * Trạng thái áp dụng phụ phí (`1.0x` hoặc `1.2x`).
  * Tổng tiền cước thanh toán cuối cùng (`%.0f VND`).

---

## 2. Đề Xuất & Phân Tích Đa Giải Pháp (Multi-Solution Analysis)

### Giải Pháp 1: Lồng ghép điều kiện sâu (Legacy / Deeply Nested IF)
* **Cơ chế hoạt động:** Kiểm tra lồng ghép đồng thời cả quãng đường di chuyển và trạng thái phụ phí bên trong các khối `if/else` đa tầng để tính tiền cước trực tiếp ở từng nhánh.
* **Minh họa mã nguồn:**
  ```c
  if (distance_km <= 2.0) {
      if (is_surge == 1) {
          total_fare = 12000.0 * 1.2;
      } else {
          total_fare = 12000.0;
      }
  } else {
      if (is_surge == 1) {
          total_fare = (12000.0 + (distance_km - 2.0) * 4500.0) * 1.2;
      } else {
          total_fare = 12000.0 + (distance_km - 2.0) * 4500.0;
      }
  }
  Giải Pháp 2: Phân tách điều kiện biên & Tính toán theo bước (Refactored / Guard Clauses & Step-by-Step)
Cơ chế hoạt động: Phân chia bài toán thành 3 tầng xử lý tuyến tính độc lập:

Tầng Guard Clauses: Đưa toàn bộ kiểm tra điều kiện biên sai lệch lên đầu hàm, phát hiện lỗi là ngắt chương trình ngay (Early Return/Exit).

Bước 1 (Base Fare): Tính cước phí cơ bản thuần túy theo cự ly di chuyển.

Bước 2 (Surge Surcharge): Áp dụng hệ số phụ phí cao điểm độc lập ở bước cuối.

Minh họa mã nguồn:

C
// Guard Clauses: Chặn lỗi sớm
if (distance_km <= 0.0 || (is_surge != 0 && is_surge != 1)) {
    return 0;
}

// Bước 1: Tính cước cơ bản
if (distance_km <= 2.0) {
    base_fare = 12000.0;
} else {
    base_fare = 12000.0 + (distance_km - 2.0) * 4500.0;
}

// Bước 2: Nhân hệ số phụ phí nếu có
if (is_surge == 1) {
    total_fare = base_fare * 1.2;
} else {
    total_fare = base_fare;
}
| Tiêu chí đánh giá | Giải pháp 1 (Deeply Nested IF) | Giải pháp 2 (Guard Clauses & Step-by-Step) |
| :--- | :--- | :--- |
| **Độ phức tạp đọc hiểu (Cognitive Complexity)** | **Cao:** Luồng điều khiển phân nhánh lồng nhau khiến lập trình viên phải nhớ ngữ cảnh điều kiện của nhiều tầng. | **Thấp:** Luồng thực thi dạng tuyến tính (đường thẳng phẳng), đọc tuần tự từ trên xuống dưới rất trực quan. |
| **Trùng lặp mã nguồn (Code Duplication)** | **Rất cao:** Phép nhân phụ phí `* 1.2` và công thức cơ sở bị lặp lại rải rác ở 4 nhánh rẽ khác nhau. | **Triệt tiêu hoàn toàn:** Công thức phụ phí chỉ xuất hiện duy nhất 1 lần ở bước tính tương ứng. |
| **Khả năng bảo trì (Maintainability)** | **Kém:** Khi thay đổi tỷ lệ phụ phí hoặc giá cước mở cửa 2 km đầu, phải sửa đồng thời nhiều nơi, rủi ro sót lỗi cao. | **Tối ưu:** Mỗi công thức nghiệp vụ được cô lập tại một bước riêng biệt, chỉ cần chỉnh sửa đúng một dòng duy nhất. |
| **Khả năng mở rộng (Extensibility)** | **Khó khăn:** Khi thêm yêu cầu mới (như mã giảm giá voucher, phụ phí đêm), số nhánh sẽ tăng theo cấp số nhân (2^n). | **Rất cao:** Dễ dàng nối thêm các bước tính toán mới vào cuối chuỗi mà không làm xáo trộn logic đã có. |
