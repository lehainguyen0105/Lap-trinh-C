# Báo Cáo Kỹ Thuật: Phân Tích Trade-Off Logic Gộp vs Biến Cờ Trạng Thái (ShopeeFood Core)

## 1. Phân Tích Bài Toán (I/O Specification)

### Dữ liệu đầu vào (Input)
* `order_id` (`int`): Mã đơn hàng định danh.
* `subtotal` (`int`): Tổng tiền món ăn (VNĐ).
* `distance_km` (`float`): Khoảng cách giao hàng (km).
* `booking_hour` (`int`): Giờ đặt hàng (0 - 23).
* `is_store_open` (`int`): Trạng thái quán (`1`: Mở, `0`: Đóng).
* `inventory_qty` (`int`): Số lượng món khả dụng trong kho.

### Dữ liệu đầu ra (Output)
* `base_fee` (`int`): Cước phí cơ bản (mặc định 15,000 VNĐ).
* `surcharge` (`int`): Phụ phí khung giờ cao điểm (10,000 VNĐ hoặc 0 VNĐ).
* `discount` (`int`): Ưu đãi giảm giá vận chuyển (15,000 VNĐ hoặc 0 VNĐ).
* `is_valid_order` (`int`): Tính hợp lệ của đơn hàng (`1`: Hợp lệ, `0`: Từ chối).
* `final_delivery_fee` (`int`): Phí giao hàng thực tế.
* `total_payment` (`int`): Tổng tiền thanh toán cuối cùng.

---

## 2. Đề Xuất & So Sánh Giải Pháp (Trade-Off Analysis)

### Giải pháp A: Tách biệt cờ hiệu (Flag-based Arithmetic)
* **Ý tưởng:** Phân tách từng quy tắc nghiệp vụ thành các biến cờ trạng thái nguyên thủy (`is_peak_hour`, `is_freeship`, `is_valid_order`). Kết quả cước phí được tính bằng tích đại số giữa cờ hiệu và đơn giá tương ứng.
* **Biểu thức cốt lõi:**
  ```c
  int is_peak_hour = ((booking_hour >= 11 && booking_hour <= 13) || (booking_hour >= 18 && booking_hour <= 20));
  int surcharge = is_peak_hour * 10000;
