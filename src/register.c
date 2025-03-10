#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../includes/global.h"
#include "../includes/function.h"
#include "../includes/register.h"

void register_form(User *user) {
    printf("====================================\n");
    printf("       USER REGISTRATION        \n");
    printf("====================================\n");
    int username_exists = 1;
    do {
        printf("Username: ");
        scanf("%s", user->email);
        username_exists = is_username_exists(user->username);
        if (username_exists) {
            msg_error("Username already exists! Please enter another username.\n");
        } else {
            username_exists = 0;
        }
    } while (username_exists);
    
    printf("Password: ");
    scanf("%s", user->password);
    
    printf("Confirm Password: ");
    char confirm_password[50];
    scanf("%s", confirm_password);
    
    while (strcmp(user->password, confirm_password) != 0) {
        printf("Passwords do not match! Please re-enter: ");
        scanf("%s", confirm_password);
    }

    int email_exists;
    do {
        printf("Email: ");
        scanf("%s", user->email);
        email_exists = is_email_exists(user->email);
        if (email_exists) {
            msg_error("Email already exists! Please enter another email.\n");
        }
    } while (email_exists);
    
    
    int phone_exists;
    do {
        printf("Phone Number: ");
        scanf("%s", user->phone);
        phone_exists = is_phone_exists(user->phone);
        if (phone_exists) {
            msg_error("Phone already exists! Please enter another phone.\n");
        }
    } while (phone_exists);

    // Drift command fails, use getchar() to remove character '\n'
    getchar();

    do {
        printf("Full Name: ");
        gets(user->full_name);
    } while(!input_string(user->full_name));

    do {
        printf("Address: ");
        gets(user->address);
    } while(!input_string(user->address));

    do {
        printf("Account Type (1: Buyer, 2: Seller): ");
        scanf("%d", &user->account_type);
        if (user->account_type < 1 || user->account_type > 2) {
            printf("Invalid account type!\n");
        }
    } while (user->account_type < 1 || user->account_type > 2);

    // Drift command fails, use getchar() to remove character '\n'
    getchar();
    if (user->account_type == 2) {
        
        do {
            printf("Shop Name: ");
            gets(user->shop_name);
        } while(!input_string(user->shop_name));

        
        do {
            printf("Warehouse Address: ");
            gets(user->warehouse_address);
        } while(!input_string(user->warehouse_address));
    } else {
        strcpy(user->shop_name, ".");
        strcpy(user->warehouse_address, ".");
    }

    // tiến hành ghi dữ liệu người dùng
    if (add_user_data(user) == 1) {
        is_logged_in = 1;
        current_user = *user;
        msg_success("\nRegistration Successful!\n");
        handle_remember_login();
    } else {
        msg_error("Registration Failed!\n");
    }
    printf("====================================\n");
}