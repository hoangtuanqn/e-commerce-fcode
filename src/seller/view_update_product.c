#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/view_ui.h"
#include "../../includes/seller/view_all_category.h"
#include "../../includes/seller/view_all_product.h"

void view_update_product() {
    FILE *file = fopen("data/products.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }
    getchar();
    char list_id[1000];
    int result = view_all_product();
    if(!result) {
        msg_error("Currently, there are no products available. Update is not possible.\n");
        return;
    }
    

    printf("Enter the list of product id to update: ");
    fgets(list_id, sizeof(list_id), stdin);

    char *token = strtok(list_id, " ");
    int listProduct[1000], i = 0, is_valid = 1;
    while (token != NULL) {
        int product_id = atoi(token);
        if(product_id > result || product_id < 1) {
            msg_error("Invalid product id ");
            printf("%d!\n", product_id);
            is_valid = 0;
        }
        listProduct[i++] = product_id;
        token = strtok(NULL, " ");
    }
    if(!is_valid) {
        msg_error("Cannot update because id is invalid!\n");
        return;
    }

    
    quick_sort(listProduct, 0, i - 1);

    char user_name[50][1000], product_name[50][1000], description[50][1000], price[50][1000], category_id[50][1000], quantity[50][1000];
    char user_name_temp[100], product_name_temp[100], description_temp[100], price_temp[100], category_id_temp[100], quantity_temp[100];
    int cnt = 0, cntList = 0, j = 0;
        
    while(fgets(user_name_temp, sizeof(user_name_temp), file) != NULL && 
          fgets(category_id_temp, sizeof(category_id_temp), file) != NULL &&
          fgets(product_name_temp, sizeof(product_name_temp), file) != NULL &&
          fgets(price_temp, sizeof(price_temp), file) != NULL &&
          fgets(quantity_temp, sizeof(quantity_temp), file) != NULL &&
          fgets(description_temp, sizeof(description_temp), file) != NULL) {
        trim_trailing_spaces(user_name_temp);
        trim_trailing_spaces(product_name_temp);
        trim_trailing_spaces(description_temp);
        trim_trailing_spaces(price_temp);
        trim_trailing_spaces(quantity_temp);
        trim_trailing_spaces(category_id_temp);
        if(strcmp(user_name_temp, current_user.username) == 0 && cntList < i) {
            cnt++;
            if(cnt == listProduct[cntList]) {
                strcpy(user_name[j], user_name_temp);
                int quantity_category = view_all_category();
                do {
                    printf("Enter new category ID for ID %d: ", cnt);
                    fgets(category_id_temp, sizeof(category_id_temp), stdin);
                    trim_trailing_spaces(category_id_temp);
                    strcpy(category_id[j], category_id_temp);
                    if(atoi(category_id_temp) < 1 || atoi(category_id_temp) > quantity_category) {
                        msg_error("Category ID is invalid!\n");
                    }
                } while (atoi(category_id_temp) < 1 || atoi(category_id_temp) > quantity_category);

                do {
                    printf("Enter new product name for ID %d: ", cnt);
                    fgets(product_name_temp, sizeof(product_name_temp), stdin);
                    trim_trailing_spaces(product_name_temp);
                    strcpy(product_name[j], product_name_temp);
                    if(strlen(product_name_temp) == 0) {
                        msg_error("Product name cannot be empty!\n");
                    }
                } while (strlen(product_name_temp) == 0);

                do {
                    printf("Enter new price for ID %d: ", cnt);
                    fgets(price_temp, sizeof(price_temp), stdin);
                    trim_trailing_spaces(price_temp);
                    strcpy(price[j], price_temp);
                    if(atof(price_temp) < 0) {
                        msg_error("Price must be greater than 0!\n");
                    }
                } while (atof(price_temp) < 0);

                do {
                    printf("Enter new quantity for ID %d: ", cnt);
                    fgets(quantity_temp, sizeof(quantity_temp), stdin);
                    trim_trailing_spaces(quantity_temp);
                    strcpy(quantity[j], quantity_temp);
                    if(atoi(quantity_temp) < 1) {
                        msg_error("Quantity must be greater than 0!\n");
                    }
                } while (atoi(quantity_temp) < 1);

                do {
                    printf("Enter new description for ID %d: ", cnt);
                    fgets(description_temp, sizeof(description_temp), stdin);
                    trim_trailing_spaces(description_temp);
                    strcpy(description[j], description_temp);
                } while (strlen(description_temp) == 0);

                ++cntList;
            } else {
                strcpy(user_name[j], user_name_temp);
                strcpy(category_id[j], category_id_temp);
                strcpy(product_name[j], product_name_temp);
                strcpy(price[j], price_temp);
                strcpy(quantity[j], quantity_temp);
                strcpy(description[j], description_temp);
            }
        } else {
            strcpy(user_name[j], user_name_temp);
            strcpy(category_id[j], category_id_temp);
            strcpy(product_name[j], product_name_temp);
            strcpy(price[j], price_temp);
            strcpy(quantity[j], quantity_temp);
            strcpy(description[j], description_temp);
        }

        j++;
    }

    msg_success("Update successfully!\n");
    fclose(file);
    file = fopen("data/products.txt", "w");
    for(int k = 0; k < j; k++) {
        if(strlen(user_name[k]) != 0) {
            fprintf(file, "%s\n%s\n%s\n%.2f\n%d\n%s\n", user_name[k], check_name_category(atoi(category_id[k])) ? check_name_category(atoi(category_id[k])) : category_id[k], product_name[k], atof(price[k]), atoi(quantity[k]) , description[k]);
        }
    }
    fclose(file);
   
}
   