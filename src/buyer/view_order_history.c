#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/buyer/view_ui.h"


// Hàm hiển thị lịch sử đơn hàng
void view_order_history() {
    Product products[MAX_PRODUCTS];
    read_product_data();

    FILE *file = fopen("data/orders.txt", "r");
    if (file == NULL) {
        msg_error("Error opening orders file for reading!\n");
        return;
    }

    char seller_username[100], buyer_username[100], email[100], phone[100], full_name[100], address[100], desc[5000];
    float total_payment;
    char date[100];

    printf("\n========== Order History ==========\n");
    int order_count = 0;

    while (fgets(seller_username, sizeof(seller_username), file) != NULL) {
        trim_trailing_spaces(seller_username);
        if(strlen(seller_username) == 0) {
            continue;
        }
        fgets(buyer_username, sizeof(buyer_username), file);
        trim_trailing_spaces(buyer_username);

        fgets(email, sizeof(email), file);
        trim_trailing_spaces(email);

        fgets(phone, sizeof(phone), file);
        trim_trailing_spaces(phone);

        fgets(full_name, sizeof(full_name), file);
        trim_trailing_spaces(full_name);

        fgets(address, sizeof(address), file);
        trim_trailing_spaces(address);

        fgets(date, sizeof(date), file);
        trim_trailing_spaces(date);

        fgets(desc, sizeof(desc), file); // Đọc ghi chú
        trim_trailing_spaces(desc); // Trim ghi chú

        fscanf(file, "%f\n", &total_payment); // Đọc tổng tiền

        printf("Order #%d:\n", ++order_count);
        printf("-> Seller Username: \033[32m%s\033[0m\n", seller_username);
        printf("-> Buyer Username: \033[32m%s\033[0m\n", buyer_username);
        printf("-> Email: \033[32m%s\033[0m\n", email);
        printf("-> Phone: \033[32m%s\033[0m\n", phone);
        printf("-> Full Name: \033[32m%s\033[0m\n", full_name);
        printf("-> Address: \033[32m%s\033[0m\n", address);
        printf("-> Total Payment: \033[32m$%.2f\033[0m\n", total_payment);
        printf("-> Order Date: \033[32m%s\033[0m\n", date);
        printf("-> Notes: \033[32m%s\033[0m\n", desc);

        // Đọc và in ra các sản phẩm trong đơn hàng
        printf("-> Products:\n");
        int product_id, quantity;
        while (fscanf(file, "%d\n", &product_id) == 1 && fscanf(file, "%d\n", &quantity) == 1) {
            // Tìm tên sản phẩm dựa trên ID
            if (product_id > 0 && product_id <= counter_product_all) {
                printf("   - Product Name: \033[32m%s\033[0m, Quantity: \033[32m%d\033[0m\n", products[product_id - 1].name_product, quantity);
            } else {
                printf("   - Product ID: %d, Quantity: %d (Invalid ID)\n", product_id, quantity);
            }
        }
        fseek(file, -1, SEEK_CUR); // Move back to read the next order
        fgets(desc, sizeof(desc), file); // Đọc ghi chú
        trim_trailing_spaces(desc); // Trim ghi chú
        printf("-> Notes: %s\n", desc);
        printf("--------------------------------\n");
    }

    if (order_count == 0) {
        msg_error("No orders found!\n");
    }

    printf("============END============\n\n");
    fclose(file);
}