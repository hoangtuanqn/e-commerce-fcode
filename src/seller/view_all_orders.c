#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/view_ui.h"
typedef struct
{
    int id;
    char name[100];
} Product_;
int load_products(Product_ products[])
{
    FILE *file = fopen("data/products.txt", "r");
    if (file == NULL)
    {
        msg_error("Error opening products file for reading!\n");
        return 0;
    }

    int count = 0;
    char username[100], category[100], name[100], price[100], quantity[100], description[100];

    while (fgets(username, sizeof(username), file) != NULL && count < MAX_PRODUCTS)
    {
        trim_trailing_spaces(username);
        if (strlen(username) == 0)
        {
            break;
        }

        fgets(category, sizeof(category), file);
        trim_trailing_spaces(category);

        fgets(name, sizeof(name), file);
        trim_trailing_spaces(name);

        fgets(price, sizeof(price), file);
        trim_trailing_spaces(price);

        fgets(quantity, sizeof(quantity), file);
        trim_trailing_spaces(quantity);

        fgets(description, sizeof(description), file);
        trim_trailing_spaces(description);

        products[count].id = count + 1; // ID sản phẩm tính từ 1
        strcpy(products[count].name, name);
        count++;
    }

    fclose(file);
    return count; // Trả về số lượng sản phẩm đã đọc
}

// Hàm hiển thị danh sách đã bán
void view_all_orders()
{
    // Load latest data
    read_order_data();
    read_product_data();

    printf("\n========== Sold Orders ==========\n");
    int order_count = 0;
    float seller_total = 0;

    // Loop through all orders
    for (int i = 0; i < counter_order_all; i++)
    {
        int has_seller_products = 0;
        float order_total = 0;

        // First check if order has any products from current seller
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

        // If order has products from current seller, display order info
        if (has_seller_products)
        {
            printf("\033[1;34mOrder #%d:\033[0m\n", ++order_count);
            printf("-> Buyer Username: \033[0;36m%s\033[0m\n", order_data[i].buyer);
            printf("-> Email: \033[0;36m%s\033[0m\n", order_data[i].email);
            printf("-> Phone: \033[0;36m%s\033[0m\n", order_data[i].phone);
            printf("-> Full Name: \033[0;36m%s\033[0m\n", order_data[i].full_name);
            printf("-> Address: \033[0;36m%s\033[0m\n", order_data[i].address);
            printf("-> Order ID: \033[1;35m%s\033[0m\n", order_data[i].order_id);
            printf("-> Order Date: \033[0;36m%s\033[0m\n", order_data[i].time_buy);

            // Print only products from current seller
            printf("\033[1;33m-> Products:\033[0m\n");
            for (int j = 0; j < order_data[i].quantity; j++)
            {
                int product_id = order_data[i].id_product[j];
                if (product_id > 0 && product_id <= counter_product_all)
                {
                    // Only show products from current seller
                    if (strcmp(product_data[product_id - 1].username, current_user.username) == 0)
                    {
                        // Simplified status display using ternary operator
                        printf("   - [%s] Product: \033[0;32m%s\033[0m\n",
                               order_data[i].status_product[j] == 0 ? "\033[33mPending\033[0m" : order_data[i].status_product[j] == 1 ? "\033[32mCompleted\033[0m"
                                                                                                                                      : "\033[31mFailed\033[0m",
                               product_data[product_id - 1].name_product);
                        printf("     Quantity: \033[0;32m%d\033[0m\n",
                               order_data[i].quantity_product[j]);
                        printf("     Item Total: \033[0;32m$%.2f\033[0m\n",
                               order_data[i].total_product[j]);
                        printf("     Product Note: \033[0;35m%s\033[0m\n",
                               order_data[i].note_product[j]);
                        printf("   -------------------------\n");

                        // Only add to total if product is completed
                        if (order_data[i].status_product[j] == 1)
                        {
                            order_total += order_data[i].total_product[j];
                        }
                    }
                }
            }

            // Show total for seller's completed products only
            printf("-> Seller's Total (Completed Products): \033[1;31m$%.2f\033[0m\n", order_total);
            printf("--------------------------------\n\n");

            seller_total += order_total;
        }
    }

    if (order_count == 0)
    {
        msg_error("No orders found for the current seller!\n");
    }
    else
    {
        printf("\nTotal Sales (Completed Products): \033[1;32m$%.2f\033[0m\n", seller_total);
    }

    printf("============END============\n\n");
}
