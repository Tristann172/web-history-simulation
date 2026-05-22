/* * THƯ VIỆN QUẢN LÝ LỊCH SỬ TRÌNH DUYỆT (Dùng Danh sách liên kết đôi)
 * Tác giả: Minh Trí
 */

#ifndef BROWSER_HISTORY_H
#define BROWSER_HISTORY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// --- KHAI BÁO CẤU TRÚC DỮ LIỆU ---

typedef struct {
    char url[200];
    char title[100];
    char time[200];
} WebPage;

struct Node {
    WebPage *data;
    struct Node *next;
    struct Node *prev;
};

// Định nghĩa List và Position để code gọn gàng hơn
typedef struct Node *List;
typedef struct Node *Position;


// --- CÁC HÀM XỬ LÝ (INTERFACE) ---

/* * Tạo một đối tượng WebPage mới
 * Trả về: Con trỏ đến vùng nhớ vừa cấp phát
 */
WebPage* create_page(char *title, char *url, char *time);

/* * Khởi tạo danh sách (Tạo Header Node)
 * Trả về: Một List rỗng nhưng có sẵn Header
 */
List create_header();

/* * Tìm và trả về vị trí của Node cuối cùng trong danh sách
 */
Position create_current(List header);

/* * Thêm một trang mới vào sau vị trí hiện tại (Current)
 * Đồng thời xóa toàn bộ các trang nằm phía trước (Forward)
 */
void visit(List header, Position *pCurrent, char *title, char *url, char *time);

/* * Điều hướng con trỏ hiện tại về trang phía trước
 */
void go_back(Position *current, List header);

/* * Điều hướng con trỏ hiện tại tiến về trang phía sau
 */
void go_forward(Position *current);

/* * Xóa toàn bộ các Node nằm sau vị trí hiện tại (Dọn dẹp tương lai)
 */
void clear_forward(Position current);

/* * In toàn bộ lịch sử ra màn hình theo định dạng bảng
 */
void print_history(List header);

#endif // Kết thúc BROWSER_HISTORY_H