
# 🌐 Browser History Management System using Doubly Linked List

Dự án mô phỏng cơ chế quản lý lịch sử duyệt web (Back/Forward) của các trình duyệt hiện đại, sử dụng cấu trúc dữ liệu **Danh sách liên kết đôi (Doubly Linked List)** bằng ngôn ngữ C. Dự án được tổ chức theo cấu trúc mã nguồn chia nhỏ nhiều file (Modular Programming) giúp tối ưu quản lý và bảo trì.

---

## 🛠️ Cấu trúc thư mục (Workplace)
```text
Project/
├── browser_history.h   # Định nghĩa Struct (Khuôn) và Khai báo hàm (Mục lục)
├── browser_history.c   # Triển khai chi tiết logic của các hàm (Ruột)
├── Linked_List.c       # File chứa hàm main(), quản lý Menu điều khiển
└── README.md           # Hướng dẫn sử dụng dự án

```

---

## 🧠 Kiến trúc và Nguyên lý hoạt động

Hệ thống sử dụng một **List (Header Node)** cố định làm điểm neo. Một con trỏ `current` (quản lý ở mức con trỏ cấp 2 `Position *current`) sẽ dịch chuyển linh hoạt qua lại giữa các Node khi người dùng điều hướng.

* **Visit (Truy cập trang mới):** Giải phóng toàn bộ các trang phía trước vị trí hiện tại (nhánh tương lai) bằng hàm `clear_forward`, sau đó nối Node mới vào ngay sau vị trí hiện tại và dịch chuyển `current` sang Node mới.
* **Go Back / Go Forward:** Thay đổi địa chỉ của con trỏ `current` sang `current->prev` hoặc `current->next` sau khi đã kiểm tra các điều kiện biên (`NULL` hoặc chạm `Header`).

---

## 🚀 Hướng dẫn Biên dịch và Chạy chương trình

### Cách 1: Biên dịch thủ công bằng Terminal

Do dự án được chia làm nhiều file nguồn `.c`, bạn cần ép trình biên dịch `gcc` gom tất cả các file lại trước khi tạo file thực thi:

```bash
# Biên dịch gộp tất cả các file .c trong thư mục
gcc *.c -o ChuongTrinh

# Chạy chương trình trên Windows
./ChuongTrinh.exe

```

### Cách 2: Cấu hình chạy tự động trên VS Code (Dành cho Code Runner)

Nếu muốn sử dụng nút **Run** (hình tam giác), hãy thêm cấu hình sau vào file `.vscode/settings.json`:

```json
"code-runner.executorMap": {
    "c": "cd $dir && gcc *.c -o $fileNameWithoutExt && $dir$fileNameWithoutExt"
}

```

---

## 📝 Nhật ký chú thích (Quy ước ôn tập)

Trong file mã nguồn `browser_history.c`, các đoạn mã được tổ chức ghi chú nghiêm ngặt theo quy ước cá nhân để phục vụ cho việc ôn tập bản chất và cấu trúc bộ nhớ:

* `//*`: Giải thích chi tiết chức năng, nhiệm vụ của từng hàm.
* `//!`: Cảnh báo các lỗi logic tiềm ẩn, bẫy con trỏ hoặc các trường hợp biên nguy hiểm (Edge cases) cần lưu ý khi thi viết ra giấy.
* `//`: Chú thích luồng xử lý và thứ tự gán con trỏ bên trong hàm con.

---

## ⚠️ Các điểm lưu ý quan trọng khi ôn tập (Deep Processing)

1. **Thứ tự giải phóng bộ nhớ trong `clear_forward`:** Luôn phải dịch chuyển con trỏ kiểm soát sang Node kế tiếp trước khi gọi lệnh `free()` vào Node hiện tại để tránh lỗi mồ côi vùng nhớ (`Memory Leak`).
2. **Kiểm tra an toàn bộ nhớ (`NULL pointer check`):** Luôn kiểm tra xem `malloc` có trả về `NULL` khi hệ thống hết bộ nhớ hay không trước khi thực hiện sao chép dữ liệu (`strcpy`).

---

*Dự án được xây dựng và phát triển bởi Đỗ Hữu Minh Trí.*

```

```
