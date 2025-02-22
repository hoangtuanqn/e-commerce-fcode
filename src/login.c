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
        printf("Invalid user data!\n");
        return 0;
    }

    FILE *file = fopen("data/users.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    char line[512];
    char username[50], password[50], email[100], phone[20], full_name[100], address[200], shop_name[200], warehouse_address[200];
    int account_type;

    while (!feof(file)) {
        fgets(line, sizeof(line), file);
        strcpy(username, line);
        trim_trailing_spaces(username);

        fgets(line, sizeof(line), file);
        strcpy(password, line);
        trim_trailing_spaces(password);

        fgets(line, sizeof(line), file);
        strcpy(email, line);
        trim_trailing_spaces(email);

        fgets(line, sizeof(line), file);
        strcpy(phone, line);
        trim_trailing_spaces(phone);

        fgets(line, sizeof(line), file);
        strcpy(full_name, line);
        trim_trailing_spaces(full_name);

        fgets(line, sizeof(line), file);
        strcpy(address, line);
        trim_trailing_spaces(address);

        fgets(line, sizeof(line), file);
        trim_trailing_spaces(line);
        account_type = atoi(line);

        fgets(line, sizeof(line), file);
        strcpy(shop_name, line);
        trim_trailing_spaces(shop_name);

        fgets(line, sizeof(line), file);
        strcpy(warehouse_address, line);
        trim_trailing_spaces(warehouse_address);

        if (strcmp(username, user->username) == 0 && strcmp(password, user->password) == 0) {
            strcpy(current_user.username, username);
            strcpy(current_user.password, password);
            strcpy(current_user.full_name, full_name);
            strcpy(current_user.email, email);
            strcpy(current_user.phone, phone);
            strcpy(current_user.address, address);
            current_user.account_type = account_type;
            strcpy(current_user.shop_name, shop_name);
            strcpy(current_user.warehouse_address, warehouse_address);
            fclose(file);
            return 1;
        }

        fgets(line, sizeof(line), file);
        fgets(line, sizeof(line), file);
    }

    fclose(file);
    return 0;
}

void login_form(User *user) {
    int is_re_login = 1;
    do {
        printf("====================================\n");
        printf("             USER LOGIN        \n");
        printf("====================================\n");
        printf("Username: ");
        scanf("%s", user->username);
        
        printf("Password: ");
        scanf("%s", user->password);

        if (handle_login(user)) {
            is_logged_in = 1;
            is_re_login = 0;
            msg_success("Login successful!\n");

        } else {
            msg_error("Invalid username or password!\n");
            is_re_login = view_ui_re_login();
        }
    } while (is_re_login == 1);
}
