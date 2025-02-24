#include <stdio.h>
#include <string.h>
#include "includes/view_ui.h"
#include "includes/global.h"
#include "includes/function.h"
#include "includes/register.h"
#include "includes/login.h"
#include "includes/seller/seller.h"
int main() {
    int choice;
    User user;
    // The user is not logged in
    do {
        view_ui_start();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                register_form(&user);
                break;
            case 2:
                login_form(&user);
                break;
            case 3:
                printf("Exit successfully\n");
                return 0;
            default:
                msg_error("Invalid choice. Please try again. \n");
        }
        if(is_logged_in) {
            switch (current_user.account_type) {
                case 1:
                    // view_ui_buyer();
                    break;
                case 2:
                    seller();
                    break;
            }
        }
    } while (is_pause_program == 0);

    // Logged in user
    return 0;
}
