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
int list_id_product[100], cnt_list_id_product = 0;
int is_product_in_cart(int product_id) {
    FILE *file = fopen("data/carts.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return 0;
    }
    char line[100];
    int quantity, id;   
    while (fgets(line, sizeof(line), file) != NULL) {
        trim_trailing_spaces(line);
        if (strcmp(line, current_user.username) == 0) {
            // Đã tìm thấy tên người dùng, tiếp tục đọc sản phẩm
            while (fgets(line, sizeof(line), file) != NULL) {
                trim_trailing_spaces(line);
                if (strlen(line) == 0) break; // Dừng khi gặp dòng trống

                sscanf(line, "%d %d", &id, &quantity);
                if (product_id == id) {
                    fclose(file); // Đóng file trước khi trả về
                    return 1; // Sản phẩm đã được tìm thấy
                }
            }
        }
    }
    fclose(file); // Đóng file nếu không tìm thấy
    return 0; // Sản phẩm không tồn tại trong giỏ hàng
}
void handle_delete_product(int product_id) {
    FILE *file_cart = fopen("data/carts.txt", "r");
    if (file_cart == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }

    Cart cart[1000];
    int cnt = 0;
    char line[1000];
    while (fgets(cart[cnt].username, sizeof(cart[cnt].username), file_cart)) {
        trim_trailing_spaces(cart[cnt].username);
        if (strlen(cart[cnt].username) == 0) {
            continue;
        }

        cart[cnt].cnt = 0;

        // Đọc các sản phẩm của user này cho đến khi gặp dòng trống
        while (fgets(line, sizeof(line), file_cart) != NULL) {
            trim_trailing_spaces(line);
            if (strlen(line) == 0) break;

            char *token = strtok(line, " ");
            if (token != NULL) {
                cart[cnt].product_id[cart[cnt].cnt] = atoi(token);
            }
            token = strtok(NULL, " ");
            if (token != NULL) {
                cart[cnt].quantity[cart[cnt].cnt] = atoi(token);
            }
            cart[cnt].cnt++;
        }
        cnt++;
    }
    fclose(file_cart);


    FILE *file_cart_new = fopen("data/carts.txt", "w");
    if (file_cart_new == NULL) {
        msg_error("Error opening file for writing!\n");
        return;
    }
    for(int i = 0; i < cnt; i++) {
        if(cart[i].cnt <= 1 && strcmp(cart[i].username, current_user.username) == 0) {
            continue;
        }
        fprintf(file_cart_new, "%s\n", cart[i].username);
        for(int j = 0; j < cart[i].cnt; j++) {
            if(cart[i].product_id[j] == 0) break;
            if(cart[i].product_id[j] == product_id && strcmp(cart[i].username, current_user.username) == 0) {
                continue;
            }
            fprintf(file_cart_new, "%d %d\n", cart[i].product_id[j], cart[i].quantity[j]);
        }
        fprintf(file_cart_new, "\n");
    }
    fclose(file_cart_new);

}
void delete_specific_product() {
    FILE *file = fopen("data/carts.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }
    getchar();
    char list_id[100];

    printf("Enter the product id to delete: ");
    fgets(list_id, sizeof(list_id), stdin);
    trim_trailing_spaces(list_id);
    char *token = strtok(list_id, " ");
    int is_error = 0;
    cnt_list_id_product = 0; // Reset the count before using it
    while(token != NULL) {
        int product_id = atoi(token);
        if(!is_product_in_cart(product_id)) {
            msg_error("Product ID ");
            printf("%d ", product_id);
            msg_error("is not found in cart!\n");
            is_error = 1;
        } else {
            list_id_product[cnt_list_id_product++] = product_id; // Increment in the same line
        }
        token = strtok(NULL, " ");
    }
    if(is_error) {
        fclose(file);
        return;
    }
    for(int i = 0; i < cnt_list_id_product; i++) {
        handle_delete_product(list_id_product[i]);
    }
    fclose(file);
}
void view_delete_cart() {
    FILE *file = fopen("data/carts.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }
    int quantity_cart = view_all_cart();
    if(quantity_cart == 0) {
        msg_error("No product in cart!\n");
        return;
    } else {
        view_delete_from_cart();
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                delete_cart();
                msg_success("Delete cart successfully!\n");
                break;
            case 2:
                delete_specific_product();
                break;
        }
    }
    msg_error("========================================\n");
    fclose(file);

    return;
}
