#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "../includes/global.h"
void trim_trailing_spaces(char *str) {
    int len = strlen(str);
    while (len > 0 && isspace(str[len - 1])) {
        len--;
    }
    str[len] = '\0';
}
void msg_success(char *message) {
    printf("\033[32m%s\033[0m", message);
}
void msg_error(char *message) {
    printf("\033[31m%s\033[0m", message);
}
void msg_bold(char *message) {
    printf("\033[1m%s\033[0m", message);
}
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  
    int i = (low - 1);  

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}


void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // GỌI HÀM partition()
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}
char *check_name_category(int category_id) {
    FILE *file = fopen("data/categories.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return NULL;
    }
    char username[100], category[100];
    int cnt = 0;
    while (fgets(username, sizeof(username), file) != NULL && fgets(category, sizeof(category), file) != NULL) {
        trim_trailing_spaces(username);
        trim_trailing_spaces(category);
        if (strcmp(username, current_user.username) == 0) {
            ++cnt;
        }
        if (cnt == category_id) {
            fclose(file);
            return strdup(category); // Use strdup to return a dynamically allocated copy of the category
        }
    }
    fclose(file);
    return NULL;
}
int is_email_exists(const char *email) {
    FILE *file = fopen("data/users.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        char existing_email[100];
        if (sscanf(line, "%*s %*s %99s", existing_email) == 1) {
            if (strcmp(existing_email, email) == 0) {
                fclose(file);
                return 1; 
            }
        }
    }

    fclose(file);
    return 0;
}
int is_phone_exists(const char *phone) {
    FILE *file = fopen("data/users.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        char existing_phone[12];
        if (sscanf(line, "%*s %*s %*s %11s", existing_phone) == 1) {
            if (strcmp(existing_phone, phone) == 0) {
                fclose(file);
                return 1; 
            }
        }
    }

    fclose(file);
    return 0;
}
void delete_cart() {
    FILE *file_cart = fopen("data/carts.txt", "r");
    if (file_cart == NULL) {    
        msg_error("Error opening carts file for reading!\n");
        return;
    }

    Cart cart[1000];
    int cnt = 0;
    char line[1000];

    // Đọc toàn bộ nội dung file
    while (fgets(cart[cnt].username, sizeof(cart[cnt].username), file_cart)) {
        trim_trailing_spaces(cart[cnt].username);
        if (strlen(cart[cnt].username) == 0) {
            continue;
        }

        cart[cnt].cnt = 0;

        // Đọc các sản phẩm của user này
        while (fgets(line, sizeof(line), file_cart)) {
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

    // Ghi lại file mà không có thông tin của người dùng hiện tại
    FILE *file_cart_new = fopen("data/carts.txt", "w");
    if (file_cart_new == NULL) {
        msg_error("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < cnt; i++) {
        if (strcmp(cart[i].username, current_user.username) != 0) {
            fprintf(file_cart_new, "%s\n", cart[i].username);
            for (int j = 0; j < cart[i].cnt; j++) {
                fprintf(file_cart_new, "%d %d\n", cart[i].product_id[j], cart[i].quantity[j]);
            }
            fprintf(file_cart_new, "\n");
        }
    }
    fclose(file_cart_new);
}
int load_products(Product products[]) {
    FILE *file = fopen("data/products.txt", "r");
    if (file == NULL) {
        msg_error("Error opening products file for reading!\n");
        return 0;
    }

    int count = 0;
    char username[100], category[100], name[100], price[100], quantity[100], description[100];

    while (fgets(username, sizeof(username), file) != NULL && count < MAX_PRODUCTS) {
        trim_trailing_spaces(username);
        if(strlen(username) == 0) {
            break;
        }

        fgets(category, sizeof(category), file);
        trim_trailing_spaces(category);

        fgets(name, sizeof(name), file);
        trim_trailing_spaces(name);

        fgets(price, sizeof(price), file);
        trim_trailing_spaces(price);

        fgets(quantity, sizeof(quantity), file);
        trim_trailing_spaces(quantity);

        fgets(description, sizeof(description), file);
        trim_trailing_spaces(description);

        products[count].id = count + 1; // ID sản phẩm tính từ 1
        strcpy(products[count].name, name);
        count++;
    }

    fclose(file);
    return count; // Trả về số lượng sản phẩm đã đọc
}
void get_all_user() {
    FILE *file = fopen("data/users.txt", "r");
    if (file == NULL) {
        msg_error("Error opening users file for reading!\n");
        return;
    }

    int count = 0;
    char line[200];
    
    // Reset list_user array
    memset(list_user, 0, sizeof(list_user));

    while (fgets(line, sizeof(line), file) && count < MAX_USERS) {
        trim_trailing_spaces(line);
        if (strlen(line) == 0) continue;  // Bỏ qua dòng trống

        strcpy(list_user[count].username, line);

        // Đọc các thông tin khác
        fgets(line, sizeof(line), file);
        trim_trailing_spaces(line);
        strcpy(list_user[count].password, line);

        fgets(line, sizeof(line), file);
        trim_trailing_spaces(line);
        strcpy(list_user[count].email, line);

        fgets(line, sizeof(line), file);
        trim_trailing_spaces(line);
        strcpy(list_user[count].phone, line);

        fgets(line, sizeof(line), file);
        trim_trailing_spaces(line);
        strcpy(list_user[count].full_name, line);

        fgets(line, sizeof(line), file);
        trim_trailing_spaces(line);
        strcpy(list_user[count].address, line);

        fgets(line, sizeof(line), file);
        trim_trailing_spaces(line);
        list_user[count].account_type = atoi(line);

        // Nếu là seller (account_type = 2) thì đọc thêm thông tin shop
        if (list_user[count].account_type == 2) {
            fgets(line, sizeof(line), file);
            trim_trailing_spaces(line);
            strcpy(list_user[count].shop_name, line);

            fgets(line, sizeof(line), file);
            trim_trailing_spaces(line);
            strcpy(list_user[count].warehouse_address, line);
        }

        count++;
    }

    fclose(file);
}