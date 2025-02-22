#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../includes/global.h"
#include "../includes/login.h"
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
    while (fgets(line, sizeof(line), file)) {
        char username[50];
        char password[50];
        if (sscanf(line, "%s %s", username, password) == 2) {
            if (strcmp(username, user->username) == 0 && strcmp(password, user->password) == 0) {
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    return 0;
}
    
int viewUIReLogin() {
    int choice;
    printf("\n=== Do you want to login again? ===\n");
    printf("1. Yes\n");
    printf("2. No\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    if(choice != 1 && choice != 2) {
        printf("Invalid choice!\n");
        return viewUIReLogin();
    }
    return choice;
}
void loginForm(User *user) {
    int isReLogin = 0;
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
            printf("Login successful!\n");
        } else {
            printf("Invalid username or password!\n");
            isReLogin = viewUIReLogin();
        
        }
        printf("\n");
    } while(isReLogin == 1);

}
