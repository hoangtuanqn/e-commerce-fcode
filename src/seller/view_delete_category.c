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
void handle_delete_category(int *list_category_delete, int count) {
    int count_your_category = 0;
    read_product_data();
    // First pass: check if all categories can be deleted
    int can_delete_all = 1;
    for(int i = 0; i < counter_category_all; ++i) {
        if(strcmp(category_data[i].username, current_user.username) == 0) {
            ++count_your_category;
            for(int j = 0; j < count; ++j) {
                if(count_your_category == list_category_delete[j]) {
                    if(category_data[i].quantity_product > 0) {
                        msg_error("Cannot delete ");
                        printf("%s", category_data[i].category);
                        msg_error(" category because there are products.\n");
                        can_delete_all = 0;
                        break;
                    }
                }
            }
        }
        if(!can_delete_all) break;
    }

    // Second pass: delete categories only if all can be deleted
    if(can_delete_all) {
        count_your_category = 0;
        for(int i = 0; i < counter_category_all; ++i) {
            if(strcmp(category_data[i].username, current_user.username) == 0) {
                ++count_your_category;
                for(int j = 0; j < count; ++j) {
                    if(count_your_category == list_category_delete[j]) {
                        strcpy(category_data[i].category, "");
                    }
                }
            }
        }
        msg_success("Deleted successfully!\n");
    } else {
        msg_error("Operation cancelled: Some categories cannot be deleted.\n");
    }
    write_category_data();
}
void view_delete_category() {
    char list_id[1000];
    view_all_category();
    if(!counter_category_seller) {
        msg_error("Currently, there are no categories available. Deletion is not possible.\n");
        return;
    }
    

    printf("Enter the category IDs to delete, separated by spaces: ");
    fgets(list_id, sizeof(list_id), stdin);

    char *token = strtok(list_id, " ");
    int list_category[1000], i = 0, is_valid = 1;
    while (token != NULL) {
        int category_id = atoi(token);
        if(category_id > counter_category_seller) {
            msg_error("Invalid category id ");
            printf("%d!\n", category_id);
            is_valid = 0;
        }
        list_category[i++] = category_id;
        token = strtok(NULL, " ");
    }
    if(!is_valid) {
        msg_error("Cannot delete because id is invalid!\n");
        return;
    }

    
    quick_sort(list_category, 0, i - 1);
    handle_delete_category(list_category, i);

}
   