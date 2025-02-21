#include <stdio.h>
#include <math.h>
#include <string.h>
#include "includes/global.h"
#include "includes/register.h"
#include "includes/login.h"
int main() {
    printf("\n=== E-commerce System ===\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    while(1) {
        switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
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
