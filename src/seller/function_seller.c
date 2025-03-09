#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/global_seller.h"
#include "../../includes/seller/function_seller.h"

void write_category_data() {
    FILE *file = fopen("data/categories.txt", "w");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }
    for(int i = 0; i < counter_category_all; ++i) {
        if(strlen(category_data[i].category) > 0) {
            fprintf(file, "%s\n%s\n\n", 
                category_data[i].username, 
                category_data[i].category
            );
        }
    }
    fclose(file);
}




int counter_products_in_category(char *name_your_category) {
    int count = 0;
    for(int i = 0; i < counter_product_all; ++i) {
        if(strcmp(product_data[i].category, name_your_category) == 0 && 
            strcmp(product_data[i].username, current_user.username) == 0) {
                ++count;
        }
    }
    return count;
}