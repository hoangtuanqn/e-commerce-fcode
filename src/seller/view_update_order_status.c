#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/view_ui.h"

void handle_update_order_status(int order_id, int new_status) {
    // Validate order ID
    if(order_id <= 0 || order_id > counter_order_all) {
        msg_error("Invalid order ID!\n");
        return;
    }

    int order_idx = order_id - 1;
    int has_seller_products = 0;

    // Check if order has products from current seller
    for(int j = 0; j < order_data[order_idx].quantity; j++) {
        int product_id = order_data[order_idx].id_product[j];
        if(product_id > 0 && product_id <= counter_product_all) {
            if(strcmp(product_data[product_id - 1].username, current_user.username) == 0) {
                has_seller_products = 1;
                break;
            }
        }
    }

    if(!has_seller_products) {
        msg_error("Order not found or doesn't contain your products!\n");
        return;
    }

    // Update status
    order_data[order_idx].status = new_status;
    write_order_data();

    msg_success("Order status updated successfully!\n");
}

void view_update_order_status() {
    read_order_data();
    read_product_data();

    printf("\n========== Update Order Status ==========\n\n");
    
    // Display seller's orders first
    int order_count = 0;
    for(int i = 0; i < counter_order_all; i++) {
        int has_seller_products = 0;
        float order_total = 0;

        // Check if order has products from current seller
        for(int j = 0; j < order_data[i].quantity; j++) {
            int product_id = order_data[i].id_product[j];
            if(product_id > 0 && product_id <= counter_product_all) {
                if(strcmp(product_data[product_id - 1].username, current_user.username) == 0) {
                    has_seller_products = 1;
                    break;
                }
            }
        }

        if(has_seller_products) {
            printf("Order #%d:\n", ++order_count);
            printf("-> Status: %s\n", 
                order_data[i].status == 0 ? "\033[33mPending\033[0m" :
                order_data[i].status == 1 ? "\033[32mCompleted\033[0m" : 
                "\033[31mFailed\033[0m");
            printf("-> Buyer: %s\n", order_data[i].buyer);
            printf("-> Order Date: %s\n", order_data[i].time_buy);
            printf("-> Products from your shop:\n");

            for(int j = 0; j < order_data[i].quantity; j++) {
                int product_id = order_data[i].id_product[j];
                if(product_id > 0 && product_id <= counter_product_all) {
                    if(strcmp(product_data[product_id - 1].username, current_user.username) == 0) {
                        printf("   - %s (Qty: %d)\n", 
                            product_data[product_id - 1].name_product,
                            order_data[i].quantity_product[j]);
                        order_total += order_data[i].total_product[j];
                    }
                }
            }
            printf("-> Your Total: $%.2f\n", order_total);
            printf("--------------------------------\n");
        }
    }

    if(order_count == 0) {
        msg_error("No orders found!\n");
        return;
    }

    // Get order to update
    int order_id;
    printf("\nEnter Order ID to update (1-%d): ", counter_order_all);
    if(scanf("%d", &order_id) != 1) {
        msg_error("Invalid input!\n");
        while(getchar() != '\n');
        return;
    }
    while(getchar() != '\n');

    // Get new status
    printf("\nSelect new status:\n");
    printf("0 - Pending\n");
    printf("1 - Completed\n");
    printf("2 - Failed\n");
    printf("Enter status: ");

    int new_status;
    if(scanf("%d", &new_status) != 1) {
        msg_error("Invalid input!\n");
        while(getchar() != '\n');
        return;
    }
    while(getchar() != '\n');

    if(new_status < 0 || new_status > 2) {
        msg_error("Invalid status!\n");
        return;
    }

    handle_update_order_status(order_id, new_status);
    printf("\n============END============\n\n");
}