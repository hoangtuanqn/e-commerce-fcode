#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/global_seller.h"
#include "../../includes/seller/function_seller.h"
#include "../../includes/seller/view_ui.h"
#include "../../includes/seller/view_all_category.h"
#include "../../includes/seller/view_all_product.h"
void handle_update_product(int *list_edit_product, int count) {
    Product temp_product[20];  // Biến tạm để lưu thông tin cập nhật
    int category_id;
    int count_your_product = 0;
    int update_success = 1;  // Flag kiểm tra quá trình update

    // Copy dữ liệu hiện tại vào biến tạm
    memcpy(temp_product, product_data, sizeof(Product) * counter_product_all);

    read_product_data();
    for(int i = 0; i < counter_product_all && update_success; ++i) {
        if(strcmp(product_data[i].username, current_user.username) == 0) {
            ++count_your_product;
            for(int j = 0; j < count; ++j) {
                if(count_your_product == list_edit_product[j]) {
                    printf("\033[1;33m\n=== Updating Product ID %d ===\n\033[0m", count_your_product);
                    printf("(Press Enter to keep current value)\n\n");
                    
                    // Update category
                    view_all_category();
                    do {
                        char category_input[10];
                        printf("Enter new category ID (current: %s): ", temp_product[i].category);
                        fgets(category_input, sizeof(category_input), stdin);
                        trim_trailing_spaces(category_input);
                        
                        if(strlen(category_input) == 0) {
                            break; // Giữ nguyên category cũ
                        }
                        
                        category_id = atoi(category_input);
                        if(!is_validation_number(category_id, 1, counter_category_seller)) {
                            msg_error("Valid category ID required\n");
                        } else {
                            strcpy(temp_product[i].category, check_name_category(category_id));
                            break;
                        }
                    } while (1);

                    // Update product name
                    do {
                        char name[200];
                        printf("Enter new product name (current: %s): ", temp_product[i].name_product);
                        fgets(name, sizeof(name), stdin);
                        trim_trailing_spaces(name);
                        
                        if(strlen(name) == 0) {
                            break; // Giữ nguyên tên cũ
                        }
                        
                        if (!input_string(name)) {
                            msg_error("Invalid product name!\n");
                            update_success = 0;
                            break;
                        }
                        strcpy(temp_product[i].name_product, name);
                    } while (0);

                    if (!update_success) break;

                    // Update price
                    do {
                        char price[20];
                        printf("Enter new price (current: %.2f): ", temp_product[i].price);
                        fgets(price, sizeof(price), stdin);
                        trim_trailing_spaces(price);
                        
                        if(strlen(price) == 0) {
                            break; // Giữ nguyên giá cũ
                        }
                        
                        float price_val = atof(price);
                        if (price_val <= 0 || price_val > 2e19) {
                            msg_error("Invalid input! Price must be greater than 0\n");
                        } else {
                            temp_product[i].price = price_val;
                            break;
                        }
                    } while (1);

                    // Update quantity  
                    do {
                        char quantity[20];
                        printf("Enter new quantity (current: %d): ", temp_product[i].quantity);
                        fgets(quantity, sizeof(quantity), stdin);
                        trim_trailing_spaces(quantity);
                        
                        if(strlen(quantity) == 0) {
                            break; // Giữ nguyên số lượng cũ
                        }
                        
                        int quantity_val = atoi(quantity);
                        if (quantity_val <= 0 || quantity_val > 2e19) {
                            msg_error("Invalid input! Quantity must be greater than 0\n");
                        } else {
                            temp_product[i].quantity = quantity_val;
                            break;
                        }
                    } while (1);

                    // Update description
                    do {
                        char desc[2000];
                        printf("Enter new description (current: %s): ", temp_product[i].description);
                        fgets(desc, sizeof(desc), stdin);
                        trim_trailing_spaces(desc);
                        
                        if(strlen(desc) == 0) {
                            break; // Giữ nguyên mô tả cũ
                        }
                        
                        if (!input_string(desc)) {
                            msg_error("Invalid description!\n");
                            update_success = 0;
                            break;
                        }
                        strcpy(temp_product[i].description, desc);
                    } while (0);

                    if (!update_success) break;

                    printf("\033[1;33m\n=== Product Updated ===\n\033[0m\n\n");

                }
            }
        }
    }

    // Nếu tất cả updates thành công, copy từ temp vào product_data
    if (update_success) {
        memcpy(product_data, temp_product, sizeof(Product) * counter_product_all);
        write_product_data();
        msg_success("Products updated successfully!\n");
    } else {
        msg_error("Update failed! No changes were made.\n");
    }
}
void view_update_product() {
    char list_id[20];
    view_all_product();
    if(!counter_product_seller) {
        msg_error("Currently, there are no products available. Update is not possible.\n");
        return;
    }

    printf("Note: You can update maximum 20 products at once\n");
    printf("Please enter the product IDs you wish to update, separated by spaces: ");
    fgets(list_id, sizeof(list_id), stdin);

    char *token = strtok(list_id, " ");
    int list_delete_product[1000], i = 0, is_valid = 1;
    while (token != NULL && i < 20) { // Thêm
        int product_id = atoi(token);
        if(product_id > counter_product_seller || product_id < 1) {
            msg_error("Invalid product id ");
            printf("%d!\n", product_id);
            is_valid = 0;
        }
        list_delete_product[i++] = product_id;
        token = strtok(NULL, " ");
    }
    if(!is_valid) {
        msg_error("Cannot update because id is invalid!\n");
        return;
    }

    
    quick_sort(list_delete_product, 0, i - 1);
    handle_update_product(list_delete_product, i);
}
