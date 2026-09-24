# CLINIC_HW07 - Phân Hệ Tiếp Nhận & Xếp Hàng Khám Bệnh MedCare Clinic

## 1. Phân tích bài toán (Input / Process / Output)

### Đầu vào (Input):
- Mảng 4 phần tử `tuoi_benh_nhan[4]`: Lưu độ tuổi từng bệnh nhân (kiểu `int`).
- Mảng 4 phần tử `co_bao_hiem[4]`: Lưu trạng thái BHYT (kiểu `int`, mong đợi `1` hoặc `0`).

### Xử lý & Ràng buộc tính toán (Process):
- **Phí khám gốc:** 200,000 VNĐ.
- **Kiểm tra độ tuổi hợp lệ (Data Validation):**
  - Điều kiện lỗi: `tuoi <= 0` hoặc `tuoi > 120`.
  - Xử lý khi lỗi: `phi_kham = 0`, luồng khám = `"LỖI DỮ LIỆU"`, không tính vào tổng số ca ưu tiên.
- **Kiểm tra trạng thái BHYT:**
  - Nếu nhập giá trị khác `0` và `1` (như âm, >1): Tự động điều chỉnh về `0` (Không BHYT) để tránh thất thoát doanh thu.
- **Tính toán phí khám & Phân luồng (với tuổi hợp lệ):**
  - Có BHYT (`1`): Giảm 80% $\rightarrow$ Thu 20% giá gốc = 40,000 VNĐ.
  - Không có BHYT (`0`): Thu 100% giá gốc = 200,000 VNĐ.
  - Phân luồng: Nếu `tuoi > 70` $\rightarrow$ Luồng `"ƯU TIÊN"` (tăng biến đếm ca ưu tiên), ngược lại $\rightarrow$ Luồng `"THƯỜNG"`.
- **Tổng hợp ca trực:**
  - `tong_doanh_thu`: Cộng dồn toàn bộ `phi_kham[i]`.
  - `tong_ca_uu_tien`: Đếm số bệnh nhân hợp lệ có `tuoi > 70`.

### Đầu ra (Output):
- Mảng `phi_kham[4]`: Phí khám của từng bệnh nhân.
- Bảng hiển thị thông tin chi tiết từng bệnh nhân: STT, Tuổi, BHYT, Phí khám, Luồng khám.
- Tổng doanh thu thực tế và tổng số ca thuộc luồng ưu tiên trong ca khám.

---

## 2. Thiết kế các bước thực hiện (Thuật toán)

1. **Khởi tạo:** Khai báo 3 mảng kích thước 4 (`tuoi_benh_nhan`, `co_bao_hiem`, `phi_kham`) và các biến tích lũy (`tong_doanh_thu = 0`, `tong_ca_uu_tien = 0`).
2. **Nhập dữ liệu:** Dùng vòng lặp `for (i = 0; i < 4; i++)` tiếp nhận tuổi và trạng thái BHYT của 4 bệnh nhân.
3. **Xử lý & Kiểm soát lỗi (Data Validation):**
   - Duyệt `for (i = 0; i < 4; i++)`:
     - Nếu `tuoi_benh_nhan[i] <= 0 || tuoi_benh_nhan[i] > 120`: Gán `phi_kham[i] = 0`.
     - Ngược lại:
       - Kiểm tra BHYT: nếu `co_bao_hiem[i] != 0 && co_bao_hiem[i] != 1` thì gán `co_bao_hiem[i] = 0`.
       - Tính `phi_kham[i]` (40,000 nếu BHYT = 1, 200,000 nếu BHYT = 0).
       - Cộng dồn `tong_doanh_thu += phi_kham[i]`.
       - Nếu `tuoi_benh_nhan[i] > 70`: Tăng `tong_ca_uu_tien++`.
4. **Hiển thị báo cáo:** Xuất bảng danh sách kết quả và số liệu tổng kết ca trực ra màn hình.
