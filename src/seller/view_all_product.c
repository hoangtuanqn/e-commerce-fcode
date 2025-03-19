#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/global_seller.h"
#include "../../includes/seller/function_seller.h"
#include "../../includes/seller/view_ui.h"
void view_all_product()
{
    printf("\n========== All Product ==========\n");
    read_category_data();
    read_product_data();

    // Display products by category
    int counter_product = 0;
    for (int k = 0; k < counter_category_all; ++k)
    {
        int is_product = 0;
        if (strcmp(category_data[k].username, current_user.username) == 0)
        {
            // Print category header
            printf("\n[Category: \033[36m%s\033[0m]\n", category_data[k].category);

            // Find all products in this category
            for (int i = 0; i < counter_product_all; ++i)
            {
                if (
                    strcmp(product_data[i].username, current_user.username) == 0 &&
                    strcmp(product_data[i].category, category_data[k].category) == 0)
                {
                    ++counter_product;
                    if (product_data[i].status != 3)
                    {
                        is_product = 1;
                        printf("%d. Name Product: \033[32m%s\033[0m\n", counter_product, product_data[i].name_product);
                        printf("\tPrice: \033[32m$%.2f\033[0m\n", product_data[i].price);
                        printf("\tQuantity: \033[32m%d\033[0m\n", product_data[i].quantity);
                        printf("\tDescription: \033[32m%s\033[0m\n", product_data[i].description);
                        printf("\tSold Quantity: \033[32m%d\033[0m\n", product_data[i].sold_quantity);

                        // Improved status display with more informative colors and messages
                        char *status_color;
                        char *status_text;
                        
                        switch(product_data[i].status) {
                            case 0:
                                status_color = "\033[33m"; // Yellow for pending/inactive
                                status_text = "Inactive";
                                break;
                            case 1:
                                status_color = "\033[32m"; // Green for active
                                status_text = "Active";
                                break;
                            case 2:
                                status_color = "\033[31m"; // Red for deleted/hidden
                                status_text = "Hidden";
                                break;
                            default:
                                status_color = "\033[90m"; // Gray for unknown
                                status_text = "Unknown";
                        }
                        
                        printf("\tStatus: %s%s\033[0m", status_color, status_text);
                        
                        // Add stock status indicator
                        if (product_data[i].status == 1) {
                            if (product_data[i].quantity <= 0) {
                                printf(" \033[31m(Out of Stock)\033[0m\n");
                            } else if (product_data[i].quantity < 5) {
                                printf(" \033[33m(Low Stock: %d)\033[0m\n", product_data[i].quantity);
                            } else {
                                printf(" \033[32m(In Stock)\033[0m\n");
                            }
                        } else {
                            printf("\n");
                        }
                        
                        printf("--------------------------------\n\n");
                    }
                }
            }
            if (!is_product)
            {
                msg_error("There are no products in this category!\n\n");
            }
        }
    }

    if (counter_product)
    {
        printf("\nTotal products: %d\n", counter_product);
    }
    printf("\n============END============\n\n");
}
