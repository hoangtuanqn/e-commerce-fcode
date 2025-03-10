#include <stdio.h>
#include <string.h>  // Add this for memset, strcmp, strcpy
#include <math.h>
#include <stdlib.h>
#include "../includes/global.h"
#include "../includes/function.h"
#include "../includes/register.h"

void register_form(User *user) {
    printf("====================================\n");
    printf("       USER REGISTRATION        \n");
    printf("====================================\n");

    // Clear any existing data in user struct
    memset(user, 0, sizeof(User));
    
    do {
        printf("Username: ");
        fgets(user->username, sizeof(user->username), stdin);
        if(!input_string(user->username)) {
            msg_error("Invalid username format!\n");
            continue;
        }
        if(is_username_exists(user->username)) {
            msg_error("Username already exists! Please enter another username.\n");
        } else {
            break;
        }
    } while (1);

    do {
        printf("Password: ");
        fgets(user->password, sizeof(user->password), stdin);
        trim_trailing_spaces(user->password);
        if(validate_password(user->password)) {
            break;
        }
    } while (1);

    do {
        printf("Confirm Password: ");
        char confirm_password[50];
        fgets(confirm_password, sizeof(confirm_password), stdin);
        trim_trailing_spaces(confirm_password);
        
        if(strcmp(user->password, confirm_password) != 0) {
            msg_error("Passwords do not match!\n");
        } else {
            break;
        }
    } while (1);

    do {
        printf("Email: ");
        fgets(user->email, sizeof(user->email), stdin);
        if(!input_string(user->email) || !is_validation_email(user->email)) {
            msg_error("Invalid email format!\n");
            continue;
        }
        if(is_email_exists(user->email)) {
            msg_error("Email already exists! Please enter another email.\n");
        } else {
            break;
        }
    } while (1);

    do {
        printf("Phone Number: ");
        fgets(user->phone, sizeof(user->phone), stdin);
        if(!input_string(user->phone) || !is_validation_phone(user->phone)) {
            msg_error("Invalid phone number format!\n");
            continue;
        }
        if(is_phone_exists(user->phone)) {
            msg_error("Phone already exists! Please enter another phone.\n");
        } else {
            break;
        }
    } while (1);

    do {
        printf("Full Name: ");
        fgets(user->full_name, sizeof(user->full_name), stdin);
        if(!input_string(user->full_name)) {
            msg_error("Invalid name format!\n");
        } else {
            break;
        }
    } while (1);

    do {
        printf("Address: ");
        fgets(user->address, sizeof(user->address), stdin);
        if(!input_string(user->address)) {
            msg_error("Invalid address format!\n");
        } else {
            break;
        }
    } while (1);

    do {
        printf("Account Type (1: Buyer, 2: Seller): ");
        char type[10];
        fgets(type, sizeof(type), stdin);
        trim_trailing_spaces(type);
        user->account_type = atoi(type);
        
        if(user->account_type != 1 && user->account_type != 2) {
            msg_error("Invalid account type! Please enter 1 or 2.\n");
        } else {
            break;
        }
    } while (1);

    if(user->account_type == 2) {
        do {
            printf("Shop Name: ");
            fgets(user->shop_name, sizeof(user->shop_name), stdin);
            if(!input_string(user->shop_name)) {
                msg_error("Invalid shop name format!\n");
            } else {
                break;
            }
        } while (1);

        do {
            printf("Warehouse Address: ");
            fgets(user->warehouse_address, sizeof(user->warehouse_address), stdin);
            if(!input_string(user->warehouse_address)) {
                msg_error("Invalid warehouse address format!\n");
            } else {
                break;
            }
        } while (1);
    } else {
        strcpy(user->shop_name, ".");
        strcpy(user->warehouse_address, ".");
    }

    // Add user data
    if(add_user_data(user)) {
        is_logged_in = 1;
        current_user = *user;
        msg_success("\nRegistration Successful!\n");
        handle_remember_login();
    } else {
        msg_error("Registration Failed!\n");
    }
    printf("====================================\n");
}