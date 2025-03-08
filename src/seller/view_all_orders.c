#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/view_ui.h"
typedef struct {        
    int id;
    char name[100];
} Product_;
int load_products(Product_ products[]) {
    FILE *file = fopen("data/products.txt", "r");
    if (file == NULL) {
        msg_error("Error opening products file for reading!\n");
        return 0;
    }

    int count = 0;
    char username[100], category[100], name[100], price[100], quantity[100], description[100];

    while (fgets(username, sizeof(username), file) != NULL && count < MAX_PRODUCTS) {
        trim_trailing_spaces(username);
        if(strlen(username) == 0) {
            break;
        }

        fgets(category, sizeof(category), file);
        trim_trailing_spaces(category);

        fgets(name, sizeof(name), file);
        trim_trailing_spaces(name);

        fgets(price, sizeof(price), file);
        trim_trailing_spaces(price);

        fgets(quantity, sizeof(quantity), file);
        trim_trailing_spaces(quantity);

        fgets(description, sizeof(description), file);
        trim_trailing_spaces(description);

        products[count].id = count + 1; // ID sản phẩm tính từ 1
        strcpy(products[count].name, name);
        count++;
    }

    fclose(file);
    return count; // Trả về số lượng sản phẩm đã đọc
}

// Hàm hiển thị danh sách đã bán
void view_all_orders() {
    Product_ products[MAX_PRODUCTS];
    int product_count = load_products(products); // Tải sản phẩm từ file

    FILE *file = fopen("data/orders.txt", "r");
    if (file == NULL) {
        msg_error("Error opening orders file for reading!\n");
        return;
    }

    char seller_username[100], buyer_username[100], email[100], phone[100], full_name[100], address[100], desc[5000];
    float total_payment;
    char date[100];

    printf("\n========== Sold Orders ==========\n");
    int order_count = 0;

    while (fgets(seller_username, sizeof(seller_username), file) != NULL) {
        trim_trailing_spaces(seller_username);
        if(strcmp(seller_username, current_user.username) != 0 || strlen(seller_username) == 0) {
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
        printf("-> Product_s:\n");
        int product_id, quantity;
        while (fscanf(file, "%d\n", &product_id) == 1 && fscanf(file, "%d\n", &quantity) == 1) {
            // Tìm tên sản phẩm dựa trên ID
            if (product_id > 0 && product_id <= product_count) {
                printf("   - Product_ Name: \033[32m%s\033[0m, Quantity: \033[32m%d\033[0m\n", products[product_id - 1].name, quantity);
            } else {
                printf("   - Product_ ID: %d, Quantity: %d (Invalid ID)\n", product_id, quantity);
            }
        }
        printf("--------------------------------\n");
    }

    if (order_count == 0) {
        msg_error("No orders found for the current seller!\n");
    }

    printf("============END============\n\n");
    fclose(file);
}
