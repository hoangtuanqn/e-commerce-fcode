#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/buyer/view_ui.h"

// Hàm tìm kiếm sản phẩm theo từ khóa
void view_search_products() {
    FILE *file = fopen("data/products.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }

    char username[100], category[100], name_product[100], price[100], quantity[100], description[100];
    char keyword[100];

    // Nhập từ khóa tìm kiếm từ người dùng
    getchar();
    printf("Enter search keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    trim_trailing_spaces(keyword);

    // Chuyển đổi từ khóa về chữ thường
    for (int i = 0; keyword[i]; i++) {
        keyword[i] = tolower(keyword[i]);
    }

    printf("\n========== Search Results ==========\n");
    int found = 0; // Biến đánh dấu có tìm thấy sản phẩm hay không
    int id_product = 0;
    while (!feof(file)) {
        fgets(username, sizeof(username), file);
        trim_trailing_spaces(username);
        if(username[0] == '\n') {
            break;
        }
        ++id_product;

        fgets(category, sizeof(category), file);
        trim_trailing_spaces(category);

        fgets(name_product, sizeof(name_product), file);
        trim_trailing_spaces(name_product);

        fgets(price, sizeof(price), file);
        trim_trailing_spaces(price);

        fgets(quantity, sizeof(quantity), file);
        trim_trailing_spaces(quantity);

        fgets(description, sizeof(description), file);
        trim_trailing_spaces(description);

        // Chuyển đổi tên sản phẩm về chữ thường
        char name_product_lower[100];
        strcpy(name_product_lower, name_product);
        for (int i = 0; name_product_lower[i]; i++) {
            name_product_lower[i] = tolower(name_product_lower[i]);
        }

        // Kiểm tra xem tên sản phẩm có chứa từ khóa không
        if (strstr(name_product_lower, keyword) != NULL) {
            printf("->\tProduct ID: \033[32m%d\033[0m\n", id_product);
            printf("->\tProduct Name: \033[32m%s\033[0m\n", name_product);
            printf("->\tSeller: \033[32m%s\033[0m\n", username);
            printf("->\tPrice: \033[32m$%s\033[0m\n", price);
            printf("->\tQuantity: \033[32m%s\033[0m\n", quantity);
            printf("->\tDescription: \033[32m%s\033[0m\n", description);
            printf("--------------------------------\n");
            found = 1; // Đánh dấu đã tìm thấy ít nhất một sản phẩm
        }
        name_product[0] = '\n';
        category[0] = '\n';
        price[0] = '\n';
        quantity[0] = '\n';
        description[0] = '\n';
    }

    if (!found) {
        msg_error("No products found with the keyword ");
        printf("%s\n", keyword);
    }

    printf("============END============\n\n");
    fclose(file);
}
