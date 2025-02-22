#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../includes/global.h"
#include "../includes/login.h"
#include "../includes/viewui.h"
#include "../includes/function.h"

User currentUser;

int handleLogin(User *user) {
    if (user == NULL) {
        printf("Invalid user data!\n");
        return 0;
    }

    FILE *file = fopen("data/Users.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    char line[512];
    char username[50], password[50], email[100], phone[20], fullName[100], address[200], shopName[200], warehouseAddress[200];
    int accountType;

    while (!feof(file)) {
        fgets(line, sizeof(line), file);
        strcpy(username, line);
        trimTrailingSpaces(username);

        fgets(line, sizeof(line), file);
        strcpy(password, line);
        trimTrailingSpaces(password);

        fgets(line, sizeof(line), file);
        strcpy(email, line);
        trimTrailingSpaces(email);

        fgets(line, sizeof(line), file);
        strcpy(phone, line);
        trimTrailingSpaces(phone);

        fgets(line, sizeof(line), file);
        strcpy(fullName, line);
        trimTrailingSpaces(fullName);


        fgets(line, sizeof(line), file);
        strcpy(address, line);
        trimTrailingSpaces(address);

        fgets(line, sizeof(line), file);
        trimTrailingSpaces(line);
        accountType = atoi(line);

        fgets(line, sizeof(line), file);
        strcpy(shopName, line);
        trimTrailingSpaces(shopName);

        fgets(line, sizeof(line), file);
        strcpy(warehouseAddress, line);
        trimTrailingSpaces(warehouseAddress);

        if (strcmp(username, user->username) == 0 && strcmp(password, user->password) == 0) {
            strcpy(currentUser.username, username);
            strcpy(currentUser.password, password);
            strcpy(currentUser.fullName, fullName);
            strcpy(currentUser.email, email);
            strcpy(currentUser.phone, phone);
            strcpy(currentUser.address, address);
            currentUser.accountType = accountType;
            strcpy(currentUser.shopName, shopName);
            strcpy(currentUser.warehouseAddress, warehouseAddress);
            fclose(file);
            return 1;
        }

        fgets(line, sizeof(line), file);
        fgets(line, sizeof(line), file);
    }

    fclose(file);
    return 0;
}


void loginForm(User *user) {
    int isReLogin = 1;
    do {
        printf("====================================\n");
        printf("             USER LOGIN        \n");
        printf("====================================\n");
        printf("Username: ");
        scanf("%s", user->username);
        
        printf("Password: ");
        scanf("%s", user->password);

        if (handleLogin(user)) {
            is_logged_in = 1;
            isReLogin = 0;
            msgSuccess("Login successful!\n");

        } else {
            msgError("Invalid username or password!\n");
            isReLogin = viewUIReLogin();
        }
    } while (isReLogin == 1);
}
