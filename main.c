#include <stdio.h>
#include <string.h>
#include "includes/global.h"
#include "includes/register.h"
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
	User newUser;
    while (1) {
        viewUIStart();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerForm(&newUser);
                break;
            case 2:
                printf("Login functionality not implemented yet.\n");
                break;
            case 3:
                printf("Exit successfully\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
