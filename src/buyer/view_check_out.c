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
Cart check_list_product_in_cart() {
    Cart cart;
    FILE *file_cart = fopen("data/carts.txt", "r");
    if (file_cart == NULL) {
        msg_error("Error opening carts file for reading!\n"); // Corrected error message
        return cart;
    }
    cart.cnt = 0; // Initialize cart.cnt to avoid undefined behavior
    char line[512];
    while(fgets(line, sizeof(line), file_cart) != NULL) {
        trim_trailing_spaces(line);
        if(strcmp(line, current_user.username) == 0) {
            strcpy(cart.username, line); // Use strcpy to copy the username
            while(fgets(line, sizeof(line), file_cart) != NULL) {
                if(line[0] == '\n' || strlen(line) == 0) {
                    break;
                }
                trim_trailing_spaces(line);
                if (sscanf(line, "%d %d", &cart.product_id[cart.cnt], &cart.quantity[cart.cnt]) == 2) { // Check if sscanf was successful
                    cart.cnt++; // Increment the count for the current user
                }
            }
            break;
        }
    }
    fclose(file_cart);
    return cart;
}
void view_check_out() {
    char desc[5000];
    FILE *file = fopen("data/carts.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }
    float total_payment = view_all_cart();
    msg_error("\n========== Check Out ==========\n\n");
    User current_address;
    if(total_payment <= 0) {
        msg_error("There are no orders in the shopping cart!\n");
        fclose(file); // Ensure the file is closed before returning
        return;
    } else {
        getchar();
        printf("Enter notes for order (If any): ");
        fgets(desc, sizeof(desc), stdin);
        trim_trailing_spaces(desc);
        if(strlen(desc) > 5000) {
            msg_error("Notes must be less than 5000 characters!\n");
            return;
        } else if(strlen(desc) == 0) {
            strcpy(desc, "No notes");
        }
        view_selection_address();
        int choice;
        scanf("%d", &choice);
        if(choice == 1) {
            // Use current information to receive goods
            current_address = current_user;
        } else if(choice == 2) {
            // Use other information to receive goods
            User temp_user; // Temporary user to collect new address information
            int email_exists;
            do {
                printf("Email: ");
                scanf("%s", temp_user.email);
                email_exists = is_email_exists(temp_user.email);
                if (email_exists) {
                    msg_error("Email already exists! Please enter another email.\n");
                }
            } while (email_exists);
            
            int phone_exists;
            do {
                printf("Phone Number: ");
                scanf("%s", temp_user.phone);
                phone_exists = is_phone_exists(temp_user.phone);
                if (phone_exists) {
                    msg_error("Phone already exists! Please enter another phone.\n");
                }
            } while (phone_exists);

            // Clear the input buffer
            getchar();

            printf("Full Name: ");
            fgets(temp_user.full_name, sizeof(temp_user.full_name), stdin);
            temp_user.full_name[strcspn(temp_user.full_name, "\n")] = 0; // Remove newline character

            printf("Address: ");
            fgets(temp_user.address, sizeof(temp_user.address), stdin);
            temp_user.address[strcspn(temp_user.address, "\n")] = 0; // Remove newline character

            // Assign temp_user to current_address for order processing
            current_address = temp_user;
        }
        
        msg_success("Order successfully!\n");
        msg_success("Please wait for the shipper to confirm the order!\n");
    }
    msg_error("\n============END============\n\n");
    fclose(file);

    FILE *file_cart = fopen("data/carts.txt", "r");
    if (file_cart == NULL) {
        msg_error("Error opening carts file for reading!\n"); // Corrected error message
        return;
    }
    Cart cart = check_list_product_in_cart();

    FILE *file_order = fopen("data/orders.txt", "a");
    if (file_order == NULL) {
        msg_error("Error opening orders file for writing!\n");
        return;
    }
    time_t now;
    struct tm *local;
    time(&now);
    local = localtime(&now); // Convert to local time
    fprintf(file_order, "%s\n", current_user.username); // Use current_address instead of current_user
    fprintf(file_order, "%s\n", current_address.email);
    fprintf(file_order, "%s\n", current_address.phone);
    fprintf(file_order, "%s\n", current_address.full_name);
    fprintf(file_order, "%s\n", current_address.address);
    fprintf(file_order, "%.2f\n", total_payment); // Assuming total_payment is calculated earlier
    fprintf(file_order, "%02d-%02d-%d %02d:%02d:%02d\n",
           local->tm_mday, local->tm_mon + 1, local->tm_year + 1900,
           local->tm_hour, local->tm_min, local->tm_sec);
    for(int i = 0; i < cart.cnt; i++) {
         fprintf(file_order, "%d %d\n", cart.product_id[i], cart.quantity[i]);
    }
    fprintf(file_order, "%s\n\n", desc);
    fclose(file_order);
    delete_cart();
    
    return;
}
