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
void handle_check_out(Order *delivery_info) {
    read_order_data();
    // Get current time
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    if(local == NULL) {
        msg_error("Error getting current time!\n");
        return;
    }

    // Set order time
    sprintf(delivery_info->time_buy, "%02d-%02d-%d %02d:%02d:%02d",
            local->tm_mday, local->tm_mon + 1, local->tm_year + 1900,
            local->tm_hour, local->tm_min, local->tm_sec);

    int cart_index = current_user.id_cart;
    float total = 0;
    int product_count = 0;

    // Process each item in cart
    for(int i = 0; i < cart_data[cart_index].quantity; i++) {
        int product_id = cart_data[cart_index].id_product[i];
        int quantity = cart_data[cart_index].quantity_product[i];
        
        // Validate product ID
        if(product_id <= 0 || product_id > counter_product_all) {
            msg_error("Invalid product ID in cart!\n");
            continue;
        }
        
        Product *product = &product_data[product_id - 1];
        
        // bỏ qua đơn hàng nếu số lượng trong giỏ > số lượng trong kho
        if(quantity > product->quantity) {
            continue;
        }
        // Validate product stock
        if(quantity > product->quantity) {
            msg_error("Product ");
            printf("%s ", product->name_product);
            msg_error("is out of stock!\n");
            continue;
        }

        // Calculate item total and add to order
        float item_total = product->price * quantity;
        delivery_info->id_product[product_count] = product_id;
        delivery_info->quantity_product[product_count] = quantity;
        delivery_info->total_product[product_count] = item_total;
        total += item_total;
        product_count++;

        // Update product quantity
        product->quantity -= quantity;
    }
    delivery_info->shipping_fee = SHIPPING_FEE;
    delivery_info->quantity = product_count;
    delivery_info->total = total + delivery_info->shipping_fee;
}

void view_check_out() {
    float total_payment = view_all_cart();
    int cart_index = current_user.id_cart;

    // Check if cart is empty
    if(total_payment <= 0 || cart_data[cart_index].quantity <= 0) {
        msg_error("There are no orders in the shopping cart!\n");
        return;
    }

    msg_success("\n========== Check Out ==========\n\n");

    // Initialize order info
    Order delivery_info;
    memset(&delivery_info, 0, sizeof(Order));

    // Copy buyer username
    strcpy(delivery_info.buyer, current_user.username);

    // Confirm purchase
    int choice;
    printf("Please confirm you want to purchase the above items?\n");
    printf("1. Yes\n");
    printf("0. No\n");
    printf("Your choice: ");
    if(scanf("%d", &choice) != 1) {
        msg_error("Invalid input!\n");
        while(getchar() != '\n');
        return;
    }
    while(getchar() != '\n');

    if(choice == 0) return;
    if(choice != 1) {
        msg_error("Invalid choice!\n");
        return;
    }

    // Get order notes
    // printf("\nEnter notes for order (If any, press Enter to skip): ");
    // fgets(delivery_info.note, sizeof(delivery_info.note), stdin);
    // trim_trailing_spaces(delivery_info.note);

    // if(strlen(delivery_info.note) == 0) {
    //     strcpy(delivery_info.note, "No notes");
    // }

    printf("\nDelivery Address Options:\n");
    printf("1. Use current address\n");
    printf("2. Use new address\n");
    printf("Your choice: ");
    
    if(scanf("%d", &choice) != 1) {
        msg_error("Invalid input!\n");
        while(getchar() != '\n');
        return;
    }
    while(getchar() != '\n');

    if(choice == 1) {
        // Use current user information
        if(strlen(current_user.email) == 0 || 
           strlen(current_user.phone) == 0 ||
           strlen(current_user.full_name) == 0 ||
           strlen(current_user.address) == 0) {
            msg_error("Current user information is incomplete!\n");
            return;
        }
        strcpy(delivery_info.email, current_user.email);
        strcpy(delivery_info.phone, current_user.phone);
        strcpy(delivery_info.full_name, current_user.full_name);
        strcpy(delivery_info.address, current_user.address);
    } 
    else if(choice == 2) {
        do {
            printf("Email: ");
            fgets(delivery_info.email, sizeof(delivery_info.email), stdin);
            if (!input_string(delivery_info.email) || !is_validation_email(delivery_info.email)) {
                msg_error("Invalid email address\n");
            } else {
                break;
            }
        } while (1);

        do {
            printf("Phone Number: ");
            fgets(delivery_info.phone, sizeof(delivery_info.phone), stdin);
            if (!input_string(delivery_info.phone) || !is_validation_phone(delivery_info.phone)) {
                msg_error("Invalid phone number!\n");
            } else {
                break;
            }
        } while (1);

        do {
            printf("Full Name: ");
            fgets(delivery_info.full_name, sizeof(delivery_info.full_name), stdin);
            if (!input_string(delivery_info.full_name) || strlen(delivery_info.full_name) < 2) {
                msg_error("Name is too short!\n");
            } else {
                break;
            }
        } while (1);

        do {
            printf("Address: ");
            fgets(delivery_info.address, sizeof(delivery_info.address), stdin);
            if (!input_string(delivery_info.address) || strlen(delivery_info.address) < 5) {
                msg_error("Address is too short!\n");
            } else {
                break;
            }
        } while (1);
    } else {
        msg_error("Invalid choice!\n");
        return;
    }

    // Get order notes for each product
    printf("\nProduct Notes (Press Enter to skip):\n");
    for(int i = 0; i < cart_data[cart_index].quantity; i++) {
        int product_id = cart_data[cart_index].id_product[i];
        printf("Note for \033[1;36m%s\033[0m (Quantity: %d): ", 
            product_data[product_id - 1].name_product,
            cart_data[cart_index].quantity_product[i]);
            
        fgets(delivery_info.note_product[i], sizeof(delivery_info.note_product[i]), stdin);
        trim_trailing_spaces(delivery_info.note_product[i]);

        if(strlen(delivery_info.note_product[i]) == 0) {
            strcpy(delivery_info.note_product[i], "No notes");
        }
    }

    generate_order_id(delivery_info.order_id, sizeof(delivery_info.order_id));
    // Process order
    handle_check_out(&delivery_info);

    // Add to order_data array
    order_data[counter_order_all] = delivery_info;
    counter_order_all++;

    // Save changes
    write_order_data();
    write_product_data();
    delete_all_cart();
    
    msg_success("\nOrder placed successfully!\n");
    msg_success("Please wait for the seller to confirm your order.\n");
    printf("\n============END============\n\n");
}
