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
    do {
        printf("Enter the product id to add to cart: ");
        scanf("%d", &id_product);
        if(id_product <= 0 || id_product > counter_product_all) {
            msg_error("Invalid product id ");
            printf("%d!\n", id_product);
        }
    } while (id_product <= 0 || id_product > counter_product_all);
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

}