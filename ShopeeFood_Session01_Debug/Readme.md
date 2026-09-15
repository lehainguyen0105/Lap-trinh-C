# Báo Cáo Phân Tích Lỗi & Kiểm Thử Logic Freeship (ShopeeFood)

## 1. Phân tích nguyên nhân lỗi kỹ thuật

* **Vị trí dòng lệnh sai logic:**
  ```c
  int is_freeship = (gia_tri_don >= 100000 || is_vip == 1) && (khoang_cach_km <= 5.0) && (is_da_huy = 0);
