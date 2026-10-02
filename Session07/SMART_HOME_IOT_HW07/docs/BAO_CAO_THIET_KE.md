# BÁO CÁO PHÂN TÍCH VÀ THIẾT KẾ GIẢI PHÁP
## Module Quản lý Cụm Thiết bị Phòng Thông minh (Smart Gateway IoT)

### I. Phân tích bài toán (Input / Output)

1. **Dữ liệu đầu vào (Input):**
   - Cấu trúc `SmartDevice`:
     - `deviceID` (int): Mã định danh thiết bị.
     - `deviceName` (char[]): Tên thiết bị (ví dụ: "Dieu hoa trung tam").
     - `status` (int): Trạng thái thiết bị (1: Bật, 0: Tắt).
     - `ratedPowerKW` (float): Công suất định mức (kW).
   - Cấu trúc `EnergySensor`:
     - `voltageVolts` (float): Điện áp cảm biến đo (V).
     - `currentAmperes` (float): Dòng điện cảm biến đo (A).
     - `unoccupancyMinutes` (int): Thời gian vắng người (phút).
   - Biến phụ trợ:
     - `operatingHours` (float): Số giờ hoạt động trong tháng (h).

2. **Dữ liệu đầu ra (Output):**
   - Trạng thái thiết bị sau khi xử lý các luật an toàn và tự động hóa (`BAT` hoặc `TAT`).
   - Cảnh báo an toàn (nếu có: Cảnh báo quá tải/nguy cơ cháy nổ, cảnh báo ngắt tiết kiệm năng lượng).
   - Tổng sản lượng điện năng tiêu thụ: `totalKWh` (kWh).
   - Tổng chi phí tiền điện dự kiến theo biểu giá 4 bậc của EVN: `totalBill` (VNĐ).

---

### II. Thiết kế giải pháp và luồng xử lý (Step-by-step Logic)

- **Bước 1: Khởi tạo dữ liệu cấu trúc**
  - Khai báo 2 kiểu cấu trúc: `struct SmartDevice` và `struct EnergySensor`.
  - Khai báo biến `dev` và `sensor`, nhập thông tin trực tiếp thông qua toán tử `.`.
  
- **Bước 2: Kiểm chuẩn dữ liệu đầu vào (Input Validation)**
  - Lỗi cảm biến: Nếu `sensor.voltageVolts < 0` hoặc `sensor.currentAmperes < 0` hoặc `sensor.unoccupancyMinutes < 0` -> Báo lỗi phần cứng cảm biến và dừng chương trình.
  - Lỗi giờ vận hành: Nếu `operatingHours <= 0` hoặc `operatingHours > 744` -> Báo lỗi giờ vận hành không hợp lệ và dừng chương trình.

- **Bước 3: Xử lý quy tắc an toàn & tự động hóa theo thứ tự ưu tiên**
  - **Ưu tiên 1 (An toàn điện):** Nếu `sensor.currentAmperes > 30.0f` -> Kích hoạt ngắt khẩn cấp (`dev.status = 0`), bật cảnh báo quá tải nguy cơ cháy nổ.
  - **Ưu tiên 2 (Tiết kiệm điện):** Nếu thiết bị vẫn bật (`dev.status == 1`) và `sensor.unoccupancyMinutes >= 15` -> Tự động ngắt (`dev.status = 0`), hiển thị thông báo tắt thiết bị để tiết kiệm điện.

- **Bước 4: Tính toán sản lượng điện và chi phí theo bậc thang EVN**
  - Tính điện năng: `totalKWh = dev.ratedPowerKW * operatingHours`.
  - Biểu giá EVN (chưa VAT):
    - Bậc 1 (kWh $\le 50$): $1.806$ đ/kWh.
    - Bậc 2 (kWh từ $51 - 100$): $1.866$ đ/kWh.
    - Bậc 3 (kWh từ $101 - 200$): $2.167$ đ/kWh.
    - Bậc 4 (kWh $> 200$): $2.729$ đ/kWh.

- **Bước 5: Xuất kết quả tổng hợp**
  - In trạng thái thiết bị cuối cùng, thông số đo lường, cảnh báo, sản lượng và chi phí tiền điện.
