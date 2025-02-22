#include <stdio.h>
#include <stdlib.h>
#include "../../includes/function.h"
#include "../../includes/seller/viewui.h"
void viewUISellerHeader() {
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
    printf("\n========== Category Menu ==========\n");
    printf("1. View All Category\n");
    printf("2. Add Category\n");
    printf("3. Delete Category\n");

    printf("\n========== Product Menu ==========\n");
    printf("4. View All Product\n");
    printf("5. Add Product\n");
    printf("6. Update Product\n");
    printf("7. Delete Product\n");
    printf("\n========== Logout ==========\n");
    printf("0. Logout\n");
    printf("Enter your choice: ");
}