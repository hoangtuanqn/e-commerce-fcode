#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/global_seller.h"
#include "../../includes/seller/function_seller.h"
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

void view_add_product() {
    Product product;
    int category_id;

    msg_success("\n========== Add Product ==========\n");
    view_all_category();
    
    // Store current username
    strcpy(product.username, current_user.username);
    
    do {
        printf("Enter id category: ");
        scanf("%d", &category_id);
        if(is_validation_number(category_id, 1, counter_category_seller)) {
            msg_error("Valid data entry required\n");
        } else {
            // Get category name from id
            strcpy(product.category, check_name_category(category_id));
            break;
        }
    } while (1);

    do {
        printf("Enter product name: ");
        getchar();
        fgets(product.name_product, sizeof(product.name_product), stdin);
    } while (!input_string(product.name_product));

    do {
        char price[20];
        printf("Enter product price: ");
        fgets(price, sizeof(price), stdin);
        trim_trailing_spaces(price);
        
        float price_val = atof(price);
        if (price_val <= 0 || price_val > 2e19) {
            msg_error("Invalid input! Price must be greater than 0\n");
        } else {
            product.price = price_val;
            break;
        }
    } while (1);

    do {
        char quantity[20];
        printf("Enter product quantity: ");
        fgets(quantity, sizeof(quantity), stdin);
        trim_trailing_spaces(quantity);
        
        int quantity_val = atoi(quantity);
        if (quantity_val <= 0 || quantity_val > 2e19) {
            msg_error("Invalid input! Quantity must be greater than 0\n");
        } else {
            product.quantity = quantity_val;
            break;
        }
    } while (1);

    do {
        printf("Enter product description: ");
        fgets(product.description, sizeof(product.description), stdin);
    } while (!input_string(product.description));

    // Display product information for confirmation
    printf("\n=== Product Information ===\n");
    printf("Category: %s\n", product.category);
    printf("Name: %s\n", product.name_product);
    printf("Price: $%.2f\n", product.price);
    printf("Quantity: %d\n", product.quantity);
    printf("Description: %s\n", product.description);
    printf("==========================\n\n");

    char confirm;
    printf("Do you want to add this product? (y/n): ");
    scanf(" %c", &confirm);
    
    if (confirm == 'y' || confirm == 'Y') {
        // Call function to add product using the Product struct
        handle_add_product(
            product.name_product,
            product.category,
            product.price,
            product.quantity,
            product.description
        );
    } else {
        msg_error("Product addition cancelled!\n");
    }
}
