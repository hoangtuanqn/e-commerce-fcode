#include <stdio.h>
#include <string.h>
#include "includes/global.h"
#include "includes/register.h"
#include "includes/login.h"
// Define User structure

void viewUIStart() {
    printf("\n=== E-commerce System ===\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}


int main() {
    int choice;
	User user;
    do {
        viewUIStart();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerForm(&user);
                break;
            case 2:
                loginForm(&user);
                break;
            case 3:
                printf("Exit successfully\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (is_logged_in == 0);

    return 0;
}
