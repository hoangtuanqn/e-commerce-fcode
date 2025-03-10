#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "../includes/global.h"
#include "../includes/login.h"
#include "../includes/view_ui.h"
#include "../includes/function.h"

User current_user;

int handle_login(char *username, char *password) {
    if (strlen(username) == 0 || strlen(password) == 0) {
        return 0;
    }
    // printf("%s---%s--%d--%d--%d", username, password, strlen(username), strlen(password), MAX_USERS);

    // Duyệt qua mảng list_user để tìm user phù hợp
    for(int i = 0; i < counter_user; i++) {
        // Nếu username rỗng thì break vì đã hết user
        // printf("%s-%s\n", list_user[i].username, list_user[i].password);
        if(strlen(list_user[i].username) == 0) {
            break;
        }

        // Kiểm tra username và password
        // printf("----%s-----%s------\n", list_user[i].username, list_user[i].password);
        // printf("----%s-----%s------\n", username, password);
        // printf("---%d--", counter_user);
        if (strcmp(list_user[i].username, username) == 0 && 
            strcmp(list_user[i].password, password) == 0) {
            
            // Copy thông tin user vào current_user
            current_user = list_user[i]; // gán dữ liệu trực tiếp
          
            return 1;
        }
    }

    return 0;
}
void handle_remember_login() {
    int choice;
    do {
        view_ui_remember();
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                FILE *fp = fopen("data/remember_login.txt", "a");
                if (fp == NULL) {
                    msg_error("Cannot open file!");
                    return;
                }
                fprintf(fp, "%s\n%s\n", current_user.username, current_user.password);
                fclose(fp);

                return;
            }
            case 0:
                return;
            default:
                msg_error("Invalid Choice");
        }
    } while(1);
}
void login_form() {
    int is_re_login = 1;
    char username[50], password[50];

    do {
        printf("====================================\n");
        printf("               LOGIN        \n");
        printf("====================================\n");
        do {
            printf("Username: ");
            scanf("%s", username);
        } while(!input_string(username));
        
        do {
            printf("Password: ");
            scanf("%s", password);
        } while(!input_string(password));

        if (handle_login(username, password)) {
            is_logged_in = 1;
            is_re_login = 0;
            msg_success("Login successful!\n");
            handle_remember_login();
        } else {
            msg_error("Invalid username or password!\n");
            is_re_login = view_ui_re_login();
        }
    } while (is_re_login == 1);
}