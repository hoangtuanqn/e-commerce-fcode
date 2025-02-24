#include <string.h>
#include <stdio.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/view_add_category.h"

int is_exist_category(char *category_name) {
    trim_trailing_spaces(category_name);
    FILE *file = fopen("data/categories.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return 0;
    }     
    char category[100], username[100];
    while (!feof(file)) {
        fgets(username, sizeof(username), file);
        trim_trailing_spaces(username);
        
        fgets(category, sizeof(category), file);
        trim_trailing_spaces(category);

        if (strcmp(category, category_name) == 0 && strcmp(username, current_user.username) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int handle_add_category(char *category_name) {
    if(category_name[0] == '\n') {
        msg_error("Category name cannot be empty!\n\n");
        return 0;
    }
    if (is_exist_category(category_name)) {
        msg_error("Category already exists!\n\n");
        return 0;
    }
    FILE *file = fopen("data/categories.txt", "a");
    if (file == NULL) {
        msg_error("Error opening file for appending!\n");
        return 0;
    }
    fprintf(file, "%s\n%s\n", current_user.username, category_name); // Write username and category name
    fclose(file);
    msg_success("Category added successfully!\n\n");
    return 1;
}

void view_add_category() {
    char category_name[100];
    int is_success = 0;
    do {
        printf("\n========== Add Category ==========\n");
        printf("Enter category name: ");
        getchar();
        fgets(category_name, sizeof(category_name), stdin);
        is_success = handle_add_category(category_name);
    } while (!is_success);
}