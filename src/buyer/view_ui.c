#include <stdio.h>
#include <stdlib.h>
#include "../../includes/function.h"
#include "../../includes/buyer/view_ui.h"
void view_ui_buyer_header() {
    printf("\n========== Welcome to Your Shopping Portal! ==========\n");
    printf("We are excited to assist you in finding the best products tailored to your needs.\n");
    printf("=====================================================\n\n");

    printf("\n========== Dashboard! ==========\n");
    printf("Explore our wide range of products available for you.\n");
    printf("Total items available: [quantity]\n");
    printf("Number of orders placed: [number of orders]\n");
    printf("Total amount spent: [total amount]\n");
    printf("=====================================================\n\n");
}
void view_ui_buyer() {
    printf("\n========== Buyer Menu ==========\n");
    
    printf("1. Browse Products\n");
    printf("2. Search for products\n");
    printf("\n");
    printf("3. Add to cart\n");
    printf("4. View cart\n");
    printf("5. Checkout\n");

    printf("\n");
    printf("0. Logout\n");
    printf("Enter your choice: ");
}