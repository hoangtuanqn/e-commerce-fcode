#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/buyer/view_ui.h"

void view_order_history() {
    // Load latest data
    read_order_data();
    read_product_data();

    printf("\n========== Order History ==========\n");
    int order_count = 0;

    // Loop through all orders
    for(int i = 0; i < counter_order_all; i++) {
        // Check if order belongs to current user
        if(strcmp(order_data[i].buyer, current_user.username) == 0) {
            printf("\033[1;34mOrder #%d:\033[0m\n", ++order_count);
            printf("-> Buyer Username: \033[0;36m%s\033[0m\n", order_data[i].buyer);
            printf("-> Email: \033[0;36m%s\033[0m\n", order_data[i].email);
            printf("-> Phone: \033[0;36m%s\033[0m\n", order_data[i].phone);
            printf("-> Full Name: \033[0;36m%s\033[0m\n", order_data[i].full_name);
            printf("-> Address: \033[0;36m%s\033[0m\n", order_data[i].address);
            printf("-> Order ID: \033[1;35m%s\033[0m\n", order_data[i].order_id);
            printf("-> Order Date: \033[0;36m%s\033[0m\n", order_data[i].time_buy);

            printf("\033[1;33m-> Products:\033[0m\n");
            for(int j = 0; j < order_data[i].quantity; j++) {
            int product_id = order_data[i].id_product[j];
            if(product_id > 0 && product_id <= counter_product_all) {
                printf("   - Product Name: \033[0;32m%s\033[0m\n", product_data[product_id - 1].name_product);
                printf("   - Quantity: \033[0;32m%d\033[0m\n", order_data[i].quantity_product[j]);
                printf("   - Item Total: \033[0;32m$%.2f\033[0m\n", order_data[i].total_product[j]);
                printf("   - Note: \033[0;35m%s\033[0m\n", order_data[i].note_product[j]);

                printf("   -------------------------\n");
            }
            }
            printf("-> Shipping Fee: \033[1;33m$%.2f\033[0m\n", order_data[i].shipping_fee);
            printf("-> Total: \033[1;31m$%.2f\033[0m\n", order_data[i].total);
            printf("--------------------------------\n\n");
        }
    }

    if(order_count == 0) {
        msg_error("No orders found!\n");
    }

    printf("============END============\n\n");
}