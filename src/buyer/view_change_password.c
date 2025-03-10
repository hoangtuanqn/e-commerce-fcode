#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/buyer/view_ui.h"
void view_change_password() {
    read_user_data(); // đọc lại phần user để cập nhật id_list_user
    char password_old[50], password_new[50], repeat_password_new[50];
    do {
        printf("Enter the old password: ");
        scanf("%s", password_old);
        if(strcmp(current_user.password, password_old) != 0) {
            msg_error("Old password is incorrect\n");
        }

    } while(!input_string(password_old) || strcmp(current_user.password, password_old) != 0);

    do {
        printf("Enter the new password: ");
        scanf("%s", password_new);
        if(strcmp(current_user.password, password_new) == 0) {
            msg_error("The new password cannot be the same as the old password.\n");
        }
    } while(!input_string(password_new) || strcmp(current_user.password, password_new) == 0);

    do {
        printf("Re-enter new password: ");
        scanf("%s", repeat_password_new);
        if(strcmp(password_new, repeat_password_new) != 0) {
            msg_error("The new password cannot be the same as the old password.\n");
        }
    } while(!input_string(repeat_password_new) || strcmp(password_new, repeat_password_new) != 0);

    strcpy(list_user[current_user.id_list_user].password, password_new);
    strcpy(current_user.password, password_new);

    write_user_data();
    
    // printf("---%d----", current_user.id_list_user);
    msg_success("You have successfully changed your password.");
    write_user_remember(); // cập nhật lại tk mk remember
    return;
}