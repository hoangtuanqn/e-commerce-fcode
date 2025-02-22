#include <stdio.h>
#include <stdlib.h>
#include "../includes/function.h"
#include "../includes/viewui.h"

void viewUIStart() {
    system("cls");
    printf("\n=== E-commerce System ===\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}
void viewUIBuyer() {
    printf("\n========== Welcome to Your Shopping Portal! ==========\n");
    printf("We are excited to assist you in finding the best products tailored to your needs.\n");
    printf("=====================================================\n\n");

    printf("\n========== Dashboard! ==========\n");
    printf("Explore our wide range of products available for you.\n");
    printf("Total items available: [quantity]\n");
    printf("Number of orders placed: [number of orders]\n");
    printf("Total amount spent: [total amount]\n");
    printf("=====================================================\n\n");

    printf("1. Browse Products\n");
    printf("2. View Cart\n");
    printf("3. Checkout\n");
    printf("4. Logout\n");
    printf("Enter your choice: ");

}
viewUISellerHeader() {
    printf("\n========== Welcome to the system! ==========\n");
    printf("We are excited to support you in your selling journey.\n");
    printf("=====================================================\n\n");

    printf("\n========== Dashboard! ==========\n");
    printf("Stock available: [quantity]\n");
    printf("Number of orders sold: [number of orders]\n");
    printf("Total sales amount: [total amount]\n");
    printf("=====================================================\n\n");
}
void viewUISeller() {
    printf("1. Add Category\n");
    printf("2. Add Product\n");
    printf("3. View Product\n");
    printf("4. Update Product\n");
    printf("5. Delete Product\n");
    printf("6. Logout\n");
    printf("Enter your choice: ");
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

