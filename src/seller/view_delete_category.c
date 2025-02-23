#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/view_ui.h"
#include "../../includes/seller/view_all_category.h"
void view_delete_category() {
    system("cls");
    FILE *file = fopen("data/categories.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }
    getchar();
    char list_id[1000];
    int quantity = view_all_category();
    

    printf("Enter the list of category id to delete: ");
    fgets(list_id, sizeof(list_id), stdin);

    char *token = strtok(list_id, " ");
    int listCategory[1000], i = 0, j = 0, k = 0, is_valid = 1;
    while (token != NULL) {
        int category_id = atoi(token);
        if(category_id > quantity) {
            msg_error("Invalid category id ");
            printf("%d!\n", category_id);
            is_valid = 0;
        }
        listCategory[i++] = category_id;
        token = strtok(NULL, " ");
    }
    if(!is_valid) {
        msg_error("Cannot delete because id is invalid!\n");
        return;
    }

    char user_categories[1000], categories[1000];
    char user_categories_temp[1000], categories_temp[1000];
    quick_sort(listCategory, 0, i - 1);

    while(!feof(file)) {
        fgets(user_categories_temp, sizeof(user_categories_temp), file);
        fgets(categories_temp, sizeof(categories_temp), file);
        if(categories_temp[0] != '\n' && categories_temp[0] != '\0') {
            user_categories[k] = trim_trailing_spaces(user_categories_temp);
            categories[k] = trim_trailing_spaces(categories_temp);
        }
        if(strcmp(user_categories, current_user.username) != 0) {
           
           
        } else {
            ++j;
        }
    }
    fclose(file);
}
   