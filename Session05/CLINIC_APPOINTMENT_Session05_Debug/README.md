"
1. Phân tích lỗi kỹ thuật & Nguyên nhân nghiệp vụ
Dòng lệnh gây lỗi: Chỉ rõ dòng mã nguồn chạy sai (queue_numbers[patient_position] = new_queue_number;).

Nguyên nhân kỹ thuật:

Phân tích sự xung đột giữa vị trí thực tế của người dùng (1-based index, vị trí 4) và chỉ số quản lý bộ nhớ của mảng trong C (0-based index, mảng 4 phần tử chỉ có chỉ số từ 0 đến 3).

Chỉ ra lỗi Index Out of Bounds / Buffer Overflow khi truy cập queue_numbers[4].

Giải thích vì sao chương trình không báo lỗi crash nhưng giá trị in ra vẫn là 1004 (dữ liệu 1099 bị ghi đè vào ô nhớ rác ngoài mảng, còn ô queue_numbers[3] chứa bệnh nhân 4 không được cập nhật).

Giải pháp khắc phục: Công thức chuyển đổi index = position - 1 và câu lệnh sửa thành queue_numbers[patient_position - 1] = new_queue_number;.

2. Bảng 02 Test Cases đối chứng
Bảng kiểm thử gồm 4 cột theo đúng quy định:

Trường hợp kiểm thử

Dữ liệu đầu vào

Kết quả sai thực tế

Kết quả đúng mong đợi
"
## Bảng Test Cases Đối Chứng

| Trường hợp kiểm thử | Dữ liệu đầu vào | Kết quả sai thực tế | Kết quả đúng mong đợi |
| :--- | :--- | :--- | :--- |
| **TC01: Cập nhật vị trí thứ 4 (Biên trên)** | - `queue_numbers`: `{1001, 1002, 1003, 1004}`<br>- `patient_position`: `4`<br>- `new_queue_number`: `1099` | - BN 4 (Index 3): `1004`<br>*(Giá trị 1099 bị ghi ngoài biên tại queue_numbers[4])* | - BN 4 (Index 3): `1099`<br>*(Cập nhật chính xác vị trí cuối mảng)* |
| **TC02: Cập nhật vị trí thứ 1 (Biên dưới)** | - `queue_numbers`: `{1001, 1002, 1003, 1004}`<br>- `patient_position`: `1`<br>- `new_queue_number`: `1000` | - BN 1 (Index 0): `1001`<br>- BN 2 (Index 1): `1000`<br>*(Cập nhật nhầm BN 2 do ghi vào index 1)* | - BN 1 (Index 0): `1000`<br>*(Cập nhật chính xác vị trí đầu mảng)* |
