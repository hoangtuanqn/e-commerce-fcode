#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/view_ui.h"
#include "../../includes/seller/view_all_category.h"

int handle_add_product(char *product_name, char *category_name, float price, int quantity, char *description) {
    if (product_name[0] == '\n') {
        msg_error("Product name cannot be empty!\n\n");
        return 0;
    }

    FILE *file = fopen("data/products.txt", "a");
    if (file == NULL) {
        msg_error("Error opening file for appending!\n");
        return 0;
    }
    fprintf(file, "%s\n%s\n%s\n%.2f\n%d\n%s\n", current_user.username, category_name, product_name, price, quantity, description); // Ghi thông tin sản phẩm
    fclose(file);
    msg_success("Product added successfully!\n\n");
    return 1;
}
char *check_name_category(int category_id) {
    FILE *file = fopen("data/categories.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return NULL;
    }
    char username[100], category[100];
    int cnt = 0;
    while (fgets(username, sizeof(username), file) != NULL && fgets(category, sizeof(category), file) != NULL) {
        trim_trailing_spaces(username);
        trim_trailing_spaces(category);
        if (strcmp(username, current_user.username) == 0) {
            ++cnt;
        }
        if (cnt == category_id) {
            fclose(file);
            return strdup(category); // Use strdup to return a dynamically allocated copy of the category
        }
    }
    fclose(file);
    return NULL;
}
void view_add_product() {
    char product_name[100], description[256];
    float price;
    int quantity, category_id;

    printf("\n========== Add Product ==========\n");
    int quantity_category = view_all_category();
    do {
        printf("Enter id category: ");
         if (scanf("%d", &category_id) != 1) {
            msg_error("Invalid input! Please enter a valid id category.\n");
            while(getchar() != '\n');
        } else if(category_id > quantity_category || category_id < 1) {
            msg_error("Category not found! Please enter again.\n");
        } else {
            break;
        }
    } while (category_id > quantity_category || category_id < 1);

    do {
        printf("Enter product name: ");
        getchar();
        fgets(product_name, sizeof(product_name), stdin);
        trim_trailing_spaces(product_name);
        if (product_name[0] == '\n') {
            msg_error("Product name cannot be empty! Please enter again.\n");
        }
    } while (strlen(product_name) == 0);

    do {
        printf("Enter product price: ");
        if (scanf("%f", &price) != 1) {
            msg_error("Invalid input! Please enter a valid price.\n");
            while(getchar() != '\n');
        } else {
            break;
        }
    } while (1);


    do {
        printf("Enter product quantity: ");
        if (scanf("%d", &quantity) != 1) {
            msg_error("Invalid input! Please enter a valid quantity.\n");
            while(getchar() != '\n');
        } else if(quantity < 0) {
            msg_error("Quantity cannot be negative! Please enter again.\n");
        } else {
            break;
        }
    } while (1);


    do {
        printf("Enter product description: ");
        getchar(); 
        fgets(description, sizeof(description), stdin);
        trim_trailing_spaces(description);
        if (strlen(description) == 0) {
            msg_error("Description cannot be empty! Please enter again.\n");
        }
    } while (strlen(description) == 0);

    // Gọi hàm để thêm sản phẩm
    handle_add_product(product_name, check_name_category(category_id), price, quantity, description);
}
