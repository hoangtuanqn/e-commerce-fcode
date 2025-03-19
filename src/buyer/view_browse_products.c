#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/buyer/view_ui.h"

void display_unique_categories()
{
    char unique_categories[MAX_CATEGORIES][100];
    int unique_count = 0;

    // Tìm các danh mục unique
    for (int i = 0; i < counter_category_all; i++)
    {
        int is_unique = 1;
        for (int j = 0; j < unique_count; j++)
        {
            if (strcmp(category_data[i].category, unique_categories[j]) == 0)
            {
                is_unique = 0;
                break;
            }
        }
        if (is_unique)
        {
            strcpy(unique_categories[unique_count], category_data[i].category);
            unique_count++;
        }
    }

    // Hiển thị menu danh mục
    printf("\n====== Categories ======\n");
    printf("0. View All Products\n");
    for (int i = 0; i < unique_count; i++)
    {
        printf("%d. %s\n", i + 1, unique_categories[i]);
    }
    printf("======================\n");
}

void view_browse_products()
{
    read_category_data();
    read_product_data();

    if (!counter_product_all)
    {
        msg_error("No products found!\n");
        return;
    }

    display_unique_categories();

    int choice;
    printf("Enter category number (0 for all products): ");
    scanf("%d", &choice);
    getchar(); // Clear buffer

    printf("\n========== Products ==========\n\n");

    if (choice == 0)
    {
        // Hiển thị tất cả sản phẩm
        for (int i = 0; i < counter_product_all; ++i)
        {
            if (product_data[i].quantity > 0 && product_data[i].status == 1)
            {
                display_product(product_data[i], i + 1);
            }
        }
    }
    else if (choice > 0 && choice <= counter_category_all)
    {
        // Lấy tên danh mục được chọn
        char selected_category[100];
        int found_category = 0;
        int category_count = 0;

        // Tìm tên danh mục tương ứng với lựa chọn
        for (int i = 0; i < counter_category_all; i++)
        {
            int is_unique = 1;
            for (int j = 0; j < i; j++)
            {
                if (strcmp(category_data[i].category, category_data[j].category) == 0)
                {
                    is_unique = 0;
                    break;
                }
            }
            if (is_unique)
            {
                category_count++;
                if (category_count == choice)
                {
                    strcpy(selected_category, category_data[i].category);
                    found_category = 1;
                    break;
                }
            }
        }

        if (found_category)
        {
            // Hiển thị sản phẩm trong danh mục đã chọn
            int products_found = 0;
            for (int i = 0; i < counter_product_all; ++i)
            {
                if (
                    strcmp(product_data[i].category, selected_category) == 0 &&
                    product_data[i].quantity > 0 && product_data[i].status == 1)
                {
                    display_product(product_data[i], i + 1);
                    products_found++;
                }
            }
            if (!products_found)
            {
                msg_error("No products found in this category!\n");
            }
        }
        else
        {
            msg_error("Invalid category selection!\n");
        }
    }
    else
    {
        msg_error("Invalid choice!\n");
    }

    printf("\n============END============\n\n");
}
