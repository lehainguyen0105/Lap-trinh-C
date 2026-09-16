# Báo cáo Phân hệ Quyết toán Đơn hàng Đa tầng ShopeeFood (C99)

## 1. Phân tích bài toán (I/O Specification)

### Dữ liệu đầu vào (Input)
* `item_id` (`int`): Mã định danh món ăn (ví dụ: 1024).
* `unit_price` (`float`): Đơn giá một món ăn (VNĐ).
* `order_quantity` (`int`): Số lượng món đặt mua.
* `delivery_distance` (`float`): Khoảng cách giao hàng (km).
* `is_peak_hour` (`int`): Trạng thái giờ cao điểm (`1`: Có, `0`: Không).
* `is_store_open` (`int`): Trạng thái quán (`1`: Mở cửa, `0`: Đóng cửa).
* `stock_quantity` (`int`): Số lượng tồn kho khả dụng tại quán.
* `account_type` (`char`): Phân loại tài khoản (`'V'`: VIP, `'N'`: Thường).

### Dữ liệu đầu ra (Output)
* `subtotal` (`float`): Tiền món ăn = `unit_price * order_quantity`.
* `base_shipping_fee` (`float`): Phí giao hàng = `delivery_distance * 5000.0`.
* `freeship_discount` (`float`): Giảm giá Freeship (tối đa 15.000 VNĐ và không vượt quá phí cơ bản).
* `peak_surcharge` (`float`): Phụ phí giờ cao điểm (10.000 VNĐ nếu có).
* `is_order_valid` (`int`): Đánh giá tính hợp lệ đơn hàng (`1`: Hợp lệ, `0`: Từ chối).
* `final_amount` (`float`): Tổng tiền thanh toán cuối cùng (VNĐ).

---

## 2. Đề xuất giải pháp & Tư duy Đại số Boole (Zero-Branching Logic)

Chương trình tuân thủ nghiêm ngặt yêu cầu: **Cấm sử dụng cấu trúc rẽ nhánh (`if/else`, `switch`) và vòng lặp**. Toàn bộ logic nghiệp vụ được giải quyết bằng giá trị trả về của toán tử quan hệ và logic (`1` ứng với True, `0` ứng với False):

* **Kiểm tra tính hợp lệ toàn diện (Order Validity):**
  ```c
  int is_order_valid = (is_store_open == 1) && 
                       (stock_quantity >= order_quantity) && 
                       (order_quantity > 0) && 
                       (unit_price > 0.0f);
