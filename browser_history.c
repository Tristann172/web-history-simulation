#include "browser_history.h"

// Triển khai chi tiết từng hàm
WebPage* create_page(char *title, char *url, char *time) {
    WebPage *newNode = malloc(sizeof(WebPage));
    strcpy(newNode->title, title);
    strcpy(newNode->url, url);
    strcpy(newNode->time, time);
    return newNode;
}

List create_header() {
    Position header = malloc(sizeof(struct Node));
    header->data = NULL;
    header->next = NULL;
    header->prev = NULL;
    return header;
}

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

void print_history(List header) {
    Position temp = header->next;
    printf("\n%-20s | %-25s | %-10s\n", "TIEU DE", "URL", "THOI GIAN");
    printf("------------------------------------------------------------\n");
    while (temp != NULL) {
        printf("%-20s | %-25s | %-10s\n", temp->data->title, temp->data->url, temp->data->time);
        temp = temp->next;
    }
}

void go_forward(Position *current) {
    if ((*current)->next == NULL) {
        printf("\n[!] Dang o trang cuoi cung!");
        return;
    }
    *current = (*current)->next;
}

void go_back(Position *current, List header) {
    if ((*current)->prev == header || *current == header) {
        printf("\n[!] Dang o trang dau tien!");
        return;
    }
    *current = (*current)->prev;
}

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

Position create_current(List header) {
    Position current = header;
    while (current->next != NULL) current = current->next; 
    return current;
}