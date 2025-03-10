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
    printf("3. View cart\n");
    printf("4. Add to cart\n");

    printf("\n");
    printf("5. Delete from cart\n");
    printf("6. Checkout\n");
    printf("7. View Orders\n");
    
    printf("\n");
    printf("8. Change password\n");


    printf("\n");
    printf("0. Logout\n");
    printf("Enter your choice: ");
}
void view_selection_address() {
    printf("\n========== Address Selection ==========\n");
    printf("1. Use current information to receive goods\n");
    printf("2. Use other information to receive goods\n");
    printf("Enter your choice: ");
}
void view_delete_from_cart() {
    msg_error("\n========== Delete from cart ==========\n");
    printf("1. Delete all products\n");
    printf("2. Delete a specific product\n");
    printf("Enter your choice: ");
}
void view_add_more_to_cart() {
    msg_error("\n========== Add More Products ==========\n");
    printf("Do you want to add more products to cart?\n");
    printf("1. Yes\n");
    printf("2. No\n");
    printf("Enter your choice: ");
}