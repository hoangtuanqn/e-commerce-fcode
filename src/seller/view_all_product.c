#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/global_seller.h"
#include "../../includes/seller/function_seller.h"
#include "../../includes/seller/view_ui.h"
void view_all_product() {
    printf("\n========== All Product ==========\n");
    read_category_data();
    read_product_data();
    int total_products = 0;

    // Display products by category
    for(int k = 0; k < counter_category_all; ++k) {
        int is_product = 0;
        if(strcmp(category_data[k].username, current_user.username) == 0) {
            // Print category header
            printf("\n[Category: \033[36m%s\033[0m]\n", category_data[k].category);
            
            int products_in_category = 0;
            // Find all products in this category
            for(int i = 0; i < counter_product_all; ++i) {
                if(strcmp(product_data[i].username, current_user.username) == 0 && 
                   strcmp(product_data[i].category, category_data[k].category) == 0) {
                    is_product = 1;
                    printf("%d. Name Product: \033[32m%s\033[0m\n", ++products_in_category, product_data[i].name_product);
                    printf("\tPrice: \033[32m$%.2f\033[0m\n", product_data[i].price);
                    printf("\tQuantity: \033[32m%d\033[0m\n", product_data[i].quantity);
                    printf("\tDescription: \033[32m%s\033[0m\n", product_data[i].description);
                    printf("--------------------------------\n\n");
                }
            }
            total_products += products_in_category;
            if(!is_product) {
                msg_error("There are no products in this category!\n\n");
            }
        }
    }
    
    if(total_products) {
        printf("\nTotal products: %d\n", total_products);
    }
    printf("\n============END============\n\n");
}
