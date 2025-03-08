#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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

    Category category_tmp;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        // Skip empty lines
        trim_trailing_spaces(line);
        if(strlen(line) == 0) continue;
        
        // Read username
        strcpy(category_tmp.username, line);

        // Read category
        if(!fgets(line, sizeof(line), file)) break;
        trim_trailing_spaces(line);
        strcpy(category_tmp.category, line);

        // Add to array
        category_data[counter_category_all] = category_tmp;
        
        // Update counters
        if(strcmp(category_tmp.username, current_user.username) == 0) {
            counter_category_seller++;
        }
        counter_category_all++;
    }
    fclose(file);
}

void write_category_data() {
    FILE *file = fopen("data/categories.txt", "w");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }
    for(int i = 0; i < counter_category_all; ++i) {
        if(strlen(category_data[i].category) > 0) {
            fprintf(file, "%s\n%s\n\n", 
                category_data[i].username, 
                category_data[i].category
            );
        }
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
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        // Skip empty lines
        trim_trailing_spaces(line);
        if(strlen(line) == 0) continue;
        
        // Read username
        strcpy(product_tmp.username, line);

        // Read category
        if(!fgets(line, sizeof(line), file)) break;
        trim_trailing_spaces(line);
        strcpy(product_tmp.category, line);

        // Read product name
        if(!fgets(line, sizeof(line), file)) break;
        trim_trailing_spaces(line);
        strcpy(product_tmp.name_product, line);

        // Read price
        if(!fgets(line, sizeof(line), file)) break;
        trim_trailing_spaces(line);
        product_tmp.price = atof(line);

        // Read quantity 
        if(!fgets(line, sizeof(line), file)) break;
        trim_trailing_spaces(line);
        product_tmp.quantity = atoi(line);

        // Read description
        if(!fgets(line, sizeof(line), file)) break;
        trim_trailing_spaces(line);
        strcpy(product_tmp.description, line);

        // Add to array
        product_data[counter_product_all] = product_tmp;
        
        // Update counters
        if(strcmp(product_tmp.username, current_user.username) == 0) {
            counter_product_seller++;
        }
        counter_product_all++;
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
        if(strlen(product_data[i].name_product) > 0) {
            fprintf(file, "%s\n%s\n%s\n%.2f\n%d\n%s\n\n", 
                product_data[i].username,
                product_data[i].category,
                product_data[i].name_product,
                product_data[i].price,
                product_data[i].quantity,
                product_data[i].description
            );
        }
    }
    fclose(file);
}

int counter_products_in_category(char *name_your_category) {
    int count = 0;
    for(int i = 0; i < counter_product_all; ++i) {
        if(strcmp(product_data[i].category, name_your_category) == 0 && 
            strcmp(product_data[i].username, current_user.username) == 0) {
                ++count;
        }
    }
    return count;
}