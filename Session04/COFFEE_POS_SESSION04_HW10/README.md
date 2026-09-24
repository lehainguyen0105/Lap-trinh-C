# Báo Cáo Kỹ Thuật: Kiểm Toán Doanh Thu Ca & Tối Ưu Hóa Luồng Dữ Liệu (Shift Revenue Audit Engine)

## 1. Phân Tích Dữ Liệu Vào / Ra (I/O Analysis)

### Dữ Liệu Đầu Vào (Input)
* `n` (`int`): Tổng số lượng giao dịch cần xử lý trong ca làm việc ($N$).
* Từng giao dịch $i$ ($1 \le i \le N$):
  * `drink_code` (`int`): Mã đồ uống (-1: Ngắt khẩn cấp, 0: Khách hủy đơn, 1: Phin Sữa Đá 29k, 2: Trà Sen Vàng 39k, 3: Freeze Cà Phê 49k).
  * `size_code` (`int`): Kích cỡ ly (1: Size S +0k, 2: Size M +6k, 3: Size L +10k).
  * `topping_count` (`int`): Số lượng topping thêm (Hợp lệ: 0 đến 5 phần, mỗi phần 8k).
  * `is_gold_member` (`int`): Trạng thái thẻ hội viên (1: Giảm 10%, 0: Không giảm).

### Dữ Liệu Đầu Ra (Output)
* Thông báo cảnh báo tức thì khi gặp đơn hủy (0), tín hiệu ngắt an ninh (-1) hoặc đơn rác sai cú pháp.
* Báo cáo kiểm toán cuối ca:
  * Tổng số giao dịch xử lý thành công.
  * Tổng số giao dịch lỗi/hủy bị bỏ qua.
  * Tổng doanh thu thực tế thu được trong ca (đơn vị: VNĐ).

---

## 2. Đề Xuất Giải Pháp & So Sánh Đánh Đổi (Trade-off Matrix)

### Giải Pháp 1: Tiếp Cận Truyền Thống (Deeply Nested Logic)
Kiểm tra dữ liệu theo mô hình hình tháp lồng nhau: Chỉ khi mã hợp lệ mới lồng tiếp kiểm tra size; chỉ khi size hợp lệ mới lồng tiếp kiểm tra topping; và chỉ tính tiền ở tầng lõi sâu nhất.
* **Hạn chế:** Tạo ra "Arrow Anti-pattern" (mã nguồn thụt vào quá sâu), khiến mã nguồn khó đọc, khó bổ sung thêm khuyến mãi và không thể ngắt khẩn cấp luồng lặp một cách tự nhiên.

### Giải Pháp 2: Tiếp Cận Tái Cấu Trúc (Guard Clauses kết hợp `break` và `continue`)
Phẳng hóa toàn bộ mã nguồn theo phương pháp lập trình phòng thủ:
* Gặp mã `-1` (an ninh POS) $\rightarrow$ Ngắt ngay vòng lặp bằng `break`.
* Gặp mã `0` (đơn hủy) hoặc dữ liệu sai lệch (size, topping) $\rightarrow$ Bỏ qua bước tính bằng `continue`.
* Mã nguồn tính giá chạy theo đường thẳng tuần tự (Flat Control Flow).

### Bảng So Sánh Chi Tiết

| Tiêu chí kỹ thuật | Giải pháp 1 (Deeply Nested Logic) | Giải pháp 2 (Guard Clauses với `break`/`continue`) |
| :--- | :--- | :--- |
| **Độ sâu lồng điều kiện (Nesting Depth)** | **Rất sâu (4-5 tầng `if-else` lồng nhau):** Tạo cảm giác ngợp mã và dễ nhầm ngoặc nhọn `{}`. | **Phẳng (Chỉ 1 tầng trong vòng lặp):** Mỗi điều kiện kiểm tra độc lập và thoát sớm. |
| **Khả năng ngắt khẩn cấp (Security Stop)** | **Kém:** Phải dùng cờ hiệu (flag variable) phức tạp để luồn lách qua các tầng `else`. | **Tối ưu:** Lệnh `break` lập tức dừng chuỗi duyệt và chốt sổ an toàn. |
| **Bảo trì & Mở rộng (Maintainability)** | **Khó khăn:** Thêm quy tắc phụ thu mới đòi hỏi chèn thêm 1 tầng lồng bên trong tầng cũ. | **Dễ dàng:** Thêm quy tắc nghiệp vụ chỉ cần đặt thêm một khối Guard độc lập bên dưới. |
| **Xử lý số nguyên tài chính (Precision)** | Dễ lẫn lộn phép chia `float` gây sai số tròn tiền. | Áp dụng công thức số nguyên $tong \times 90 / 100$ chuẩn xác 100%. |

**Kết luận lựa chọn:** Giải pháp 2 (Guard Clauses kết hợp `break` / `continue`) vượt trội hoàn toàn về tính tường minh, khả năng phòng thủ dữ liệu dị biệt và hiệu năng xử lý luồng giao dịch.

---

## 3. Các Bước Thực Hiện (Pseudocode)

```text
1. Nhập N. Nếu N <= 0: Báo lỗi và dừng chương trình.
2. Khởi tạo: total_revenue = 0, successful_orders = 0, skipped_orders = 0.
3. Cho i chạy từ 1 đến N:
     a. Nhập drink_code.
     b. Nếu drink_code == -1: Báo động ngắt an ninh, thực hiện BREAK.
     c. Nếu drink_code == 0: Báo đơn hủy, tăng skipped_orders, thực hiện CONTINUE.
     d. Nếu drink_code không thuộc {1, 2, 3}: Báo lỗi mã rác, tăng skipped_orders, CONTINUE.
     e. Xác định base_price theo drink_code (1: 29k, 2: 39k, 3: 49k).
     f. Nhập size_code, topping_count, is_gold_member.
     g. Nếu size_code không thuộc {1, 2, 3} HOẶC topping_count < 0 HOẶC topping_count > 5:
        Báo lỗi thông số order, tăng skipped_orders, CONTINUE.
     h. Tính item_total = base_price + size_surcharge + (topping_count * 8000).
     i. Nếu is_gold_member == 1: item_total = item_total * 90 / 100.
     j. total_revenue += item_total; successful_orders++.
4. In báo cáo tổng kết doanh thu ca làm việc.
