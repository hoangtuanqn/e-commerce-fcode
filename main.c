#include <stdio.h>
#include <string.h>

// Define User structure
typedef struct {
    char username[50];
    char password[50];
    char email[100];
    char phone[20];
    char fullName[100];
    char address[200];
    int accountType; // 1 = Buyer, 2 = Seller
    char shopName[100];       // Only for sellers
    char warehouseAddress[200]; // Only for sellers
} User;

void viewUIStart() {
    printf("\n=== E-commerce System ===\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

void registerForm(User *user) {
    printf("====================================\n");
    printf("       USER REGISTRATION        \n");
    printf("====================================\n");

    // Input user details
    printf("Username: ");
    scanf("%s", user->username);

    printf("Password: ");
    scanf("%s", user->password);

    printf("Confirm Password: ");
    char confirmPassword[50];
    scanf("%s", confirmPassword);

    // Validate password confirmation
    while (strcmp(user->password, confirmPassword) != 0) {
        printf("Passwords do not match! Please re-enter: ");
        scanf("%s", confirmPassword);
    }

    printf("Email: ");
    scanf("%s", user->email);

    printf("Phone Number: ");
    scanf("%s", user->phone);

    printf("Full Name: ");
    scanf(" %[^\n]", user->fullName); // Fixed format for full name input

    printf("Address: ");
    scanf(" %[^\n]", user->address); // Fixed format for address input

    // Choose account type
    printf("Account Type (1: Buyer, 2: Seller): ");
    scanf("%d", &user->accountType);

    if (user->accountType == 2) {
        printf("Shop Name: ");
        scanf(" %[^\n]", user->shopName);

        printf("Warehouse Address: ");
        scanf(" %[^\n]", user->warehouseAddress);
    }

    printf("\nRegistration Successful!\n");
    printf("====================================\n");
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
