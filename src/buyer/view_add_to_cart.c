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
    int found_user = 0;
    
    // Đọc toàn bộ nội dung file
    char line[1000];
    while(fgets(cart[cnt].username, sizeof(cart[cnt].username), file)) {
        trim_trailing_spaces(cart[cnt].username);
        if(strlen(cart[cnt].username) == 0) {
            continue;
        }
        
        cart[cnt].cnt = 0;
        
        // Đọc các sản phẩm của user này
        while(fgets(line, sizeof(line), file)) {
            trim_trailing_spaces(line);
            if(strlen(line) == 0) break;
            
            char *token = strtok(line, " ");
            if(token != NULL) {
                cart[cnt].product_id[cart[cnt].cnt] = atoi(token);
            }
            token = strtok(NULL, " ");
            if(token != NULL) {
                cart[cnt].quantity[cart[cnt].cnt] = atoi(token);
            }
            cart[cnt].cnt++;
        }

        // Xử lý nếu là user hiện tại
        if(strcmp(cart[cnt].username, current_user.username) == 0) {
            found_user = 1;
            int found_product = 0;
            for(int i = 0; i < cart[cnt].cnt; i++) {
                if(cart[cnt].product_id[i] == id_product) {
                    cart[cnt].quantity[i] += quantity_product;
                    found_product = 1;
                    break;
                }
            }
            if(!found_product) {
                cart[cnt].product_id[cart[cnt].cnt] = id_product;
                cart[cnt].quantity[cart[cnt].cnt] = quantity_product;
                cart[cnt].cnt++;
            }
            
            // Sắp xếp theo id tăng dần
            for(int i = 0; i < cart[cnt].cnt - 1; i++) {
                for(int j = i + 1; j < cart[cnt].cnt; j++) {
                    if(cart[cnt].product_id[i] > cart[cnt].product_id[j]) {
                        int temp_id = cart[cnt].product_id[i];
                        cart[cnt].product_id[i] = cart[cnt].product_id[j];
                        cart[cnt].product_id[j] = temp_id;
                        
                        int temp_quantity = cart[cnt].quantity[i];
                        cart[cnt].quantity[i] = cart[cnt].quantity[j];
                        cart[cnt].quantity[j] = temp_quantity;
                    }
                }
            }
        }
        cnt++;
    }

    // Nếu lần đầu thêm vô giỏ hàng, sẽ bắt đầu thêm mới
    if(!found_user) {
        strcpy(cart[cnt].username, current_user.username);
        cart[cnt].product_id[0] = id_product;
        cart[cnt].quantity[0] = quantity_product;
        cart[cnt].cnt = 1;
        cnt++;
    }

    fclose(file);
    
    // Ghi lại file
    FILE *file_cart = fopen("data/carts.txt", "w");
    if (file_cart == NULL) {
        msg_error("Error opening file for writing!\n");
        return;
    }

    // Ghi lại toàn bộ dữ liệu
    for(int i = 0; i < cnt; i++) {
        fprintf(file_cart, "%s\n", cart[i].username);
        for(int j = 0; j < cart[i].cnt; j++) {
            fprintf(file_cart, "%d %d\n", cart[i].product_id[j], cart[i].quantity[j]);
        }
        fprintf(file_cart, "\n");
    }
    fclose(file_cart);
}