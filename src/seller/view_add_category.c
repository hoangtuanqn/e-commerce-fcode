#include <string.h>
#include <stdio.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/global_seller.h"
#include "../../includes/seller/function_seller.h"
#include "../../includes/seller/view_add_category.h"

int is_exist_category(char *category_name)
{
    read_category_data();

    for (int i = 0; i < counter_category_all; ++i)
    {
        if (strcmp(category_data[i].username, current_user.username) == 0 &&
            strcmp(category_data[i].category, category_name) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int handle_add_category(char *category_name)
{
    if (strlen(category_name) == 0)
    {
        msg_error("Category name cannot be empty!\n\n");
        return 0;
    }
    if (is_exist_category(category_name))
    {
        msg_error("Category already exists!\n\n");
        return 0;
    }
    FILE *file = fopen("data/categories.txt", "a");
    if (file == NULL)
    {
        msg_error("Error opening file for appending!\n");
        return 0;
    }
    fprintf(file, "%s\n%s\n\n", current_user.username, category_name); // Write username and category name
    fclose(file);
    msg_success("Category added successfully!\n\n");
    return 1;
}

void view_add_category()
{
    char category_name[100];
    int is_success = 0;
    do
    {
        printf("\n========== Add Category ==========\n");
        do
        {
            printf("Enter category name: ");
            fgets(category_name, sizeof(category_name), stdin);
        } while (!input_string(category_name));
        // printf("%s--%d\n", category_name, strlen(category_name));
        is_success = handle_add_category(category_name);
    } while (!is_success);
}