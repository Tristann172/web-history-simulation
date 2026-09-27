#include "browser_history.h"

//* Chức năng: Cấp phát vùng nhớ một trang web mới
WebPage* create_page(char *title, char *url, char *time) {
    WebPage *newNode = malloc(sizeof(WebPage));
    strcpy(newNode->title, title);
    strcpy(newNode->url, url);    
    strcpy(newNode->time, time);
    return newNode;
}

//* Chức năng: Tạo Header
List create_header() {
    Position header = malloc(sizeof(struct Node));
    header->data = NULL; 
    header->next = NULL; 
    header->prev = NULL;
    return header;
}

//* Chức năng: Thêm một trang web đã có sẵn vào cuối danh sách lịch sử
void add_to_history(List header, WebPage *e) {
    Position temp = header;
    Position newNode = malloc(sizeof(struct Node));
    if (newNode == NULL) return;
    newNode->data = e;          
    newNode->next = NULL;   

    while (temp->next != NULL) temp = temp->next;
    
    newNode->prev = temp;    
    temp->next = newNode;       
}

//* Chức năng: Duyệt và in lịch sử theo dạng bảng
void print_history(List header) {
    Position temp = header->next;
    printf("\n%-20s | %-25s | %-10s\n", "TIEU DE", "URL", "THOI GIAN");
    printf("------------------------------------------------------------\n");
    while (temp != NULL) {
        printf("%-20s | %-25s | %-10s\n", temp->data->title, temp->data->url, temp->data->time);
        temp = temp->next;
    }
}

//* Chức năng: Dịch chuyển con trỏ vị trí hiện tại sang trang web kế tiếp (bấm nút Forward trên trình duyệt)
void go_forward(Position *current) {
    if ((*current)->next == NULL) {
        printf("\n[!] Dang o trang cuoi cung!");
        return;
    }
    *current = (*current)->next;
}

//* Chức năng: Dịch chuyển con trỏ vị trí hiện tại về trang web phía trước (bấm nút Back trên trình duyệt)
void go_back(Position *current, List header) {
    if ((*current)->prev == header || *current == header) {
        printf("\n[!] Dang o trang dau tien!");
        return;
    }
    *current = (*current)->prev;
}

//* Chức năng: Xóa toàn bộ các trang web phía sau vị trí hiện tại
void clear_forward(Position current) {
    if (current == NULL) return;
    Position temp = current->next;
    current->next = NULL;          
    
    while (temp != NULL) {
        Position toDelete = temp;
        temp = temp->next;      
        free(toDelete->data);   
        free(toDelete);     
    }
}

//* Chức năng: Người dùng truy cập một trang web mới
void visit(List header, Position *pCurrent, char *title, char *url, char *time) {
    clear_forward(*pCurrent);
    WebPage *e = create_page(title, url, time);
    Position newPage = malloc(sizeof(struct Node));
    
    newPage->data = e;           
    newPage->next = NULL;        
    newPage->prev = (*pCurrent);  
    (*pCurrent)->next = newPage;  
    *pCurrent = newPage;         
}

//* Chức năng: Tìm kiếm và trả về current_node
Position create_current(List header) {
    Position current = header;
    while (current->next != NULL) current = current->next; 
    return current;
}