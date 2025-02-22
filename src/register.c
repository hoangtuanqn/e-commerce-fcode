#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../includes/global.h"
#include "../includes/register.h"
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

    printf("Email: ");
    scanf("%s", user->email);
    
    

    printf("Phone Number: ");
    scanf("%s", user->phone);

    printf("Full Name: ");
    scanf(" %[^\n]", user->fullName);

    printf("Address: ");
    scanf(" %[^\n]", user->address);

    printf("Account Type (1: Buyer, 2: Seller): ");
    scanf("%d", &user->accountType);

    if (user->accountType == 2) {
        printf("Shop Name: ");
        scanf(" %[^\n]", user->shopName);

        printf("Warehouse Address: ");
        scanf(" %[^\n]", user->warehouseAddress);
    }
    is_logged_in = 1;
    printf("\nRegistration Successful!\n");
    printf("====================================\n");
}