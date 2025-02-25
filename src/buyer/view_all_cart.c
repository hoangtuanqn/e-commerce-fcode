#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/view_ui.h"

float view_all_cart() {
    FILE *cart_file = fopen("data/carts.txt", "r");
    if (cart_file == NULL) {
        msg_error("Error opening file for reading!\n");
        return 0;
    }
    
    char cart_line[100];
    float total_amount = 0;
    printf("\n========== Shopping Cart ==========\n");
    int product_count = 0;
    int is_current_user = 0;
    const float shipping_fee = 5.00;

    while (fgets(cart_line, sizeof(cart_line), cart_file)) {
        trim_trailing_spaces(cart_line);
        
        // Skip empty lines
        if (cart_line[0] == '\n' || strlen(cart_line) == 0) {
            is_current_user = 0;
            continue;
        }
        
        // Check if this is a username line
        if (!strchr(cart_line, ' ')) {
            is_current_user = (strcmp(cart_line, current_user.username) == 0);
            continue;
        }
        
        // Process cart items only for current user
        if (is_current_user) {
            int product_id, quantity;
            sscanf(cart_line, "%d %d", &product_id, &quantity);
            
            // Get product details from products.txt
            FILE *product_file = fopen("data/products.txt", "r");
            char product_line[100];
            int current_product_id = 0;
            int product_found = 0;
            
            while (fgets(product_line, sizeof(product_line), product_file)) {
                current_product_id++;
                trim_trailing_spaces(product_line);
                if (product_line[0] == '\n' || strlen(product_line) == 0) continue;
                
                char category[100], name[100], price_str[100], qty[100], desc[100];
                
                // Read all 6 lines of product data
                fgets(category, sizeof(category), product_file);
                fgets(name, sizeof(name), product_file);
                fgets(price_str, sizeof(price_str), product_file);
                fgets(qty, sizeof(qty), product_file);
                fgets(desc, sizeof(desc), product_file);
                
                trim_trailing_spaces(category);
                trim_trailing_spaces(name);
                trim_trailing_spaces(price_str);
                
                if (current_product_id == product_id) {
                    float price = atof(price_str);
                    float subtotal = price * quantity;
                    total_amount += subtotal;
                    
                    printf("%d. Product: \033[32m%s\033[0m\n", ++product_count, name);
                    printf("   Category: \033[32m%s\033[0m\n", category);
                    printf("   Quantity: \033[32m%d\033[0m\n", quantity);
                    printf("   Price per unit: \033[32m$%.2f\033[0m\n", price);
                    printf("   Subtotal: \033[32m$%.2f\033[0m\n\n", subtotal);
                    product_found = 1;
                    break;
                }
            }
            fclose(product_file);
            
            if (!product_found) {
                printf("%d. Product ID \033[32m%d\033[0m not found\n\n", ++product_count, product_id);
            }
        }
    }
    
    if (!product_count) {
        msg_error("Your cart is empty!\n");
    } else {
        printf("Order total: \033[32m$%.2f\033[0m\n", total_amount);
        printf("Shipping: \033[32m$%.2f\033[0m\n", shipping_fee);
        printf("Total: \033[31m$%.2f\033[0m\n", total_amount + shipping_fee);
    }
    printf("============END============\n\n");
    fclose(cart_file);
    return total_amount;
}
