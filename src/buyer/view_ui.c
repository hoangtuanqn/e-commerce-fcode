#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/function.h"
#include "../../includes/buyer/view_ui.h"
void view_ui_buyer_header()
{
    read_product_data();
    read_order_data();

    int total_available_items = 0;
    int total_orders = 0;
    float total_spent = 0;

    // Calculate total available items
    for (int i = 0; i < counter_product_all; i++)
    {
        if (product_data[i].quantity > 0 && product_data[i].status == 1)
        {
            total_available_items += product_data[i].quantity;
            printf("Run this is");
        }
    }

    // Calculate buyer's orders and total spent
    for (int i = 0; i < counter_order_all; i++)
    {
        if (strcmp(order_data[i].buyer, current_user.username) == 0)
        {
            float order_total = 0;

            for (int j = 0; j < order_data[i].quantity; j++)
            {
                order_total += order_data[i].total_product[j];
            }

            // Only count completed orders
            if (order_data[i].status == 0 || order_data[i].status == 1)
            {
                total_orders++;
                total_spent += order_total;
            }
        }
    }

    printf("\n========== Welcome to Your Shopping Portal! ==========\n");
    printf("We are excited to assist you in finding the best products tailored to your needs.\n");
    printf("=====================================================\n\n");

    printf("\n========== Dashboard! ==========\n");
    printf("Explore our wide range of products available for you.\n");
    printf("Total items available: \033[1;32m%d\033[0m items\n", total_available_items);
    printf("Number of orders placed: \033[1;32m%d\033[0m orders\n", total_orders);
    printf("Total amount spent: \033[1;32m$%.2f\033[0m\n", total_spent);
    printf("=====================================================\n\n");
}
void view_ui_buyer()
{
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
void view_selection_address()
{
    printf("\n========== Address Selection ==========\n");
    printf("1. Use current information to receive goods\n");
    printf("2. Use other information to receive goods\n");
    printf("Enter your choice: ");
}
void view_delete_from_cart()
{
    msg_error("\n========== Delete from cart ==========\n");
    printf("1. Delete all products\n");
    printf("2. Delete a specific product\n");
    printf("Enter your choice: ");
}
void view_add_more_to_cart()
{
    msg_error("\n========== Add More Products ==========\n");
    printf("Do you want to add more products to cart?\n");
    printf("1. Yes\n");
    printf("2. No\n");
    printf("Enter your choice: ");
}