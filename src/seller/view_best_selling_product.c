#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/global_seller.h"
#include "../../includes/seller/function_seller.h"
#include "../../includes/seller/view_ui.h"
void view_best_selling_product() {
    msg_bold("\n========== Best Selling Product ==========\n");
    read_product_data();

    // Use pointer array for more efficient sorting
    Product *product_ptrs[MAX_PRODUCTS];
    int product_count = 0;

    // Store pointers to seller's products
    for(int i = 0; i < counter_product_all; ++i) {
        if(strcmp(product_data[i].username, current_user.username) == 0 && 
           product_data[i].status != 3) {
            product_ptrs[product_count++] = &product_data[i];
        }
    }

    // Sort using pointers (faster than copying whole structs)
    for(int i = 0; i < product_count - 1; i++) {
        for(int j = 0; j < product_count - i - 1; j++) {
            if(product_ptrs[j]->sold_quantity < product_ptrs[j + 1]->sold_quantity) {
                Product *temp = product_ptrs[j];
                product_ptrs[j] = product_ptrs[j + 1];
                product_ptrs[j + 1] = temp;
            }
        }
    }

    // Display sorted products
    if(product_count == 0) {
        msg_error("You don't have any products!\n\n");
    } else {
        for(int i = 0; i < product_count; ++i) {
            printf("%d. Name Product: \033[32m%s\033[0m\n", i + 1, product_ptrs[i]->name_product);
            printf("\tPrice: \033[32m$%.2f\033[0m\n", product_ptrs[i]->price);
            printf("\tQuantity: \033[32m%d\033[0m\n", product_ptrs[i]->quantity);
            printf("\tDescription: \033[32m%s\033[0m\n", product_ptrs[i]->description);
            printf("\tSold Quantity: \033[32m%d\033[0m\n", product_ptrs[i]->sold_quantity);
            printf("\tCategory: \033[36m%s\033[0m\n", product_ptrs[i]->category);
            printf("\tStatus: %s%s\033[0m\n", 
                product_ptrs[i]->status == 1 ? "\033[32m" : "\033[31m",
                get_status(product_ptrs[i]->status));
            printf("--------------------------------\n\n");
        }
        printf("\nTotal products: %d\n", product_count);
    }

    printf("\n============END============\n\n");
}
