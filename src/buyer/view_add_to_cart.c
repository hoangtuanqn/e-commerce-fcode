#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/view_ui.h"
#include "../../includes/buyer/view_add_to_cart.h"
void handle_add_to_cart()
{
    int id_product;
    if (counter_product_all <= 0)
    {
        msg_error("Currently, there are no products available. Add to cart is not possible.\n");
        return;
    }

    // Get product ID
    do
    {
        printf("Enter the product id to add to cart: ");
        scanf("%d", &id_product);
        if (id_product < 1 || id_product > counter_product_all || product_data[id_product - 1].status != 1)
        {
            msg_error("Invalid product id ");
            printf("%d!\n", id_product);
        }
        else if (product_data[id_product - 1].quantity <= 0)
        {
            printf("ID: %d ", id_product);
            msg_error("no more products in stock \n");
        }
        if (
            id_product > 0 &&
            id_product <= counter_product_all &&
            product_data[id_product - 1].quantity > 0 &&
            product_data[id_product - 1].status == 1)
        {
            break;
        }
    } while (1);

    // Get quantity
    int quantity_in_stock = product_data[id_product - 1].quantity;
    int quantity_product;
    do
    {
        printf("Enter the quantity of the product: ");
        scanf("%d", &quantity_product);
        if (quantity_product <= 0)
        {
            msg_error("Invalid quantity\n");
        }
        else if (quantity_product > quantity_in_stock)
        {
            msg_error("Our stock only has ");
            printf("%d ", quantity_in_stock);
            msg_error("products left!\n");
        }
    } while (quantity_product <= 0 || quantity_product > quantity_in_stock);

    // Find or create cart for current user
    int cart_index = -1;
    for (int i = 0; i < counter_cart_all; i++)
    {
        if (strcmp(cart_data[i].buyer, current_user.username) == 0)
        {
            cart_index = i;
            break;
        }
    }

    // If user doesn't have a cart, create new one
    if (cart_index == -1)
    {
        if (counter_cart_all >= MAX_CARTS)
        {
            msg_error("System cart storage is full!\n");
            return;
        }
        cart_index = counter_cart_all;
        strcpy(cart_data[cart_index].buyer, current_user.username);
        cart_data[cart_index].quantity = 0;
        counter_cart_all++;
        current_user.id_cart = cart_index;
    }

    // Check if product already exists in cart
    int product_exists = 0;
    for (int i = 0; i < cart_data[cart_index].quantity; i++)
    {
        if (cart_data[cart_index].id_product[i] == id_product)
        {
            // Update quantity if doesn't exceed stock
            int new_quantity = cart_data[cart_index].quantity_product[i] + quantity_product;
            if (new_quantity > quantity_in_stock)
            {
                msg_error("Cannot add more. Total quantity would exceed stock!\n");
                return;
            }
            cart_data[cart_index].quantity_product[i] = new_quantity;
            product_exists = 1;
            break;
        }
    }

    // If product doesn't exist in cart, add it
    printf("Truoc khi them %d \n", cart_data[cart_index].quantity);
    if (!product_exists)
    {
        if (cart_data[cart_index].quantity >= MAX_PRODUCTS)
        {
            msg_error("Cart is full! Cannot add more products.\n");
            return;
        }

        // Add new product to cart
        int current_index = cart_data[cart_index].quantity;
        cart_data[cart_index].id_product[current_index] = id_product;
        cart_data[cart_index].quantity_product[current_index] = quantity_product;
        cart_data[cart_index].quantity++;
    }

    printf("Sau khi them %d \n", cart_data[cart_index].id_product[cart_data[cart_index].quantity - 1]);

    // Save cart data to file
    write_cart_data();

    msg_success("Product added to cart successfully!\n");
}
void view_add_to_cart()
{
    handle_add_to_cart();
    do
    {
        view_add_more_to_cart();
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            view_add_to_cart();
        case 2:
            return;
        default:
            msg_error("Choice invalid");
        }
    } while (1);
}