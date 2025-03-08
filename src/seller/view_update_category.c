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
int update_product_category(char *user_name_old, char *category_name) {
    if(strcmp(user_name_old, category_name) == 0) {
        return 0;
    }
    if(strlen(user_name_old) == 0 || strlen(category_name) == 0) {
        return 0;
    }
    int cnt = 0;
    for(int i = 0; i < counter_product_all; ++i) {
        if(strcmp(product_data[i].category, user_name_old) == 0 && strcmp(product_data[i].username, current_user.username) == 0) {
            strcpy(product_data[i].category, category_name);
            ++cnt;
        }
    }
    return cnt;
}
void handle_update_category(int *list_edit_category, int count) {
    char category_new[100];
    int count_your_category = 0, affected = 0;
    for(int i = 0; i < counter_category_all; ++i) {
        if(strcmp(category_data[i].username, current_user.username) == 0) {
            ++count_your_category;
            for(int j = 0; j < count; ++j) {
                if(count_your_category == list_edit_category[j]) {
                    do {
                        printf("Enter new category name for ID %d: ", count_your_category);
                        fgets(category_new, sizeof(category_new), stdin);
                    } while(!input_string(category_new));
                    affected += update_product_category(category_data[i].category, category_new);
                    strcpy(category_data[i].category, category_new);
                } else if(count_your_category < list_edit_category[j]) {
                    break;
                }
            }
        }
    }
    write_category_data();
    write_product_data();
    msg_success("Update successfully!\n");
    printf("Affected %d products. \n\n", affected);
}
void view_update_category() {
    char list_id[1000];
    view_all_category();
    if(!counter_category_seller) {
        msg_error("Currently, there are no categories available. Update is not possible.\n");
        return;
    }

    printf("Please enter the category IDs you wish to update, separated by spaces: ");
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
        msg_error("Cannot update because id is invalid!\n");
        return;
    }

    read_product_data();
    quick_sort(list_category, 0, i - 1);
    handle_update_category(list_category, i);
}
   