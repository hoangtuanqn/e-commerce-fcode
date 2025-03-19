#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/view_ui.h"

void handle_update_product_status(int order_id, int *product_indices, int product_count, int new_status)
{
    int updated_count = 0;

    // Validate order ID
    if (order_id <= 0 || order_id > counter_order_all)
    {
        printf("Order ID %d is invalid\n", order_id);
        return;
    }

    int order_idx = order_id - 1;

    // Update status for each product in the list
    for (int i = 0; i < product_count; i++)
    {
        int product_idx = product_indices[i];

        // Validate product index
        if (product_idx < 0 || product_idx >= order_data[order_idx].quantity)
        {
            printf("Product index %d is invalid - skipping\n", product_idx);
            continue;
        }

        // Check if product belongs to current seller
        int product_id = order_data[order_idx].id_product[product_idx];
        if (product_id <= 0 || product_id > counter_product_all ||
            strcmp(product_data[product_id - 1].username, current_user.username) != 0)
        {
            printf("Product index %d is not from your shop - skipping\n", product_idx);
            continue;
        }

        // Update product status
        order_data[order_idx].status_product[product_idx] = new_status;
        updated_count++;
    }

    if (updated_count > 0)
    {
        write_order_data();
        msg_success("Product status updated successfully!\n");
        printf("Updated status for \033[1;32m%d\033[0m product(s)\n", updated_count);
    }
    else
    {
        msg_error("No products were updated\n");
    }
}

void view_update_order_status()
{
    read_order_data();
    read_product_data();

    printf("\n========== Update Order Status ==========\n\n");

    // Display seller's orders first
    int order_count = 0;
    int order_indices[MAX_ORDERS]; // Store actual order indices

    for (int i = 0; i < counter_order_all; i++)
    {
        int has_seller_products = 0;
        float order_total = 0;

        // Check if order has products from current seller
        for (int j = 0; j < order_data[i].quantity; j++)
        {
            int product_id = order_data[i].id_product[j];
            if (product_id > 0 && product_id <= counter_product_all)
            {
                if (strcmp(product_data[product_id - 1].username, current_user.username) == 0)
                {
                    has_seller_products = 1;
                    break;
                }
            }
        }

        if (has_seller_products)
        {
            order_indices[order_count] = i; // Store the actual index
            printf("Order #%d (ID: %d):\n", order_count + 1, i + 1);
            printf("-> Buyer: %s\n", order_data[i].buyer);
            printf("-> Order Date: %s\n", order_data[i].time_buy);
            printf("-> Products from your shop:\n");

            for (int j = 0; j < order_data[i].quantity; j++)
            {
                int product_id = order_data[i].id_product[j];
                if (product_id > 0 && product_id <= counter_product_all)
                {
                    if (strcmp(product_data[product_id - 1].username, current_user.username) == 0)
                    {
                        printf("   [%d] %s (Qty: %d) - Status: %s\n",
                               j,
                               product_data[product_id - 1].name_product,
                               order_data[i].quantity_product[j],
                               order_data[i].status_product[j] == 0 ? "\033[33mPending\033[0m" : order_data[i].status_product[j] == 1 ? "\033[32mCompleted\033[0m"
                                                                                                                                      : "\033[31mFailed\033[0m");
                        order_total += order_data[i].total_product[j];
                    }
                }
            }
            printf("-> Your Total: $%.2f\n", order_total);
            printf("--------------------------------\n");
            order_count++;
        }
    }

    if (order_count == 0)
    {
        msg_error("No orders found!\n");
        return;
    }

    // Get order to update
    int selected_order_num;
    printf("\nPlease enter the order number you wish to update (1-%d): ", order_count);
    if (scanf("%d", &selected_order_num) != 1 || selected_order_num < 1 || selected_order_num > order_count)
    {
        msg_error("Invalid order number!\n");
        while (getchar() != '\n')
            ;
        return;
    }
    while (getchar() != '\n')
        ;

    // Get the actual order index
    int selected_order_idx = order_indices[selected_order_num - 1];

    // Display products for the selected order
    printf("\nProducts in Order #%d (ID: %d):\n", selected_order_num, selected_order_idx + 1);
    int seller_product_count = 0;

    for (int j = 0; j < order_data[selected_order_idx].quantity; j++)
    {
        int product_id = order_data[selected_order_idx].id_product[j];
        if (product_id > 0 && product_id <= counter_product_all)
        {
            if (strcmp(product_data[product_id - 1].username, current_user.username) == 0)
            {
                printf("[%d] %s (Qty: %d) - Status: %s\n",
                       j,
                       product_data[product_id - 1].name_product,
                       order_data[selected_order_idx].quantity_product[j],
                       order_data[selected_order_idx].status_product[j] == 0 ? "\033[33mPending\033[0m" : order_data[selected_order_idx].status_product[j] == 1 ? "\033[32mCompleted\033[0m"
                                                                                                                                                                : "\033[31mFailed\033[0m");
                seller_product_count++;
            }
        }
    }

    if (seller_product_count == 0)
    {
        msg_error("No products from your shop found in this order!\n");
        return;
    }

    // Get products to update
    char list_id[1000];
    printf("\nPlease enter the product indices you wish to update, separated by spaces: ");
    fgets(list_id, sizeof(list_id), stdin);

    char *token = strtok(list_id, " \n");
    int product_indices[1000], i = 0, is_valid = 1;
    while (token != NULL)
    {
        int product_idx = atoi(token);
        if (product_idx < 0 || product_idx >= order_data[selected_order_idx].quantity)
        {
            msg_error("Invalid product index ");
            printf("%d!\n", product_idx);
            is_valid = 0;
        }
        else
        {
            // Verify product belongs to seller
            int product_id = order_data[selected_order_idx].id_product[product_idx];
            if (product_id <= 0 || product_id > counter_product_all ||
                strcmp(product_data[product_id - 1].username, current_user.username) != 0)
            {
                msg_error("Product index ");
                printf("%d is not from your shop!\n", product_idx);
                is_valid = 0;
            }
        }
        product_indices[i++] = product_idx;
        token = strtok(NULL, " \n");
    }

    if (!is_valid || i == 0)
    {
        msg_error("Cannot update because indices are invalid or none were provided!\n");
        return;
    }

    // Get new status
    printf("\nSelect new status:\n");
    printf("0 - Pending\n");
    printf("1 - Completed\n");
    printf("2 - Failed\n");
    printf("Enter status: ");

    int new_status;
    if (scanf("%d", &new_status) != 1)
    {
        msg_error("Invalid input!\n");
        while (getchar() != '\n')
            ;
        return;
    }
    while (getchar() != '\n')
        ;

    if (new_status < 0 || new_status > 2)
    {
        msg_error("Invalid status!\n");
        return;
    }

    handle_update_product_status(selected_order_idx + 1, product_indices, i, new_status);
    printf("\n============END============\n\n");
}