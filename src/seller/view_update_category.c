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
    // printf("--%s---%s--\n", user_name_old, category_name);
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
void view_update_category() {
    FILE *file = fopen("data/categories.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }
    char list_id[1000];
    view_all_category();
    if(!counter_category_seller) {
        msg_error("Currently, there are no categories available. Update is not possible.\n");
        return;
    }
    

    printf("Please enter the category IDs you wish to update, separated by spaces: ");
    fgets(list_id, sizeof(list_id), stdin);

    char *token = strtok(list_id, " ");
    int listCategory[1000], i = 0, is_valid = 1;
    while (token != NULL) {
        int category_id = atoi(token);
        if(category_id > counter_category_seller) {
            msg_error("Invalid category id ");
            printf("%d!\n", category_id);
            is_valid = 0;
        }
        listCategory[i++] = category_id;
        token = strtok(NULL, " ");
    }
    if(!is_valid) {
        msg_error("Cannot update because id is invalid!\n");
        return;
    }

    
    quick_sort(listCategory, 0, i - 1);

    char user_name[50][1000], category_name[50][1000];
    char category_name_old[50][1000];
    char temp_user[100], temp_category[100];
    int category_index = 0, list_index = 0, total_entries = 0;

    // Read and process each line pair from the file
    while (fgets(temp_user, sizeof(temp_user), file) && 
           fgets(temp_category, sizeof(temp_category), file)) {
        
        trim_trailing_spaces(temp_user);
        trim_trailing_spaces(temp_category);
        
        // Store original category name for later reference
        strcpy(category_name_old[total_entries], temp_category);
        strcpy(user_name[total_entries], temp_user);
        strcpy(category_name[total_entries], temp_category);

        // Check if this is a category we want to update
        if (strcmp(temp_user, current_user.username) == 0 && list_index < i) {
            category_index++;
            
            if (category_index == listCategory[list_index]) {
                printf("Enter new category name for ID %d: ", category_index);
                fgets(temp_category, sizeof(temp_category), stdin);
                trim_trailing_spaces(temp_category);
                strcpy(category_name[total_entries], temp_category);
                list_index++;
            }
        }

        total_entries++;
    }


    // Tác động đến các sản phẩm có cùng danh mục
    msg_success("Update successfully!\n");
    fclose(file);
    file = fopen("data/categories.txt", "w");
    int affected = 0;
    read_product_data();
    for(int k = 0; k < total_entries; k++) {
        if(strlen(user_name[k]) != 0) {
            affected += update_product_category(category_name_old[k], category_name[k]);
            fprintf(file, "%s\n%s\n", user_name[k], category_name[k]);
        }
    }
    write_product_data();
    printf("Affected %d products. \n\n", affected);
    fclose(file);
   
}
   