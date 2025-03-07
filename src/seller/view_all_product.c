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
    read_product_data();
    printf("\n========== All Product ==========\n");
    int counter_product = 0;
    for(int i = 0; i < counter_product_all; ++i) {
        if(strcmp(product_data[i].username, current_user.username)) {
            printf("%d. Category: \033[32m%s\033[0m\n", ++counter_product, product_data[i].category);
            printf("\tPrice: \033[32m$%s\033[0m\n", product_data[i].price);
            printf("\tName Product: \033[32m%s\033[0m\n", product_data[i].name_product);
            printf("\tQuantity: \033[32m%s\033[0m\n", product_data[i].quantity);
            printf("\tDescription: \033[32m%s\033[0m\n", product_data[i].description);
        }
    }
    if(!counter_product) {
        msg_error("No product found!\n");
    }
    printf("============END============\n\n");
}
