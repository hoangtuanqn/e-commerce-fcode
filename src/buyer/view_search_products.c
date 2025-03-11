#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/buyer/view_ui.h"

// Hàm tìm kiếm sản phẩm theo từ khóa
void view_search_products() {
    char keyword[2000];
    char temp_name[2000];
    char unique_categories[MAX_CATEGORIES][100];
    int unique_count = 0;

    // Get search keyword
    printf("Enter search keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    trim_trailing_spaces(keyword);

    // Convert keyword to lowercase
    for (int i = 0; keyword[i]; i++) {
        keyword[i] = tolower(keyword[i]);
    }

    printf("\n========== Search Results ==========\n");
    int found = 0;

    // Find unique categories first
    for(int i = 0; i < counter_category_all; i++) {
        int is_unique = 1;
        for(int j = 0; j < unique_count; j++) {
            if(strcmp(category_data[i].category, unique_categories[j]) == 0) {
                is_unique = 0;
                break;
            }
        }
        if(is_unique) {
            strcpy(unique_categories[unique_count], category_data[i].category);
            unique_count++;
        }
    }

    // Display products by category
    for(int cat = 0; cat < unique_count; cat++) {
        int category_has_products = 0;
        
        // Check if category has matching products before printing header
        for(int i = 0; i < counter_product_all; ++i) {
            strcpy(temp_name, product_data[i].name_product);
            for(int j = 0; temp_name[j]; j++) {
                temp_name[j] = tolower(temp_name[j]);
            }

            if(strstr(temp_name, keyword) != NULL && 
               strcmp(product_data[i].category, unique_categories[cat]) == 0 &&
               product_data[i].quantity > 0 &&
               product_data[i].status == 1
            ) {
                if(!category_has_products) {
                    printf("\n\033[1;33m=== Category: %s ===\033[0m\n", unique_categories[cat]);
                    category_has_products = 1;
                }
                display_product(product_data[i], i + 1);
               
                found = 1;
            }
        }
    }

    if (!found) {
        msg_error("No products found with the keyword ");
        printf("\"%s\"\n", keyword);
    }

    printf("\n============END============\n\n");
}
