#include <stdio.h>
#include <stdlib.h>


void viewUIStart() {
    system("cls");
    printf("\n=== E-commerce System ===\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}
void viewUIBuyer() {
    system("cls");
    printf("\n========== Welcome to the system! ==========\n");
    printf("We are delighted to assist you with your shopping experience.\n");

}
void viewUISeller() {
    system("cls");
    printf("\n========== Welcome to the system! ==========\n");
    printf("We are excited to support you in your selling journey.\n");
}

int viewUIReLogin() {
    int choice;
    printf("\n=== Do you want to login again? ===\n");
    printf("1. Yes\n");
    printf("2. No\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    if (choice != 1 && choice != 2) {
        msgError("Invalid choice!\n");
        return viewUIReLogin();
    }
    return choice;
}