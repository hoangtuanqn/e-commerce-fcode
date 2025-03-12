#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../includes/function.h"
#include "../../includes/seller/view_ui.h"
void view_ui_seller_header() {
    read_product_data();
    read_order_data();

    int total_stock = 0;
    int total_orders = 0;
    float total_sales = 0;
    
    // Calculate total stock from all products
    for(int i = 0; i < counter_product_all; i++) {
        if(strcmp(product_data[i].username, current_user.username) == 0) {
            total_stock += product_data[i].quantity;
        }
    }

    // Calculate total orders and sales
    for(int i = 0; i < counter_order_all; i++) {
        int has_seller_products = 0;
        float order_total = 0;

        // Check if order has products from current seller
        for(int j = 0; j < order_data[i].quantity; j++) {
            int product_id = order_data[i].id_product[j];
            if(product_id > 0 && product_id <= counter_product_all) {
                if(strcmp(product_data[product_id - 1].username, current_user.username) == 0) {
                    // Calculate total for each product: quantity * price
                    float product_total = order_data[i].quantity_product[j] * product_data[product_id - 1].price;
                    order_total += product_total;
                    has_seller_products = 1;
                }
            }
        }

        if(has_seller_products && order_data[i].status == 1) { // Only count completed orders
            total_orders++;
            total_sales += order_total;
        }
    }

    printf("\n========== Welcome to the system! ==========\n");
    printf("We are excited to support you in your selling journey.\n");
    printf("=====================================================\n\n");

    printf("\n========== Dashboard! ==========\n");
    printf("Stock available: \033[1;32m%d\033[0m items\n", total_stock);
    printf("Number of orders completed: \033[1;32m%d\033[0m orders\n", total_orders);
    printf("Total sales amount: \033[1;32m$%.2f\033[0m\n", total_sales);
    printf("=====================================================\n\n");
}
void view_ui_seller() {
    msg_bold("\n========== Seller Menu ==========\n");
    printf("1. View All Category\n");
    printf("2. Add Category\n");
    printf("3. Update Category\n");
    printf("4. Delete Category\n");
    printf("\n");
    printf("5. View All Product\n");
    printf("6. View Best-Selling Products\n");
    printf("7. View Out-of-Stock Products\n");
    printf("\n");
    printf("8. Add Product\n");
    printf("9. Update Product\n");
    printf("10. Delete Product\n");
    printf("\n");

    printf("11. View All Order\n");
    printf("12. Update Order Status\n");
    printf("\n");
    printf("13. Change password\n");
    printf("\n");

    printf("0. Logout\n");
    printf("Enter your choice: ");
}