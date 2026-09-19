# Báo Cáo Kỹ Thuật: Dò Luồng & Sửa Lỗi Tính Cước Lũy Tiến Chuyến Xe GrabRide

## 1. Phân Tích Lỗi Sai Logic & Nguyên Nhân Kỹ Thuật (Root Cause Analysis)

Mã nguồn legacy ban đầu biên dịch thành công mà không phát sinh bất kỳ lỗi cú pháp nào (syntax error), tuy nhiên hệ thống đang gặp phải 02 lỗi sai logic nghiệp vụ nghiêm trọng:

### Lỗi 1: Sai công thức tính cước lũy tiến khi quãng đường > 2 km
* **Đoạn mã lỗi:**
  ```c
  } else {
      total_fare = distance * 4500.0;
  }
