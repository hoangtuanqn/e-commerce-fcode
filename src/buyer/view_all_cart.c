#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/view_ui.h"
int view_all_cart() {
    FILE *file = fopen("data/carts.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return 0;
    }
    
    char line[100];
    float total = 0;
    printf("\n========== Shopping Cart ==========\n");
    int i = 0;
    int reading_current_user = 0;
    
    while (fgets(line, sizeof(line), file)) {
        trim_trailing_spaces(line);
        
        // Skip empty lines
        if (line[0] == '\n' || strlen(line) == 0) {
            reading_current_user = 0;
            continue;
        }
        
        // Check if this is a username line
        if (!strchr(line, ' ')) {
            reading_current_user = (strcmp(line, current_user.username) == 0);
            continue;
        }
        
        // Process cart items only for current user
        if (reading_current_user) {
            int product_id, quantity;
            sscanf(line, "%d %d", &product_id, &quantity);
            
            // Get product details from products.txt
            FILE *product_file = fopen("data/products.txt", "r");
            char prod_line[100];
            int current_prod_id = 0;
            int found_product = 0;
            
            while (fgets(prod_line, sizeof(prod_line), product_file)) {
                current_prod_id++;
                trim_trailing_spaces(prod_line);
                if (prod_line[0] == '\n' || strlen(prod_line) == 0) continue;
                
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
                
                if (current_prod_id == product_id) {
                    float price = atof(price_str);
                    float subtotal = price * quantity;
                    total += subtotal;
                    
                    printf("%d. Product: \033[32m%s\033[0m\n", ++i, name);
                    printf("   Category: \033[32m%s\033[0m\n", category);
                    printf("   Quantity: \033[32m%d\033[0m\n", quantity);
                    printf("   Price per unit: \033[32m$%.2f\033[0m\n", price);
                    printf("   Subtotal: \033[32m$%.2f\033[0m\n\n", subtotal);
                    found_product = 1;
                    break;
                }
            }
            fclose(product_file);
            
            if (!found_product) {
                printf("%d. Product ID \033[32m%d\033[0m not found\n\n", ++i, product_id);
            }
        }
    }
    
    if (!i) {
        msg_error("Your cart is empty!\n");
    } else {
        printf("Total: \033[32m$%.2f\033[0m\n", total);
    }
    printf("============END============\n\n");
    fclose(file);
    return i;
}
