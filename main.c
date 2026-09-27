#include "browser_history.h"

int main(){
    List history = create_header();
    Position current = create_current(history);
    int choice;
    char t[100], u[200], choice_buf[10];

    while(1){
        printf("\n========== TRINH DUYET C-WEB ==========");
        if (current == history) {
            printf("\n[HOME] Ban dang o trang chu.");
        } else {
            printf("\n[CURRENT] %s (%s)", current->data->title, current->data->url);
        }
        printf("\n=======================================");

        printf("\n1. Truy cap URL moi.");
        printf("\n2. Quay lai (Back)");
        printf("\n3. Tien toi (Forward)");
        printf("\n4. Xem toan bo lich su");
        printf("\n5. Thoat");
        printf("\nChon chuc nang: ");
        
        if (fgets(choice_buf, sizeof(choice_buf), stdin)) {
            choice = atoi(choice_buf);
        } else {
            continue;
        }

        switch (choice) {
            case 1:
                printf("Nhap Tieu de: "); fgets(t, 100, stdin); t[strcspn(t, "\n")] = 0;
                printf("Nhap URL: "); fgets(u, 200, stdin); u[strcspn(u, "\n")] = 0;
                visit(history, &current, t, u, "00:00:00");
                break;
            case 2:
                go_back(&current, history);
                break;
            case 3:
                go_forward(&current);
                break;
            case 4:
                print_history(history);
                break;
            case 5:
                printf("\nCam on ban da su dung! Tam biet.");
                return 0;
            default:
                printf("\nLua chon khong ton tai!");
        }
    }
    return 0;
}