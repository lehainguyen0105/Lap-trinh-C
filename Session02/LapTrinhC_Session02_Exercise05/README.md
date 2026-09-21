# Báo Cáo Kỹ Thuật: Hệ Thống Tính Cước Chuyến Đi GrabRide Áp Dụng Mã Giảm Giá & Cước Sàn

## 1. Phân Tích Nghiệp Vụ & Yêu Cầu Kỹ Thuật

### Dữ Liệu Đầu Vào (Input)
* `distance` (kiểu `float`): Quãng đường di chuyển thực tế (đơn vị: km).
  * Ràng buộc: `distance > 0.0`.
* `has_promo` (kiểu `int`): Trạng thái áp dụng mã khuyến mãi.
  * Ràng buộc: Chỉ nhận giá trị `0` (Không có mã) hoặc `1` (Có mã giảm giá 20%).

### Dữ Liệu Đầu Ra (Output)
* Khi dữ liệu không hợp lệ: Xuất đúng định dạng `Loi: Du lieu dau vao khong hop le!`.
* Khi dữ liệu hợp lệ: Xuất tổng tiền cước làm tròn 2 chữ số thập phân theo mẫu:
  `Tong cuoc phi: [So_tien] VNĐ` (Ví dụ: `Tong cuoc phi: 100000.00 VNĐ`).

---

## 2. Thiết Kế Thuật Toán Xử Lý (Step-by-Step Logic)

Quy trình xử lý tuân thủ nguyên tắc lập trình phòng thủ (**Defensive Programming**) qua 4 bước:

1. **Bước 1 (Input Validation):**
   * Kiểm tra điều kiện bất thường: `distance <= 0.0f || (has_promo != 0 && has_promo != 1)`.
   * Nếu vi phạm, in `Loi: Du lieu dau vao khong hop le!` và kết thúc chương trình (`return 0;`).
2. **Bước 2 (Base Fare Calculation):**
   * Đơn giá cố định: 20.000 VNĐ/km.
   * `total_fare = distance * 20000.0f;`
3. **Bước 3 (Promo Discount & Floor Price):**
   * Nếu `has_promo == 1`:
     * Giảm 20%: `total_fare = total_fare * 0.8f;`
     * Kiểm tra cước sàn tối thiểu: Nếu `total_fare < 15000.0f` thì gán `total_fare = 15000.0f;`
4. **Bước 4 (Format Output):**
   * Xuất kết quả ra màn hình dạng `%.2f VNĐ`.

---

## 3. Bảng Kiểm Thử Đối Chứng (Test Cases Verification)

| Case | Input (`distance`, `has_promo`) | Output Kỳ Vọng | Nghiệp Vụ Kiểm Thử |
| :---: | :--- | :--- | :--- |
| **Case 1** | `5.0`, `0` | `Tong cuoc phi: 100000.00 VNĐ` | Cước tiêu chuẩn không giảm giá: $5.0 \times 20.000 = 100.000$ |
| **Case 2** | `10.0`, `1` | `Tong cuoc phi: 160000.00 VNĐ` | Có mã giảm 20%: $200.000 \times 0.8 = 160.000$ |
| **Case 3** | `0.8`, `1` | `Tong cuoc phi: 15000.00 VNĐ` | Sau giảm còn 12.800 < 15.000 -> Áp dụng cước sàn 15.000 |
| **Case 4** | `-2.5`, `0` | `Loi: Du lieu dau vao khong hop le!` | Chặn ngoại lệ cự ly âm |
| **Case 5** | `3.0`, `5` | `Loi: Du lieu dau vao khong hop le!` | Chặn ngoại lệ trạng thái mã giảm giá sai |

---

## 4. Hướng Dẫn Biên Dịch & Chạy Thử Nghiệm

* **Biên dịch bằng GCC với cờ chuẩn C11:**
  ```bash
  gcc -Wall -Wextra -std=c11 main.c -o main
