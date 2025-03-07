#include <string.h>
#include <stdio.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/global_seller.h"
#include "../../includes/seller/function_seller.h"
// Đọc hết dữ liệu trong file category
void read_category_data() {
    counter_category_all = 0;
    counter_category_seller = 0;
    FILE *file = fopen("data/categories.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }
    char username[50], category[100];
    while (fgets(username, sizeof(username), file) != NULL) {
        trim_trailing_spaces(username);
        fgets(category, sizeof(category), file);
        trim_trailing_spaces(category);
        if(username[0] != '\n') {
            strcpy(category_data[counter_category_all].username, username);
            strcpy(category_data[counter_category_all].category, category);

            if(strcmp(category_data[counter_category_all].username, current_user.username)) {
                counter_category_seller++;
            }
            // printf("%s-%d-ok\n", category, strlen(category));
            counter_category_all++;
        }
        username[0] = '\n';
        category[0] = '\n';
    }
    fclose(file);
}

// Đọc hết dữ liệu trong file product
void read_product_data() {
    counter_product_all = 0;
    counter_product_seller = 0;
    FILE *file = fopen("data/products.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }
    Product product_tmp;
    while (fgets(product_tmp.username, sizeof(product_tmp.username), file) != NULL) {
        trim_trailing_spaces(product_tmp.username);

        fgets(product_tmp.category, sizeof(product_tmp.category), file);
        trim_trailing_spaces(product_tmp.category);

        fgets(product_tmp.name_product, sizeof(product_tmp.name_product), file);
        trim_trailing_spaces(product_tmp.name_product);

        fgets(product_tmp.price, sizeof(product_tmp.price), file);
        trim_trailing_spaces(product_tmp.price);

        fgets(product_tmp.quantity, sizeof(product_tmp.quantity), file);
        trim_trailing_spaces(product_tmp.quantity);

        fgets(product_tmp.description, sizeof(product_tmp.description), file);
        trim_trailing_spaces(product_tmp.description);

        if(product_tmp.username[0] != '\n') {
            product_data[counter_product_all] = product_tmp;
            if(strcmp(product_tmp.username, current_user.username) == 0) {
                counter_product_seller++;
            }
            counter_product_all++;
        } 
    }
    fclose(file);
}

void write_product_data() {
    FILE *file = fopen("data/products.txt", "w");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }
    for(int i = 0; i < counter_product_all; ++i) {
        fprintf(file, 
            "%s\n%s\n%s\n%s\n%s\n%s\n", 
            product_data[i].username, 
            product_data[i].category, 
            product_data[i].name_product, 
            product_data[i].price, 
            product_data[i].quantity, 
            product_data[i].description);
    }
    fclose(file);
}