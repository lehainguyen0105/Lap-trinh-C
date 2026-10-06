```markdown
# BÁO CÁO PHÂN TÍCH VÀ SỬA LỖI MÃ NGUỒN (DEBUG REPORT)
## Hệ thống quản lý thuê bao SaaS - Nền tảng Streamify

---

### 1. Phân tích lỗi mã nguồn (Root Cause Analysis)

#### Vị trí dòng lệnh sai logic
Trong vòng lặp duyệt mảng struct:
- `if (user_list[0].days_overdue <= 3)`
- `total_revenue += user_list[0].monthly_fee;`

#### Nguyên nhân kỹ thuật
- Lập trình viên hardcode chỉ số mảng cố định là `[0]` thay vì dùng biến chỉ số `[i]`.
- Giá trị `user_list[0].days_overdue` là `0` (luôn `<= 3`), làm cho điều kiện `if` luôn nhận giá trị đúng (true) ở cả 4 lần lặp:
  1. Tất cả tài khoản quá hạn (`user_list[1]`, `user_list[3]`) đều bị hiển thị sai thành trạng thái "Hop le".
  2. Tổng doanh thu bị cộng dồn 4 lần giá trị phí tháng của phần tử đầu tiên (180000 * 4 = 720000 VND), thay vì chỉ cộng các tài khoản đủ điều kiện (180000 + 260000 = 440000 VND).

#### Hướng xử lý
- Đổi `user_list[0].days_overdue` thành `user_list[i].days_overdue`.
- Đổi `user_list[0].monthly_fee` thành `user_list[i].monthly_fee`.

---

### 2. Bảng Test Cases đối chứng

| Trường hợp kiểm thử | Dữ liệu đầu vào | Kết quả sai thực tế | Kết quả đúng mong đợi |
| :--- | :--- | :--- | :--- |
| **TC01: Tài khoản quá hạn > 3 ngày** | user_id = 1002<br>monthly_fee = 90000<br>days_overdue = 5 | - Trạng thái: Hop le<br>- Doanh thu cộng dồn: +180000 | - Trạng thái: Qua han<br>- Doanh thu cộng dồn: 0 |
| **TC02: Tổng doanh thu toàn hệ thống** | 4 tài khoản mẫu:<br>- 1001: 180k, trễ 0 ngày<br>- 1002: 90k, trễ 5 ngày<br>- 1003: 260k, trễ 1 ngày<br>- 1004: 90k, trễ 4 ngày | Tổng doanh thu: 720000 VND | Tổng doanh thu: 440000 VND |
