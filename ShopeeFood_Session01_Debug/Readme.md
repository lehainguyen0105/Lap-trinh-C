# Báo Cáo Phân Tích Lỗi & Kiểm Thử Logic Freeship (ShopeeFood)

## 1. Phân tích nguyên nhân lỗi kỹ thuật

* **Vị trí dòng lệnh sai logic:**
  `int is_freeship = (gia_tri_don >= 100000 || is_vip == 1) && (khoang_cach_km <= 5.0) && (is_da_huy = 0);`
  Lỗi phát sinh trực tiếp tại biểu thức con: `(is_da_huy = 0)`.

* **Nguyên nhân kỹ thuật:**
  * **Nhầm lẫn toán tử:** Lập trình viên sử dụng toán tử gán `=` thay vì toán tử so sánh bằng `==`.
  * **Cơ chế trả về giá trị của phép gán trong C:** Biểu thức gán trả về chính giá trị vừa được gán. Biểu thức `(is_da_huy = 0)` gán `0` vào biến `is_da_huy` và trả về giá trị `0` (false).
  * **Hậu quả logic:** Phép `&&` gặp giá trị `0` thì toàn bộ biểu thức `is_freeship` luôn luôn bằng `0` (bị từ chối Freeship trên mọi đơn hàng).
  * **Hậu quả dữ liệu:** Biến `is_da_huy` bị ghi đè thành `0`, làm sai lệch dữ liệu gốc (đơn đã hủy bị đổi thành đơn hợp lệ).

* **Giải pháp khắc phục:**
  Sửa toán tử gán `=` thành so sánh bằng `==`: `(is_da_huy == 0)`.

---

## 2. Bảng 02 Test Cases đối chứng

| Trường hợp kiểm thử | Dữ liệu đầu vào | Kết quả sai thực tế | Kết quả đúng mong đợi |
| :--- | :--- | :--- | :--- |
| **Đơn hợp lệ đủ điều kiện Freeship** | - gia_tri_don: 200000<br>- khoang_cach_km: 2.0<br>- is_vip: 1<br>- is_da_huy: 0 | - is_freeship: 0 (Từ chối sai)<br>- is_da_huy: 0 | - is_freeship: 1 (Được Freeship)<br>- is_da_huy: 0 (Giữ nguyên) |
| **Đơn đã hủy nhưng thỏa tiền và khoảng cách** | - gia_tri_don: 150000<br>- khoang_cach_km: 3.0<br>- is_vip: 0<br>- is_da_huy: 1 | - is_freeship: 0<br>- is_da_huy: 0 (Bị ghi đè sai dữ liệu) | - is_freeship: 0 (Từ chối vì đơn đã hủy)<br>- is_da_huy: 1 (Giữ nguyên) |
