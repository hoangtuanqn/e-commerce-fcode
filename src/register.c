#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../includes/global.h"
#include "../includes/function.h"
#include "../includes/register.h"

int handle_register(User *user) {
    if (user == NULL) {
        msg_error("Invalid user data!\n");
        return 0;
    }

    FILE *file = fopen("data/users.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    if (fprintf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%d\n%s\n%s\n",
                user->username, user->password, user->email, user->phone,
                user->full_name, user->address, user->account_type,
                user->shop_name, user->warehouse_address) < 0) {
        msg_error("Error writing to file!\n");
        fclose(file);
        return 0;
    }

    fclose(file);
    return 1;
}

int is_email_exists(const char *email) {
    FILE *file = fopen("data/users.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        char existing_email[100];
        if (sscanf(line, "%*s %*s %99s", existing_email) == 1) {
            if (strcmp(existing_email, email) == 0) {
                fclose(file);
                return 1; 
            }
        }
    }

    fclose(file);
    return 0;
}
int is_phone_exists(const char *phone) {
    FILE *file = fopen("data/users.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        char existing_phone[12];
        if (sscanf(line, "%*s %*s %*s %11s", existing_phone) == 1) {
            if (strcmp(existing_phone, phone) == 0) {
                fclose(file);
                return 1; 
            }
        }
    }

    fclose(file);
    return 0;
}
void register_form(User *user) {
    printf("====================================\n");
    printf("       USER REGISTRATION        \n");
    printf("====================================\n");
    printf("Username: ");
    scanf("%s", user->username);
    
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

    printf("Full Name: ");
    gets(user->full_name);

    printf("Address: ");
    gets(user->address);

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
        printf("Shop Name: ");
        gets(user->shop_name);

        printf("Warehouse Address: ");
        gets(user->warehouse_address);
    } else {
        strcpy(user->shop_name, ".");
        strcpy(user->warehouse_address, ".");
    }

    if (handle_register(user) == 1) {
        is_logged_in = 1;
        current_user = *user;
        msg_success("\nRegistration Successful!\n");
    } else {
        msg_error("Registration Failed!\n");
    }
    printf("====================================\n");
}