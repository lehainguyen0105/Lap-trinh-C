# Báo Cáo Phân Tích Kỹ Thuật (Trade-off Analysis) & Thiết Kế Module Quản Lý Hàng Chờ

**Dự án:** CLINIC_APPOINTMENT  
**Học phần:** Session 05 - Lesson 10 (Mảng trong C / C11)  
**Tác vụ:** Quản lý hàng chờ Kiosk, tính toán viện phí và xử lý biến động khi bệnh nhân hủy lượt khám.

---

## 1. Phân Tích Bài Toán (I/O Analysis)

### 1.1. Dữ liệu đầu vào (Input)
- **Số lượng bệnh nhân ban đầu ($n$):** Kiểu số nguyên, nằm trong khoảng giới hạn $[0, MAX]$ với $MAX = 100$.
- **Thông tin chi tiết từng bệnh nhân:**
  - `queue_ids[MAX]`: Mã số thứ tự khám (số nguyên dương).
  - `ages[MAX]`: Độ tuổi của bệnh nhân, thỏa mãn điều kiện hợp lệ $1 \le tuoi \le 120$.
  - `has_insurance[MAX]`: Trạng thái BHYT, chuẩn hóa nhị phân ($1$: Có BHYT, $0$: Không có BHYT).
- **Chỉ số yêu cầu hủy lượt ($K$):** Số nguyên đại diện cho chỉ số phần tử cần hủy trong mảng active, thỏa mãn $0 \le K < n$.

### 1.2. Dữ liệu đầu ra (Output)
- **Danh sách hàng chờ ban đầu:** Bảng chi tiết gồm STT, Queue ID, Tuổi, Trạng thái BHYT, Chi phí khám ban đầu, Phân loại luồng (Ưu tiên nếu $tuoi \ge 70$, Thường nếu $tuoi < 70$).
- **Chỉ số tổng hợp ban đầu:** Tổng doanh thu tạm tính và tổng số lượt ưu tiên.
- **Danh sách hàng chờ sau khi hủy lượt:** Bảng dữ liệu đã được tái cấu trúc, đảm bảo không còn ô trống hoặc số thứ tự ảo.
- **Chỉ số tổng hợp cập nhật:** Tổng doanh thu thực tế và tổng số ca ưu tiên còn lại trong hàng active.

---

## 2. Đề Xuất Các Giải Pháp Xử Lý "Hủy Lượt Khám Tại Chỉ Số K"

Để giải quyết bài toán hủy phần tử tại vị trí $K$ trên mảng 1 chiều, ba phương án kỹ thuật được đưa ra xem xét:

### Giải pháp 1: Dồn dịch mảng (Shift Array / Hard Delete)
- **Cơ chế:** Khi hủy bệnh nhân tại chỉ số $K$, thực hiện vòng lặp dịch chuyển toàn bộ các phần tử từ chỉ số $K + 1$ đến $n - 1$ về trước 1 vị trí (ghi đè lên vị trí $K$). Sau đó, giảm biến đếm $n$ đi 1 đơn vị.
- **Đặc điểm:** Dữ liệu active luôn liên tục trong bộ nhớ từ $0$ đến $n - 1$.

### Giải pháp 2: Đánh dấu trạng thái (Soft Delete / Lazy Deletion)
- **Cơ chế:** Bổ sung thêm một mảng cờ trạng thái `is_active[MAX]`. Khi có yêu cầu hủy tại $K$, chỉ đổi cờ `is_active[K] = 0` mà không tác động hay di chuyển các phần tử khác trong mảng.
- **Đặc điểm:** Thao tác hủy diễn ra tức thì, giữ lại dấu vết lịch sử nhưng kích thước mảng không đổi.

### Giải pháp 3: Đổi chỗ với phần tử cuối (Swap with Last)
- **Cơ chế:** Sao chép phần tử ở vị trí cuối mảng ($n - 1$) đè trực tiếp vào vị trí $K$, sau đó giảm biến đếm $n$ đi 1 đơn vị.
- **Đặc điểm:** Tối ưu số phép gán dữ liệu nhưng làm xáo trộn hoàn toàn thứ tự gốc.

---

## 3. Bảng So Sánh Trade-off Giữa Các Giải Pháp

| Tiêu chí đánh giá | Giải pháp 1: Dồn dịch (Shift Array) | Giải pháp 2: Đánh dấu (Soft Delete) | Giải pháp 3: Đổi chỗ cuối (Swap Last) |
| :--- | :--- | :--- | :--- |
| **Độ phức tạp thời gian khi hủy (Time)** | $O(n)$ *(Tối đa $n - 1 - K$ phép dịch)* | $O(1)$ *(Gán cờ tức thì)* | $O(1)$ *(1 phép gán duy nhất)* |
| **Độ phức tạp bộ nhớ phụ (Space)** | $O(1)$ *(Không tốn bộ nhớ phụ)* | Tốn thêm $O(MAX)$ *(Mảng `is_active`)* | $O(1)$ *(Không tốn bộ nhớ phụ)* |
| **Bảo toàn thứ tự hàng đợi (FIFO)** | **Được bảo toàn tuyệt đối** | **Được bảo toàn** | **Bị vi phạm hoàn toàn** |
| **Độ phức tạp khi duyệt & tính toán** | $O(1)$ logic đơn giản, duyệt từ $0$ đến $n - 1$ | Phức tạp hơn: mỗi thao tác duyệt phải lồng điều kiện `if (is_active[i])` | Đơn giản, duyệt từ $0$ đến $n - 1$ |
| **Rủi ro hiển thị dữ liệu rác** | **Triệt tiêu hoàn toàn** | Dễ sót nếu quên kiểm tra cờ | Không có dữ liệu rác |

---

## 4. Quyết Định Kỹ Thuật & Lý Do Lựa Chọn

### Quyết định: Lựa chọn Giải pháp 1 (Dồn dịch mảng - Shift Array / Hard Delete).

### Lý do lựa chọn:
1. **Tính đúng đắn nghiệp vụ y tế (FIFO):**
   - Phòng khám vận hành theo nguyên tắc công bằng: người đến trước khám trước (**FIFO**).
   - Giải pháp 3 (Swap with Last) đưa người đăng ký cuối cùng nhảy cóc lên vị trí của người vừa hủy, vi phạm quy trình tiếp nhận và gây khiếu nại bệnh nhân. Do đó, Giải pháp 3 bị loại bỏ đầu tiên.

2. **Quy mô dữ liệu thực tế ($MAX = 100$):**
   - Với dung lượng mảng tối đa $100$ phần tử, thao tác dịch mảng tối đa $99$ bước dịch chuyển số nguyên chỉ tiêu tốn vài nano-giây trên CPU hiện đại. Thời gian thực thi chênh lệch giữa $O(n)$ và $O(1)$ ở quy mô này là hoàn toàn không đáng kể.

3. **Tính toàn vẹn dữ liệu và loại bỏ rủi ro gọi khống:**
   - Dùng cờ trạng thái (Giải pháp 2) giữ lại phần tử chết trong mảng. Nếu các module hiển thị LCD cho bác sĩ hoặc máy in phiếu gặp lỗi bỏ sót kiểm tra `is_active`, tình trạng "gọi khống số thứ tự" đã hủy vẫn sẽ tái diễn.
   - Dồn dịch mảng loại bỏ triệt để phần tử đã hủy ra khỏi phạm vi active ($0 \le i < n$), đảm bảo tính nhất quán tuyệt đối giữa dữ liệu hàng chờ và doanh thu thu ngân.

---

## 5. Hướng Dẫn Biên Dịch & Chạy Chương Trình

Mã nguồn được viết theo chuẩn **C11**, không sử dụng thư viện ngoài.

```bash
# Di chuyển vào thư mục bài làm
cd CLINIC_APPOINTMENT/Session05_Lesson10

# Biên dịch chương trình với cờ kiểm tra chuẩn C11 và cảnh báo đầy đủ
gcc -std=c11 -Wall -Wextra main.c -o main

# Thực thi chương trình
./main
