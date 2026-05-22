#include "browser_history.h"

//* Chức năng: Cấp phát vùng nhớ và khởi tạo giá trị cho một trang web mới.
WebPage* create_page(char *title, char *url, char *time) {
    WebPage *newNode = malloc(sizeof(WebPage));
    //! Thắc mắc: Nếu RAM hết, malloc trả về NULL thì sao? strcpy vào NULL sẽ làm sập app (Segmentation fault) ngay lập tức!
    strcpy(newNode->title, title); // Sao chép chuỗi tiêu đề
    strcpy(newNode->url, url);     // Sao chép chuỗi URL
    strcpy(newNode->time, time);   // Sao chép chuỗi thời gian
    return newNode;
}

//* Chức năng: Tạo ra Node gốc (Header) làm điểm neo ban đầu cho danh sách liên kết đôi.
List create_header() {
    Position header = malloc(sizeof(struct Node));
    //! Thắc mắc: Tại sao dùng sizeof(struct Node) ở đây nhưng ở hàm create_page lại dùng sizeof(WebPage)? Thống nhất dùng tên kiểu dữ liệu đã typedef sẽ sạch code hơn.
    header->data = NULL; // Node header không chứa dữ liệu trang web
    header->next = NULL; // Chưa có trang kế tiếp
    header->prev = NULL; // Không có trang phía trước
    return header;
}

//* Chức năng: Thêm một trang web đã có sẵn vào cuối danh sách lịch sử.
void add_to_history(List header, WebPage *e) {
    Position temp = header;
    Position newNode = malloc(sizeof(struct Node));
    if (newNode == NULL) return; // Kiểm tra RAM đầy
    newNode->data = e;           // Gán dữ liệu trang web vào Node mới
    newNode->next = NULL;        // Node cuối nên next luôn trỏ vào NULL
    
    // Duyệt qua danh sách để tìm Node cuối hiện tại
    while (temp->next != NULL) temp = temp->next;
    
    newNode->prev = temp;        // Nối ngược Node mới về Node cuối cũ
    temp->next = newNode;        // Nối xuôi Node cuối cũ sang Node mới
}

//* Chức năng: Duyệt toàn bộ danh sách từ đầu đến cuối và in lịch sử ra màn hình theo dạng bảng.
void print_history(List header) {
    Position temp = header->next; // Bỏ qua Node header vì data của nó là NULL
    //! Thắc mắc: Nếu lịch sử trống (temp == NULL), bảng vẫn in ra tiêu đề trống. Nên có một dòng kiểm tra để báo "[!] Lich su trống" thì giao diện sẽ chuyên nghiệp hơn.
    printf("\n%-20s | %-25s | %-10s\n", "TIEU DE", "URL", "THOI GIAN");
    printf("------------------------------------------------------------\n");
    while (temp != NULL) {
        printf("%-20s | %-25s | %-10s\n", temp->data->title, temp->data->url, temp->data->time);
        temp = temp->next; // Dịch chuyển sang Node tiếp theo
    }
}

//* Chức năng: Dịch chuyển con trỏ vị trí hiện tại sang trang web kế tiếp (bấm nút Forward trên trình duyệt).
void go_forward(Position *current) {
    // Kiểm tra xem phía trước còn trang nào không
    if ((*current)->next == NULL) {
        printf("\n[!] Dang o trang cuoi cung!");
        return;
    }
    *current = (*current)->next; // Thay đổi địa chỉ của con trỏ current sang Node tiếp theo
}

//* Chức năng: Dịch chuyển con trỏ vị trí hiện tại về trang web phía trước (bấm nút Back trên trình duyệt).
void go_back(Position *current, List header) {
    // Kiểm tra nếu phía sau là Header hoặc bản thân đang đứng ở Header thì không lùi được nữa
    if ((*current)->prev == header || *current == header) {
        printf("\n[!] Dang o trang dau tien!");
        return;
    }
    *current = (*current)->prev; // Thay đổi địa chỉ của con trỏ current về Node phía trước
}

//* Chức năng: Xóa toàn bộ các trang web phía trước vị trí hiện tại (xóa nhánh lịch sử tương lai).
void clear_forward(Position current) {
    if (current == NULL) return;
    Position temp = current->next; // Giữ lại Node đầu tiên cần xóa
    current->next = NULL;          // Ngắt kết nối xuôi của vị trí hiện tại để cô lập nhánh tương lai
    
    // Vòng lặp giải phóng từng Node trong nhánh bị cô lập
    while (temp != NULL) {
        Position toDelete = temp;
        temp = temp->next;       // Lưu lại địa chỉ Node tiếp theo trước khi xóa Node hiện tại
        free(toDelete->data);    // Giải phóng vùng nhớ của cấu trúc WebPage bên trong
        free(toDelete);          // Giải phóng vùng nhớ của bản thân Node
    }
}

//* Chức năng: Khởi tạo sự kiện người dùng truy cập một trang web mới hoàn toàn.
void visit(List header, Position *pCurrent, char *title, char *url, char *time) {
    clear_forward(*pCurrent); // Xóa hết lịch sử tương lai trước khi rẽ nhánh mới
    WebPage *e = create_page(title, url, time); // Tạo trang web mới
    Position newPage = malloc(sizeof(struct Node));
    //! Thắc mắc: Lại bỏ quên kiểm tra newPage == NULL! Nếu hết RAM, dòng tiếp theo gán dữ liệu sẽ làm sập chương trình ngay lập tức.
    
    newPage->data = e;            // Bỏ trang web vào Node mới
    newPage->next = NULL;         // Trang mới nhất nên phía trước là NULL
    newPage->prev = (*pCurrent);  // Nối ngược Node mới về Node hiện tại
    (*pCurrent)->next = newPage;  // Nối xuôi Node hiện tại sang Node mới
    *pCurrent = newPage;          // Cập nhật con trỏ quản lý vị trí hiện tại chính là trang mới này
}

//* Chức năng: Tìm kiếm và trả về Node nằm ở cuối cùng của danh sách lịch sử hiện tại.
Position create_current(List header) {
    Position current = header;
    // Duyệt liên tục sang phải cho đến khi gặp Node cuối cùng
    while (current->next != NULL) current = current->next; 
    return current;
}