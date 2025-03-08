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

void handle_add_product(Product *product) {
    read_product_data();
    product_data[++counter_product_all] = *product;
    write_product_data();
    msg_success("Product added successfully!\n\n");
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
        if(!is_validation_number(category_id, 1, counter_category_seller)) {
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
        handle_add_product(&product);
    } else {
        msg_error("Product addition cancelled!\n");
    }
}
