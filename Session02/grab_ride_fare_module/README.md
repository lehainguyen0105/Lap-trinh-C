# Thiết Kế Kiến Trúc Dynamic Pricing Engine - Phân Hệ Tính Cước GrabRide

## 1. Phân Tích Bài Toán & Phạm Vi Kỹ Thuật

### Dữ Liệu Đầu Vào (Input)
* `distance` (kiểu `double`): Khoảng cách di chuyển của chuyến đi (km).
  * Ràng buộc: Bắt buộc `distance > 0.0`.
* `is_peak_or_rain` (kiểu `int`): Trạng thái phụ phí thời tiết mưa hoặc giờ cao điểm.
  * Quy ước: `1` là Có áp dụng phụ phí, `0` là Thời tiết / Khung giờ bình thường.

### Dữ Liệu Đầu Ra (Output)
* Thông báo từ chối xử lý và hủy giao dịch nếu khoảng cách không hợp lệ (`distance <= 0.0`).
* Hóa đơn chi tiết hiển thị trên console:
  * Quãng đường di chuyển (`%.2f km`).
  * Cước phí cơ sở (`%.0f VND`).
  * Tiền phụ phí phát sinh (`%.0f VND`).
  * Tổng chi phí cuối cùng cần thanh toán (`%.0f VND`).

---

## 2. Mô Hình Hóa Luồng Dữ Liệu (Data Flow)

Luồng xử lý dữ liệu được thiết kế thành 4 tầng tuần tự, phân tách rõ rệt giữa kiểm tra dữ liệu và tính toán:

```text
[Bàn phím: distance, is_peak_or_rain]
                 │
                 ▼
     [TẦNG 1: KIỂM TRA TÍNH HỢP LỆ]
        (distance <= 0.0 km?)
         ├── ĐÚNG ──> [Thông báo từ chối xử lý] ──> [DỪNG CHƯƠNG TRÌNH]
         └── SAI  ──> Tiếp tục sang Tầng 2
                 │
                 ▼
     [TẦNG 2: TÍNH CƯỚC CƠ SỞ (BASE FARE)]
        (distance <= 2.0 km?)
         ├── ĐÚNG ──> base_fare = 12.000 VNĐ
         └── SAI  ──> base_fare = 12.000 + (distance - 2.0) * 4.500 VNĐ
                 │
                 ▼
     [TẦNG 3: TÍNH PHỤ PHÍ BIẾN ĐỔI (DYNAMIC SURCHARGE)]
        (is_peak_or_rain == 1?)
         ├── ĐÚNG ──> surcharge_fare = base_fare * 0.20
         └── SAI  ──> surcharge_fare = 0 VNĐ
                 │
                 ▼
     [TẦNG 4: QUYẾT TOÁN & XUẤT HÓA ĐƠN]
        total_fare = base_fare + surcharge_fare
        Xuất chi tiết hóa đơn minh bạch ra Console
