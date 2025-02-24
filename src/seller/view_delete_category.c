#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/view_ui.h"
#include "../../includes/seller/view_all_category.h"
void view_delete_category() {
    FILE *file = fopen("data/categories.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }
    getchar();
    char list_id[1000];
    int quantity = view_all_category();
    if(!quantity) {
        msg_error("Currently, there are no categories available. Deletion is not possible.\n");
        return;
    }
    

    printf("Enter the list of category id to delete: ");
    fgets(list_id, sizeof(list_id), stdin);

    char *token = strtok(list_id, " ");
    int listCategory[1000], i = 0, is_valid = 1;
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

    
    quick_sort(listCategory, 0, i - 1);

    char user_name[1000][1000], category_name[1000][1000]; // lưu trữ dữ liệu chính của tất cả file
    char user_name_temp[1000], category_name_temp[1000]; // lữ trữ 1 dữ liệu người dùng qua mỗi lần lặp
    int cnt = 0, cntList = 0, j = 0;
    while(fgets(user_name_temp, sizeof(user_name_temp), file) != NULL && 
          fgets(category_name_temp, sizeof(category_name_temp), file) != NULL) {
        trim_trailing_spaces(user_name_temp);
        trim_trailing_spaces(category_name_temp);
        if(strcmp(user_name_temp, current_user.username) == 0 && cntList < i) {
            cnt++;
            if(cnt == listCategory[cntList]) {
                ++cntList;
                continue;
            } else {
                strcpy(user_name[j], user_name_temp);
                strcpy(category_name[j], category_name_temp);
            }
        } else {
            strcpy(user_name[j], user_name_temp);
            strcpy(category_name[j], category_name_temp);
        }

        j++;
    }
    msg_success("Delete category successfully!\n");
    fclose(file);
    
    file = fopen("data/categories.txt", "w");
    for(int k = 0; k < j; k++) {
        if(strcmp(user_name[k], "") != 0) {
            fprintf(file, "%s\n%s\n", user_name[k], category_name[k]);
        }
    }
    fclose(file);
}
   