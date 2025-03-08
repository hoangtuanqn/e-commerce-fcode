// #include <stdio.h>
// #include <math.h>
// #include <string.h>
// #include <stdlib.h>
// #include <time.h>
// #include "../../includes/global.h"
// #include "../../includes/function.h"
// #include "../../includes/buyer/view_ui.h"
// #include "../../includes/buyer/view_all_cart.h"
// #include "../../includes/buyer/view_add_to_cart.h"
// #include "../../includes/buyer/view_check_out.h"
// char *name_seller(int product_id) { 
//     FILE *file = fopen("data/products.txt", "r");   
//     if (file == NULL) {
//         msg_error("Error opening file for reading!\n");
//         return NULL;
//     }
//     int cnt = 0;
//     char line[512];
//     while(fgets(line, sizeof(line), file) != NULL) {
//         ++cnt;
//         trim_trailing_spaces(line);
//         if(cnt == product_id) {
//             return strdup(line);
//         }
//         for(int i = 1; i <= 5; ++i) {
//             fgets(line, sizeof(line), file);
//         }
//     }
//     fclose(file);
//     return NULL;
// }
// Cart check_list_product_in_cart() {
//     Cart cart;
//     FILE *file_cart = fopen("data/carts.txt", "r");
//     if (file_cart == NULL) {
//         msg_error("Error opening carts file for reading!\n"); // Corrected error message
//         return cart;
//     }
//     cart.cnt = 0; // Initialize cart.cnt to avoid undefined behavior
//     char line[512];
//     while(fgets(line, sizeof(line), file_cart) != NULL) {
//         trim_trailing_spaces(line);
//         if(strcmp(line, current_user.username) == 0) {
//             strcpy(cart.username, line); // Use strcpy to copy the username
//             while(fgets(line, sizeof(line), file_cart) != NULL) {
//                 if(line[0] == '\n' || strlen(line) == 0) {
//                     break;
//                 }
//                 trim_trailing_spaces(line);
//                 if (sscanf(line, "%d %d", &cart.product_id[cart.cnt], &cart.quantity[cart.cnt]) == 2) { // Check if sscanf was successful
//                     cart.cnt++; // Increment the count for the current user
//                 }
//             }
//             break;
//         }
//     }
//     fclose(file_cart);
//     return cart;
// }
// void view_check_out() {
//     int choice;
//     float total_payment = view_all_cart();

//     char desc[5000];
//     FILE *file = fopen("data/carts.txt", "r");
//     if (file == NULL) {
//         msg_error("Error opening file for reading!\n");
//         return;
//     }
//     msg_error("\n========== Check Out ==========\n\n");
//     User current_address;
//     if(total_payment <= 0) {
//         msg_error("There are no orders in the shopping cart!\n");
//         fclose(file); // Ensure the file is closed before returning
//         msg_error("\n============END============\n\n");
        
//         return;
//     } else {
//         do {
//             printf("Please confirm you want to purchase the above items? (1. Yes 0. No): ");
//             scanf("%d", &choice);
//             if(choice == 0) {
//                 return;
//             }
//         } while (choice < 0 || choice > 1);

//         getchar();
//         printf("Enter notes for order (If any): ");
//         fgets(desc, sizeof(desc), stdin);
//         trim_trailing_spaces(desc);
//         if(strlen(desc) > 5000) {
//             msg_error("Notes must be less than 5000 characters!\n");
//             return;
//         } else if(strlen(desc) == 0) {
//             strcpy(desc, "No notes");
//         }
//         view_selection_address();
//         int choice;
//         scanf("%d", &choice);
//         if(choice == 1) {
//             // Use current information to receive goods
//             current_address = current_user;
//         } else if(choice == 2) {
//             // Use other information to receive goods
//             User temp_user; // Temporary user to collect new address information
//             int email_exists;
//             do {
//                 printf("Email: ");
//                 scanf("%s", temp_user.email);
//                 email_exists = is_email_exists(temp_user.email);
//                 if (email_exists) {
//                     msg_error("Email already exists! Please enter another email.\n");
//                 }
//             } while (email_exists);
            
//             int phone_exists;
//             do {
//                 printf("Phone Number: ");
//                 scanf("%s", temp_user.phone);
//                 phone_exists = is_phone_exists(temp_user.phone);
//                 if (phone_exists) {
//                     msg_error("Phone already exists! Please enter another phone.\n");
//                 }
//             } while (phone_exists);

//             // Clear the input buffer
//             getchar();

//             printf("Full Name: ");
//             fgets(temp_user.full_name, sizeof(temp_user.full_name), stdin);
//             temp_user.full_name[strcspn(temp_user.full_name, "\n")] = 0; // Remove newline character

//             printf("Address: ");
//             fgets(temp_user.address, sizeof(temp_user.address), stdin);
//             temp_user.address[strcspn(temp_user.address, "\n")] = 0; // Remove newline character

//             // Assign temp_user to current_address for order processing
//             current_address = temp_user;
//         }
        
//         msg_success("Order successfully!\n");
//         msg_success("Please wait for the shipper to confirm the order!\n");
//     }
//     msg_error("\n============END============\n\n");
//     fclose(file);

//     FILE *file_cart = fopen("data/carts.txt", "r");
//     if (file_cart == NULL) {
//         msg_error("Error opening carts file for reading!\n"); // Corrected error message
//         return;
//     }
//     Cart cart = check_list_product_in_cart();

//     FILE *file_order = fopen("data/orders.txt", "a");
//     if (file_order == NULL) {
//         msg_error("Error opening orders file for writing!\n");
//         return;
//     }
//     time_t now;
//     struct tm *local;
//     time(&now);
//     local = localtime(&now);

//     // Lưu từng sản phẩm trong giỏ hàng thành các đơn hàng riêng biệt
//     for(int i = 0; i < cart.cnt; i++) {
//         fprintf(file_order, "%s\n", name_seller(cart.product_id[i]));     // username người bán
//         fprintf(file_order, "%s\n", current_user.username);               // username người mua
//         fprintf(file_order, "%s\n", current_address.email);               // email người mua
//         fprintf(file_order, "%s\n", current_address.phone);               // số điện thoại người mua
//         fprintf(file_order, "%s\n", current_address.full_name);             // địa chỉ người mua
//         fprintf(file_order, "%s\n", current_address.address);             // địa chỉ người mua
//         fprintf(file_order, "%02d-%02d-%d %02d:%02d:%02d\n",             // thời gian mua
//                local->tm_mday, local->tm_mon + 1, local->tm_year + 1900,
//                local->tm_hour, local->tm_min, local->tm_sec);
//         fprintf(file_order, "%s\n", desc);                   
//            // Tính tổng tiền cho sản phẩm này
//         float item_total = cart.product_id[i] * cart.quantity[i];
//         fprintf(file_order, "%.2f\n", item_total);
//         fprintf(file_order, "%d\n", cart.product_id[i]);
//         fprintf(file_order, "%d\n\n", cart.quantity[i]);
        

//     }
    
//     fclose(file_order);
//     delete_cart();
    
//     return;
// }
