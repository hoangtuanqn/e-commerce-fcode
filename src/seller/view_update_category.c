#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/view_ui.h"
#include "../../includes/seller/view_all_category.h"
void update_product_category(char *user_name_old, char *category_name) {
    if(strcmp(user_name_old, category_name) == 0) {
        return;
    }
    if(strlen(user_name_old) == 0 || strlen(category_name) == 0) {
        return;
    }
    FILE *file_product = fopen("data/products.txt", "r+");
    if (file_product == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }
    char username[50][1000], category[50][1000], nameProduct[50][1000], price[50][1000], quantity[50][1000], description[50][1000];
    char username_temp[100], category_temp[100], nameProduct_temp[100], price_temp[100], quantity_temp[100], description_temp[100];
    int i = 0, cnt = 0;
    while(fgets(username_temp, sizeof(username_temp), file_product) != NULL && 
          fgets(category_temp, sizeof(category_temp), file_product) != NULL &&
          fgets(nameProduct_temp, sizeof(nameProduct_temp), file_product) != NULL &&
          fgets(price_temp, sizeof(price_temp), file_product) != NULL &&
          fgets(quantity_temp, sizeof(quantity_temp), file_product) != NULL &&
          fgets(description_temp, sizeof(description_temp), file_product) != NULL) {
        if(username_temp[0] == '\n') {
            break;
        }
        trim_trailing_spaces(username_temp);
        trim_trailing_spaces(category_temp);
        trim_trailing_spaces(nameProduct_temp);
        trim_trailing_spaces(price_temp);
        trim_trailing_spaces(quantity_temp);
        trim_trailing_spaces(description_temp);

        strcpy(username[i], username_temp);
        strcpy(category[i], category_temp);
        strcpy(nameProduct[i], nameProduct_temp);
        strcpy(price[i], price_temp);
        strcpy(quantity[i], quantity_temp);
        strcpy(description[i], description_temp);

        if(strcmp(username_temp, current_user.username) == 0 && strcmp(category_temp, user_name_old) == 0) {
            ++cnt;
            strcpy(category[i], category_name);
        }

        i++;
    }
    fclose(file_product);
    FILE *file_product2 = fopen("data/products.txt", "w");
    if (file_product2 == NULL) {
        msg_error("Error opening file for writing!\n");
        return;
    }

    for (int j = 0; j < i; j++) {
        fprintf(file_product2, "%s\n%s\n%s\n%s\n%s\n%s\n", username[j], category[j], nameProduct[j], price[j], quantity[j], description[j]);
    }
    printf("Affected %d products. \n\n", cnt);
    fclose(file_product2);
}
void view_update_category() {
    FILE *file = fopen("data/categories.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }
    getchar();
    char list_id[1000];
    int quantity = view_all_category();
    if(!quantity) {
        msg_error("Currently, there are no categories available. Update is not possible.\n");
        return;
    }
    

    printf("Enter the list of category id to update: ");
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
        msg_error("Cannot update because id is invalid!\n");
        return;
    }

    
    quick_sort(listCategory, 0, i - 1);

    char user_name[50][1000], category_name[50][1000]; // lưu trữ dữ liệu chính của tất cả file
    char category_name_old[50][1000]; // lưu trữ dữ liệu chính của tất cả file
    char user_name_temp[100], category_name_temp[100]; // lữ trữ 1 dữ liệu người dùng qua mỗi lần lặp
    int cnt = 0, cntList = 0, j = 0;
    while(fgets(user_name_temp, sizeof(user_name_temp), file) != NULL && 
          fgets(category_name_temp, sizeof(category_name_temp), file) != NULL) {
        trim_trailing_spaces(user_name_temp);
        trim_trailing_spaces(category_name_temp);
        strcpy(category_name_old[j], category_name_temp);
        if(strcmp(user_name_temp, current_user.username) == 0 && cntList < i) {
            cnt++;
            if(cnt == listCategory[cntList]) {
                strcpy(user_name[j], user_name_temp);
                printf("Enter new category name for ID %d: ", cnt);
                fgets(category_name_temp, sizeof(category_name_temp), stdin);
                trim_trailing_spaces(category_name_temp);
                strcpy(category_name[j], category_name_temp);

                ++cntList;
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


    // Tác động đến các sản phẩm có cùng danh mục
    msg_success("Update successfully!\n");
    fclose(file);
    file = fopen("data/categories.txt", "w");
    for(int k = 0; k < j; k++) {
        if(strlen(user_name[k]) != 0) {
            update_product_category(category_name_old[k],category_name[k]);
            fprintf(file, "%s\n%s\n", user_name[k], category_name[k]);
        }
    }
    fclose(file);
   
}
   