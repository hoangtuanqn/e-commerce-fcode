#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/buyer/view_ui.h"
#include "../../includes/buyer/view_all_cart.h"
#include "../../includes/buyer/view_add_to_cart.h"
#include "../../includes/buyer/view_check_out.h"

void handle_delete_product(int product_id) {
    int cart_index = current_user.id_cart;
    
    // Find product in cart
    for(int i = 0; i < cart_data[cart_index].quantity; i++) {
        if(cart_data[cart_index].id_product[i] == product_id) {
            // Shift remaining products left
            for(int j = i; j < cart_data[cart_index].quantity - 1; j++) {
                cart_data[cart_index].id_product[j] = cart_data[cart_index].id_product[j + 1];
                cart_data[cart_index].quantity_product[j] = cart_data[cart_index].quantity_product[j + 1];
            }
            cart_data[cart_index].quantity--;
            break;
        }
    }
}

void delete_specific_product() {
    char list_id[100];
    int list_id_product[100];
    int cnt_list_id_product = 0;

    printf("Enter the product ID(s) to delete, separated by spaces: ");
    fgets(list_id, sizeof(list_id), stdin);
    trim_trailing_spaces(list_id);

    char *token = strtok(list_id, " ");
    int is_error = 0;

    // Collect valid product IDs
    while(token != NULL) {
        int product_id = atoi(token);
        int found = 0;
        
        // Check if product exists in cart
        int cart_index = current_user.id_cart;
        for(int i = 0; i < cart_data[cart_index].quantity; i++) {
            if(cart_data[cart_index].id_product[i] == product_id) {
                found = 1;
                break;
            }
        }

        if(!found) {
            msg_error("Product ID ");
            printf("%d ", product_id);
            msg_error("is not found in cart!\n");
            is_error = 1;
        } else {
            list_id_product[cnt_list_id_product++] = product_id;
        }
        token = strtok(NULL, " ");
    }

    if(is_error) {
        return;
    }

    // Delete products and update cart
    for(int i = 0; i < cnt_list_id_product; i++) {
        handle_delete_product(list_id_product[i]);
    }

    // Save changes to file
    write_cart_data();
    
    msg_success("Products deleted successfully!\n");
}

void view_delete_cart() {
    read_cart_data();
    view_all_cart();
    if(cart_data[current_user.id_cart].quantity == 0) {
        msg_error("No product in cart!\n");
        return;
    }

    view_delete_from_cart();
    int choice;
    scanf("%d", &choice);
    getchar(); // Clear input buffer

    switch (choice) {
        case 1:
            delete_all_cart();
            msg_success("Delete cart successfully!\n");
            break;
        case 2:
            delete_specific_product();
            break;
        default:
            msg_error("Invalid choice!\n");
            break;
    }
    
    msg_error("========================================\n");
}