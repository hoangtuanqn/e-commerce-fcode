#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../includes/global.h"
#include "../includes/register.h"
int handleRegister(User *user) {
    if (user == NULL) {
        printf("Invalid user data!\n");
        return 0;
    }

    FILE *file = fopen("data/Users.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    if (fprintf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%d\n%s\n%s\n\n",
                user->username, user->password, user->email, user->phone,
                user->fullName, user->address, user->accountType,
                user->shopName, user->warehouseAddress) < 0) {
        printf("Error writing to file!\n");
        fclose(file);
        return 0;
    }

    fclose(file);
    return 1;
}

int isEmailExists(const char *email) {
    FILE *file = fopen("data/Users.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        char existingEmail[100];
        if (sscanf(line, "%*s %*s %99s", existingEmail) == 1) {
            if (strcmp(existingEmail, email) == 0) {
                fclose(file);
                return 1; 
            }
        }
    }

    fclose(file);
    return 0;
}
int isPhoneExists(const char *phone) {
    FILE *file = fopen("data/Users.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        char existingPhone[12];
        if (sscanf(line, "%*s %*s %*s %11s", existingPhone) == 1) {
            if (strcmp(existingPhone, phone) == 0) {
                fclose(file);
                return 1; 
            }
        }
    }

    fclose(file);
    return 0;
}
void registerForm(User *user) {
    printf("====================================\n");
    printf("       USER REGISTRATION        \n");
    printf("====================================\n");
    printf("Username: ");
    scanf("%s", user->username);
    
    printf("Password: ");
    scanf("%s", user->password);
    
    printf("Confirm Password: ");
    char confirmPassword[50];
    scanf("%s", confirmPassword);
    
    while (strcmp(user->password, confirmPassword) != 0) {
        printf("Passwords do not match! Please re-enter: ");
        scanf("%s", confirmPassword);
    }

    int emailExists;
    do {
        printf("Email: ");
        scanf("%s", user->email);
        emailExists = isEmailExists(user->email);
        if (emailExists) {
            msgError("Email already exists! Please enter another email.\n");
        }
    } while (emailExists);
    
    
    int phoneExists;
    do {
        printf("Phone Number: ");
        scanf("%s", user->phone);
        phoneExists = isPhoneExists(user->phone);
        if (phoneExists) {
            msgError("Phone already exists! Please enter another phone.\n");
        }
    } while (phoneExists);


    printf("Full Name: ");
    scanf(" %[^\n]", user->fullName);

    printf("Address: ");
    scanf(" %[^\n]", user->address);

    do {
        printf("Account Type (1: Buyer, 2: Seller): ");
        scanf("%d", &user->accountType);
        if (user->accountType < 1 || user->accountType > 2) {
            printf("Invalid account type!\n");
        }
    } while (user->accountType < 1 || user->accountType > 2);

    if (user->accountType == 2) {
        printf("Shop Name: ");
        scanf(" %[^\n]", user->shopName);

        printf("Warehouse Address: ");
        scanf(" %[^\n]", user->warehouseAddress);
    } else {
        strcpy(user->shopName, ".");
        strcpy(user->warehouseAddress, ".");
    }

    if (handleRegister(user) == 1) {
        is_logged_in = 1;
        currentUser = *user;
        msgSuccess("\nRegistration Successful!\n");
    } else {
        msgError("Registration Failed!\n");
    }
    printf("====================================\n");
}