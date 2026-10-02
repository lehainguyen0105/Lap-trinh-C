# BÁO CÁO PHÂN TÍCH VÀ THIẾT KẾ GIẢI PHÁP
## Đề bài: Phân tích Trade-off: Biến Đơn lẻ Rời rạc vs Gom nhóm Dữ liệu qua Struct

---

### I. Phân tích Bài toán (Input / Output)

#### 1. Dữ liệu đầu vào (Input)
- Thong tin dinh danh:
  - id (int, 4 bytes): Ma dinh danh thiet bi.
- Trang thai & Kiem soat:
  - status (char, 1 byte): Trang thai thiet bi (0: Tat, 1: Bat).
  - errorCode (char, 1 byte): Ma loi trang thai thiet bi.
  - isAlert (char, 1 byte): Co canh bao bat thuong.
- Thong so cam bien do dac:
  - voltage (float, 4 bytes): Dien ap do duoc U (Volt).
  - current (float, 4 bytes): Dong dien do duoc I (Ampere).
  - powerMeasured (float, 4 bytes): Cong suat do thuc te P (Watt).
- Thoi gian van hanh:
  - operatingMinutes (float, 4 bytes): Thoi gian hoat dong tinh theo phut (t).

#### 2. Dữ liệu đầu ra (Output)
- Kich thuoc bo nho:
  - Do kich thuoc sizeof truoc va sau khi toi uu cau truc du lieu (bytes).
- Canh bao an toan & cam bien:
  - Canh bao cam bien cong suat sai lech (> 5% so voi cong suat tinh toan).
  - Canh bao QUA TAI NGUY HIEM (neu I > 30.0A hoac P > 6600.0W).
  - Canh bao RO RI DIEN HOAC TAI AN (neu status == 0 nhung I > 0.05A).
- Chi so nang luong:
  - San luong dien nang tieu thu kWh = (P * (t / 60.0)) / 1000.0.

---

### II. Đề xuất Đa giải pháp Tái cấu trúc Struct

#### 1. Cấu trúc ban đầu chưa tối ưu (Khai báo tự phát)
- struct DeviceUnoptimized gom cac truong:
  - status (1 byte) + padding (3 bytes)
  - id (4 bytes)
  - errorCode (1 byte) + padding (3 bytes)
  - voltage (4 bytes)
  - isAlert (1 byte) + padding (3 bytes)
  - current (4 bytes)
  - powerMeasured (4 bytes)
  - operatingMinutes (4 bytes)
- Tong kich thuoc: 32 bytes (lang phi 9 bytes padding).

#### 2. Giải pháp 1: Flat Struct Optimization (Sắp xếp giảm dần kích thước)
- Sap xep cac kieu du lieu lon (4 bytes: int, float) len truoc, gom cac kieu nho (1 byte: char) xuong cuoi:
  - id (4 bytes)
  - voltage (4 bytes)
  - current (4 bytes)
  - powerMeasured (4 bytes)
  - operatingMinutes (4 bytes)
  - status (1 byte)
  - errorCode (1 byte)
  - isAlert (1 byte)
  - padding cuoi (1 byte) de can chinh boi so 4 bytes.
- Tong kich thuoc: 24 bytes (tiet kiem 8 bytes ~ 25% dung luong RAM).

#### 3. Giải pháp 2: Nested Struct (Gom nhóm theo chức năng)
- Tach thanh 2 struct con:
  - struct PowerMetrics (16 bytes): voltage, current, powerMeasured, operatingMinutes.
  - struct DeviceMeta (8 bytes): id, status, errorCode, isAlert (kem 1 byte padding).
  - struct DeviceNested chua 2 struct tren.
- Tong kich thuoc: 24 bytes.

---

### III. Bảng so sánh Trade-off & Lựa chọn Giải pháp

| Tieu chi so sanh | Giai phap 1: Flat Struct Optimization | Giai phap 2: Nested Struct |
| :--- | :--- | :--- |
| Kich thuoc bo nho (sizeof) | 24 bytes (Toi uu triet de) | 24 bytes (Tuong duong) |
| Do phuc tap truy xuat cu phap | Don gian (1 cap: dev.voltage) | Sau hon (2 cap: dev.power.voltage) |
| Tinh dong goi (Encapsulation) | Trung binh (tat ca nam cung 1 cap) | Rat cao (chia module ro rang) |
| Tinh de bao tri & Mo rong | Can chu y thu tu khi them bien | De dang mo rong tung module con |
| Phu hop vi dieu khien Gateway | Rat cao, nhe, de lap trinh | Phu hop he thong quy mo lon |

* Lua chon cho bai toan: Chon Giai phap 1 (Flat Struct Optimization) vi vua giai quyet triet de van de lang phi bo nho RAM do padding tren vi dieu khien IoT Gateway, vua giu code trong ham main() don gian, khong phat sinh cu phap truy cap long nhau phuc tap.

---

### IV. Các bước xử lý Logic chương trình (Flowchart Steps)

1. Buoc 1 (Do bo nho): In ra sizeof cua struct chua toi uu va struct da toi uu de so sanh su chenh lech bo nho.
2. Buoc 2 (Nhap lieu & Kiem tra loi bat thuong):
   - Kiem tra status chi nhan 0 hoac 1.
   - Kiem tra U > 0, I >= 0, powerMeasured >= 0, operatingMinutes >= 0.
   - Neu du lieu sai lech, bao loi va dung chuong trinh.
3. Buoc 3 (Kiem tra cam bien cong suat):
   - Tinh cong suat ly thuyet P_calc = U * I.
   - Neu thiet bi bat va sai lech tuyet doi giua powerMeasured voi P_calc > 5% thi phat canh bao.
4. Buoc 4 (Kiem tra an toan dien):
   - Neu I > 30.0A hoac P_calc > 6600.0W -> Canh bao QUA TAI NGUY HIEM.
   - Neu status == 0 nhung I > 0.05A -> Canh bao RO RI DIEN HOAC TAI AN.
5. Buoc 5 (Tinh dien nang tieu thu):
   - Neu status == 1: kWh = (P_calc * (operatingMinutes / 60.0)) / 1000.0.
   - Neu status == 0: kWh = 0.0.
6. Buoc 6 (Xuat bao cao): In toan bo thong so va ket qua tinh toan ra man hinh console.
