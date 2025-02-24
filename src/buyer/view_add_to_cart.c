#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/buyer/view_browse_products.h"
#include "../../includes/buyer/view_add_to_cart.h"

int check_quantity_product(int id_product) {
    FILE *file = fopen("data/products.txt", "r");
    int cnt = 0;
    char user_name_temp[1000], product_name_temp[1000], description_temp[1000], price_temp[1000], quantity_temp[1000], category_id_temp[1000];
    while(fgets(user_name_temp, sizeof(user_name_temp), file) != NULL && 
          fgets(product_name_temp, sizeof(product_name_temp), file) != NULL &&
          fgets(description_temp, sizeof(description_temp), file) != NULL &&
          fgets(price_temp, sizeof(price_temp), file) != NULL &&
          fgets(quantity_temp, sizeof(quantity_temp), file) != NULL &&
          fgets(category_id_temp, sizeof(category_id_temp), file) != NULL) {

        trim_trailing_spaces(quantity_temp);
        if(++cnt == id_product) {
            return atoi(quantity_temp);
        }
    }
    return 0;
    
}
void view_add_to_cart() {
    FILE *file = fopen("data/carts.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }
    getchar();
    int id_product;
    int quantity_product = view_browse_products();
    if (quantity_product <= 0) {
        msg_error("Currently, there are no products available. Add to cart is not possible.\n");
        fclose(file);
        return;
    }

    do {
        printf("Enter the product id to add to cart: ");
        scanf("%d", &id_product);
        if(id_product <= 0 || id_product > quantity_product) {
            msg_error("Invalid product id ");
            printf("%d!\n", id_product);
        }
    } while (id_product <= 0 || id_product > quantity_product);
    int quantity_product_in_stock = check_quantity_product(id_product);
    do {
        printf("Enter the quantity of the product: ");
        scanf("%d", &quantity_product);
        if(quantity_product <= 0 || quantity_product > quantity_product_in_stock) {
            msg_error("Our stock only has ");
            printf("%d ", quantity_product_in_stock);
            msg_error("products left!\n");
        }
    } while (quantity_product <= 0 || quantity_product > quantity_product_in_stock);

    Cart cart[1000];
    int cnt = 0;
    while(!feof(file)) {
        fgets(cart[cnt].username, sizeof(cart[cnt].username), file);
        trim_trailing_spaces(cart[cnt].username);
        if(cart[cnt].username[0] == '\n') {
            break;
        }
        cart[cnt].cnt = 0;
        char info_id_and_quantity[1000];
        int is_suitable = 0;
        while(fgets(info_id_and_quantity, sizeof(info_id_and_quantity), file) != NULL) {
            if(info_id_and_quantity[0] == '\n') {
                break;
            }
            trim_trailing_spaces(info_id_and_quantity);
            char *token = strtok(info_id_and_quantity, " ");
            if(token != NULL) {
                cart[cnt].product_id[cart[cnt].cnt] = atoi(token);
            }
            token = strtok(NULL, " ");
            if(token != NULL) {
                cart[cnt].quantity[cart[cnt].cnt] = atoi(token);
            }
            if(strcmp(cart[cnt].username, current_user.username) == 0) {
                if(id_product == cart[cnt].product_id[cart[cnt].cnt]) {
                    is_suitable = 1;
                    cart[cnt].quantity[cart[cnt].cnt] += quantity_product;
                }
            }
            cart[cnt].cnt++;
        }
        if(!is_suitable) {
            strcpy(cart[cnt].username, current_user.username);
            cart[cnt].product_id[cart[cnt].cnt] = id_product;
            cart[cnt].quantity[cart[cnt].cnt] = quantity_product;
            cart[cnt].cnt++;
        }
        cnt++;
        fgets(cart[cnt].username, sizeof(cart[cnt].username), file);

    }
    fclose(file);
    FILE *file_cart = fopen("data/carts.txt", "w");
    if (file_cart == NULL) {
        msg_error("Error opening file for writing!\n");
        return;
    }
    for(int i = 0; i < cnt; ++i) {
        fprintf(file_cart, "%s\n", cart[i].username);
        for(int j = 0; j < cart[i].cnt; ++j) {
            if(cart[i].product_id[j] != 0) {
                fprintf(file_cart, "%d ", cart[i].product_id[j]);
                fprintf(file_cart, "%d\n", cart[i].quantity[j]);
            }
        }
        fprintf(file_cart, "\n");
    }
    fclose(file_cart);



}