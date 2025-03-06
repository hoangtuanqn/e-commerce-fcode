#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../includes/global.h"
#include "../includes/login.h"
#include "../includes/view_ui.h"
#include "../includes/function.h"

User current_user;

int handle_login(User *user) {
    if (user == NULL) {
        return 0;
    }

    // Duyệt qua mảng list_user để tìm user phù hợp
    for(int i = 0; i < MAX_USERS; i++) {
        // Nếu username rỗng thì break vì đã hết user
        if(strlen(list_user[i].username) == 0) {
            break;
        }

        // Kiểm tra username và password
        if (strcmp(list_user[i].username, user->username) == 0 && 
            strcmp(list_user[i].password, user->password) == 0) {
            
            // Copy thông tin user vào current_user
            strcpy(current_user.username, list_user[i].username);
            strcpy(current_user.password, list_user[i].password);
            strcpy(current_user.full_name, list_user[i].full_name);
            strcpy(current_user.email, list_user[i].email); 
            strcpy(current_user.phone, list_user[i].phone);
            strcpy(current_user.address, list_user[i].address);
            current_user.account_type = list_user[i].account_type;
            strcpy(current_user.shop_name, list_user[i].shop_name);
            strcpy(current_user.warehouse_address, list_user[i].warehouse_address);
            
            return 1;
        }
    }

    return 0;
}

void login_form() {
    int is_re_login = 1;
    User user;
    char username[50];
    char password[50];

    do {
        printf("====================================\n");
        printf("               LOGIN        \n");
        printf("====================================\n");
        printf("Username: ");
        scanf("%s", username);
        
        printf("Password: ");
        scanf("%s", password);

        // Copy credentials to user struct
        strcpy(user.username, username);
        strcpy(user.password, password);

        if (handle_login(&user)) {
            is_logged_in = 1;
            is_re_login = 0;
            msg_success("Login successful!\n");
        } else {
            msg_error("Invalid username or password!\n");
            is_re_login = view_ui_re_login();
        }
    } while (is_re_login == 1);
}