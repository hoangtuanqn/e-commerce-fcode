#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/buyer/view_ui.h"

// Function to search categories by keyword
void view_search_categories()
{
    char keyword[100];
    char temp_category[100];
    int found_categories[MAX_CATEGORIES];
    int found_count = 0;

    // Get search keyword
    printf("Enter category search keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    trim_trailing_spaces(keyword);

    // Convert keyword to lowercase
    for (int i = 0; keyword[i]; i++)
    {
        keyword[i] = tolower(keyword[i]);
    }

    printf("\n========== Category Search Results ==========\n");

    // Find matching categories
    for (int i = 0; i < counter_category_all; i++)
    {
        // Skip duplicates
        int is_duplicate = 0;
        for (int j = 0; j < found_count; j++)
        {
            if (strcmp(category_data[i].category, category_data[found_categories[j]].category) == 0)
            {
                is_duplicate = 1;
                break;
            }
        }

        if (!is_duplicate)
        {
            // Convert category name to lowercase for case-insensitive search
            strcpy(temp_category, category_data[i].category);
            for (int j = 0; temp_category[j]; j++)
            {
                temp_category[j] = tolower(temp_category[j]);
            }

            // Check if category contains the keyword
            // Check if category contains the keyword as a whole word
            // This prevents partial word matches (e.g., "Lap" matching "TV Laptop")
            char *found = strstr(temp_category, keyword);
            int is_match = 0;

            if (found != NULL)
            {
                // Check if the match is at the beginning or has a space before it
                int pos = found - temp_category;
                int is_word_start = (pos == 0 || temp_category[pos - 1] == ' ');

                // Check if the match is at the end or has a space after it
                int keyword_end = pos + strlen(keyword);
                int is_word_end = (temp_category[keyword_end] == '\0' ||
                                   temp_category[keyword_end] == ' ');

                // Only consider it a match if it's a whole word
                if (is_word_start && is_word_end)
                {
                    is_match = 1;
                }
            }

            if (is_match)
            {
                found_categories[found_count++] = i;
            }
        }
    }

    // Display found categories and their products
    if (found_count > 0)
    {
        printf("Found \033[1;32m%d\033[0m categories matching '\033[1;36m%s\033[0m':\n\n", found_count, keyword);

        for (int i = 0; i < found_count; i++)
        {
            int cat_index = found_categories[i];
            int product_count = 0;

            // Count available products in this category
            for (int j = 0; j < counter_product_all; j++)
            {
                if (strcmp(product_data[j].category, category_data[cat_index].category) == 0 &&
                    product_data[j].quantity > 0 &&
                    product_data[j].status == 1)
                {
                    product_count++;
                }
            }

            // Display category with product count
            printf("\033[1;33m%d. %s\033[0m (\033[1;32m%d\033[0m available products)\n",
                   i + 1, category_data[cat_index].category, product_count);
        }

        // Ask user if they want to view products from a specific category
        printf("\nEnter category number to view products (0 to return): ");
        int choice;
        scanf("%d", &choice);
        while (getchar() != '\n')
            ; // Clear input buffer

        if (choice > 0 && choice <= found_count)
        {
            int cat_index = found_categories[choice - 1];
            printf("\n\033[1;36m========== Products in %s ==========\033[0m\n",
                   category_data[cat_index].category);

            int products_found = 0;
            for (int j = 0; j < counter_product_all; j++)
            {
                if (strcmp(product_data[j].category, category_data[cat_index].category) == 0 &&
                    product_data[j].quantity > 0 &&
                    product_data[j].status == 1)
                {
                    display_product(product_data[j], j + 1);
                    products_found = 1;
                }
            }

            if (!products_found)
            {
                msg_error("No available products in this category!\n");
            }
        }
    }
    else
    {
        msg_error("No categories found with the keyword ");
        printf("\"%s\"\n", keyword);
    }

    printf("\n============END============\n\n");
}