### Nguyên Nhân Kỹ Thuật (Lỗi Lệch 1 Đơn Vị - Off-By-One Error)
* **Khởi tạo biến đếm:** Biến `i` bắt đầu từ `1`, tương ứng với ly nước thứ nhất trong đơn hàng.
* **Sai lệch điều kiện dừng (`i < so_luong_ly`):** Toán tử so sánh nhỏ hơn nghiêm ngặt `<` khiến vòng lặp chỉ chạy đến giá trị `so_luong_ly - 1`.
* **Ví dụ cụ thể:** Khi nhập `so_luong_ly = 3`, vòng lặp chỉ duyệt qua $i = 1$ và $i = 2$. Khi biến đếm tăng lên $i = 3$, biểu thức điều kiện $3 < 3$ trả về kết quả sai (`false`), dẫn đến việc thoát khỏi vòng lặp ngay lập tức.
* **Hậu quả nghiệp vụ:** Ly nước cuối cùng (ly thứ $N$) không được nhập kích cỡ và không được tính tiền vào biến `tong_tien`. Do đó, hệ thống luôn xuất ra hóa đơn thiếu tiền so với thực tế, gây thất thoát doanh thu của quán cà phê.

### Giải Pháp Khắc Phục
Điều chỉnh toán tử so sánh điều kiện lặp từ `<` sang `<=` để vòng lặp duyệt đủ từ ly 1 đến đúng ly thứ `so_luong_ly`:
```c
for (int i = 1; i <= so_luong_ly; i++)

| STT | Trường Hợp Kiểm Thử | Dữ Liệu Đầu Vào | Kết Quả Thực Tế (Mã Cũ) | Kết Quả Mong Đợi (Mã Sửa) | Ghi Chú Kỹ Thuật |
| :---: | :--- | :--- | :--- | :--- | :--- |
| **01** | Đơn hàng 3 ly: Ly 1 (Size S), Ly 2 (Size M), Ly 3 (Size L) | `so_luong_ly = 3`<br>Ly 1: size 1 (S)<br>Ly 2: size 2 (M)<br>*(Ly 3 bị bỏ qua)* | **66.000 VNĐ**<br>*(Chỉ tính 2 ly: 30k + 36k)* | **106.000 VNĐ**<br>*(Đủ 3 ly: 30k + 36k + 40k)* | Khắc phục triệt để lỗi bỏ sót ly cuối cùng |
| **02** | Đơn hàng 1 ly duy nhất: Ly 1 (Size L) | `so_luong_ly = 1`<br>*(Vòng lặp không chạy)* | **0 VNĐ**<br>*(Bỏ qua toàn bộ đơn hàng)* | **40.000 VNĐ**<br>*(Tính chính xác 1 ly size L)* | Sửa lỗi điều kiện 1 < 1 bị sai ngay từ đầu |
