#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/buyer/view_browse_products.h"
#include "../../includes/buyer/view_add_to_cart.h"

void view_add_to_cart() {
    int id_product;
    view_browse_products();
    if (counter_product_all <= 0) {
        msg_error("Currently, there are no products available. Add to cart is not possible.\n");
        return;
    }

    // Get product ID
    do {
        printf("Enter the product id to add to cart: ");
        scanf("%d", &id_product);
        if(id_product <= 0 || id_product > counter_product_all) {
            msg_error("Invalid product id ");
            printf("%d!\n", id_product);
        }
    } while (id_product <= 0 || id_product > counter_product_all);

    // Get quantity
    int quantity_in_stock = product_data[id_product - 1].quantity;
    int quantity_product;
    do {
        printf("Enter the quantity of the product: ");
        scanf("%d", &quantity_product);
        if(quantity_product <= 0) {
            msg_error("Invalid quantity\n");
        } else if(quantity_product > quantity_in_stock) {
            msg_error("Our stock only has ");
            printf("%d ", quantity_in_stock);
            msg_error("products left!\n");
        }
    } while (quantity_product <= 0 || quantity_product > quantity_in_stock);

    // Get cart index for current user
    int cart_index = current_user.id_cart;

    // Check if product already exists in cart
    int product_exists = 0;
    for(int i = 0; i < cart_data[cart_index].quantity; i++) {
        if(cart_data[cart_index].id_product[i] == id_product) {
            // Update quantity if doesn't exceed stock
            int new_quantity = cart_data[cart_index].quantity_product[i] + quantity_product;
            if(new_quantity > quantity_in_stock) {
                msg_error("Cannot add more. Total quantity would exceed stock!\n");
                return;
            }
            cart_data[cart_index].quantity_product[i] = new_quantity;
            product_exists = 1;
            break;
        }
    }

    // If product doesn't exist in cart, add it
    if(!product_exists) {
        if(cart_data[cart_index].quantity >= MAX_PRODUCTS) {
            msg_error("Cart is full! Cannot add more products.\n");
            return;
        }
        
        // Add new product to cart
        cart_data[cart_index].id_product[cart_data[cart_index].quantity] = id_product;
        cart_data[cart_index].quantity_product[cart_data[cart_index].quantity] = quantity_product;
        cart_data[cart_index].quantity++;
    }

    // Save cart data to file
    write_cart_data();

    msg_success("Product added to cart successfully!\n\n");

}