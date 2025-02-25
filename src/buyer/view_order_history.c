#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/buyer/view_ui.h"

#define MAX_PRODUCTS 100 // Giới hạn số sản phẩm có thể lưu trữ

// Cấu trúc để lưu thông tin sản phẩm
typedef struct {
    int id;
    char name[100];
} Product;

// Hàm đọc danh sách sản phẩm từ file
int load_products(Product products[]) {
    FILE *file = fopen("data/Products.txt", "r");
    if (file == NULL) {
        msg_error("Error opening products file for reading!\n");
        return 0;
    }

    int count = 0;
    char username[100], category[100], name[100], price[100], quantity[100], description[100];

    while (fgets(username, sizeof(username), file) != NULL && count < MAX_PRODUCTS) {
        trim_trailing_spaces(username);
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

// Hàm hiển thị lịch sử đơn hàng
void view_order_history() {
    Product products[MAX_PRODUCTS];
    int product_count = load_products(products); // Tải sản phẩm từ file

    FILE *file = fopen("data/orders.txt", "r");
    if (file == NULL) {
        msg_error("Error opening orders file for reading!\n");
        return;
    }

    char username[100], email[100], phone[100], full_name[100], address[100], desc[5000];
    float total_payment;
    char date[100];

    printf("\n========== Order History ==========\n");
    int order_count = 0;

    while (fgets(username, sizeof(username), file) != NULL) {
        trim_trailing_spaces(username);
        if(strlen(username) == 0) {
            break;
        }
        fgets(email, sizeof(email), file);
        trim_trailing_spaces(email);
        fgets(phone, sizeof(phone), file);
        trim_trailing_spaces(phone);
        fgets(full_name, sizeof(full_name), file);
        trim_trailing_spaces(full_name);
        fgets(address, sizeof(address), file);
        trim_trailing_spaces(address);
        fscanf(file, "%f\n", &total_payment); // Đọc tổng tiền
        fgets(date, sizeof(date), file);
        trim_trailing_spaces(date);

        printf("Order #%d:\n", ++order_count);
        printf("-> Username: \033[32m%s\033[0m\n", username);
        printf("-> Email: \033[32m%s\033[0m\n", email);
        printf("-> Phone: \033[32m%s\033[0m\n", phone);
        printf("-> Full Name: \033[32m%s\033[0m\n", full_name);
        printf("-> Address: \033[32m%s\033[0m\n", address);
        printf("-> Total Payment: \033[32m$%.2f\033[0m\n", total_payment);
        printf("-> Order Date: \033[32m%s\033[0m\n", date);

        // Đọc và in ra các sản phẩm trong đơn hàng
        printf("-> Products:\n");
        int product_id, quantity;
        while (fscanf(file, "%d %d\n", &product_id, &quantity) == 2) {
            // Tìm tên sản phẩm dựa trên ID
            if (product_id > 0 && product_id <= product_count) {
                printf("   - Product Name: \033[32m%s\033[0m, Quantity: \033[32m%d\033[0m\n", products[product_id - 1].name, quantity);
            } else {
                printf("   - Product ID: %d, Quantity: %d (Invalid ID)\n", product_id, quantity);
            }
        }
        fgets(desc, sizeof(desc), file); // Đọc ghi chú
        printf("-> Notes: %s\n", desc);
        printf("--------------------------------\n");
    }

    if (order_count == 0) {
        msg_error("No orders found!\n");
    }

    printf("============END============\n\n");
    fclose(file);
}