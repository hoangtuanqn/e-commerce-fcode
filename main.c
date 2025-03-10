#include <stdio.h>
#include <string.h>
#include "includes/view_ui.h"
#include "includes/global.h"
#include "includes/function.h"
#include "includes/register.h"
#include "includes/login.h"
#include "includes/seller/seller.h"
#include "includes/buyer/buyer.h"
int main() {
    int choice;
    User user;
    // The user is not logged in
    check_remember_login();
    do {
        if(is_logged_in) {

            switch (current_user.account_type) {
                case 1:
                    buyer();
                    break;
                case 2:
                    seller();
                    break;
                default:
                    msg_error("Invalid account type. Please try again. \n");
                    return 0;
            }
        } else {
            view_ui_start();
            scanf("%d", &choice);
            read_user_data(); // đọc dữ liệu từ file user;
            getchar();
            switch (choice) {
                case 1:
                    register_form(&user);
                    break;
                case 2:
                    login_form();
                    break;
                case 3:
                    msg_success("Exit successfully\n");
                    return 0;
                default:
                    msg_error("Invalid choice. Please try again. \n");
            }
        }
    } while (is_pause_program == 0);

    // Logged in user
    return 0;
}
