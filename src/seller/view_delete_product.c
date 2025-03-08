#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/global_seller.h"
#include "../../includes/seller/function_seller.h"
#include "../../includes/seller/view_ui.h"
#include "../../includes/seller/view_all_product.h"

void handle_delete_product_(int *list_product_delete, int count) {
    int count_your_product = 0;
    read_product_data();
    for(int i = 0; i < counter_product_all; ++i) {
        if(strcmp(product_data[i].username, current_user.username) == 0) {
            ++count_your_product;
            for(int j = 0; j < count; ++j) {
                if(count_your_product == list_product_delete[j]) {
                    strcpy(product_data[i].name_product, "");
                } else if(count_your_product < list_product_delete[j]) {
                    break;
                }
            }
        }
    }
    write_product_data();
    msg_success("Delete product successfully!\n");
}

void view_delete_product() {
   
    char list_id[1000];
    view_all_product();
    if(!counter_product_seller) {
        msg_error("Currently, there are no products available. Deletion is not possible.\n");
        return;
    }
    
    printf("Please enter the product IDs you wish to delete, separated by spaces: ");
    fgets(list_id, sizeof(list_id), stdin);

    char *token = strtok(list_id, " ");
    int list_product[1000], i = 0, is_valid = 1;
    while (token != NULL) {
        int product_id = atoi(token);
        if(product_id > counter_product_seller) {
            msg_error("Invalid product id ");
            printf("%d!\n", product_id);
            is_valid = 0;
        }
        list_product[i++] = product_id;
        token = strtok(NULL, " ");
    }
    if(!is_valid) {
        msg_error("Cannot delete because id is invalid!\n");
        return;
    }

    quick_sort(list_product, 0, i - 1);
    handle_delete_product_(list_product, i);
}