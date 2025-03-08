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
int is_username_exists(const char *username) {
    for(int i = 0; i < counter_user; ++i) {
        if(strcmp(list_user[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}
int is_email_exists(const char *email) {
    for(int i = 0; i < counter_user; ++i) {
        if(strcmp(list_user[i].email, email) == 0) {
            return 1;
        }
    }
    return 0;
}
int is_phone_exists(const char *phone) {
    for(int i = 0; i < counter_user; ++i) {
        if(strcmp(list_user[i].phone, phone) == 0) {
            return 1;
        }
    }
    return 0;
}
int contains_dangerous_chars(const char *input) {
    const char *dangerous_chars = "'\";--<>|&$(){}[]";
    
    for (int i = 0; input[i] != '\0'; i++) {
        if (strchr(dangerous_chars, input[i]) != NULL) {
            return 1; // Phát hiện ký tự đặc biệt
        }
    }
    return 0; // Không có ký tự đặc biệt
}
int is_validation_number(float value, float min_value, float max_value) {
    if(value < min_value || value > max_value) {
        return 0;
    }
    return 1;
}
char *input_string(char *input) {
    trim_trailing_spaces(input);
    if(strlen(input) == 0) {
        msg_error("Error: Please enter data!\n");
        return NULL;
    }
    if(contains_dangerous_chars(input)) {
        msg_error("Error: The input contains potentially dangerous special characters!\n");
        return NULL;
    }
    return input;
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

// Hàm đọc dữ liệu người dùng từ file
void read_user_data() {
    FILE *file = fopen("data/users.txt", "r");
    if (file == NULL) {
        msg_error("Error opening users file for reading!\n");
        return;
    }
    char line[200];
    
    // Reset list_user array
    // memset(list_user, 0, sizeof(list_user));

    while (fgets(line, sizeof(line), file) && counter_user < MAX_USERS) {
        trim_trailing_spaces(line);
        if (strlen(line) == 0) continue;  // Bỏ qua dòng trống

        strcpy(list_user[counter_user].username, line);

        // Đọc các thông tin khác
        fgets(line, sizeof(line), file);
        trim_trailing_spaces(line);
        strcpy(list_user[counter_user].password, line);

        fgets(line, sizeof(line), file);
        trim_trailing_spaces(line);
        strcpy(list_user[counter_user].email, line);

        fgets(line, sizeof(line), file);
        trim_trailing_spaces(line);
        strcpy(list_user[counter_user].phone, line);

        fgets(line, sizeof(line), file);
        trim_trailing_spaces(line);
        strcpy(list_user[counter_user].full_name, line);

        fgets(line, sizeof(line), file);
        trim_trailing_spaces(line);
        strcpy(list_user[counter_user].address, line);

        fgets(line, sizeof(line), file);
        trim_trailing_spaces(line);
        list_user[counter_user].account_type = atoi(line);

        // Nếu là seller (account_type = 2) thì đọc thêm thông tin shop
        // if (list_user[counter_user].account_type == 2) {
        fgets(line, sizeof(line), file);
        trim_trailing_spaces(line);
        strcpy(list_user[counter_user].shop_name, line);

        fgets(line, sizeof(line), file);
        trim_trailing_spaces(line);
        strcpy(list_user[counter_user].warehouse_address, line);
        // }

        counter_user++;
    }

    fclose(file);
}

int write_user_data(User *user) {
    if (user == NULL) {
        msg_error("Invalid user data!\n");
        return 0;
    }

    FILE *file = fopen("data/users.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    if (fprintf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%d\n%s\n%s\n",
                user->username, user->password, user->email, user->phone,
                user->full_name, user->address, user->account_type,
                user->shop_name, user->warehouse_address) < 0) {
        msg_error("Error writing to file!\n");
        fclose(file);
        return 0;
    }

    fclose(file);
    return 1;
}

// Đọc hết dữ liệu trong file category
void read_category_data() {
    counter_category_all = 0;
    counter_category_seller = 0;
    FILE *file = fopen("data/categories.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }

    Category category_tmp;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        // Skip empty lines
        trim_trailing_spaces(line);
        if(strlen(line) == 0) continue;
        
        // Read username
        strcpy(category_tmp.username, line);

        // Read category
        if(!fgets(line, sizeof(line), file)) break;
        trim_trailing_spaces(line);
        strcpy(category_tmp.category, line);

        // Add to array
        category_data[counter_category_all] = category_tmp;
        
        // Update counters
        if(strcmp(category_tmp.username, current_user.username) == 0) {
            counter_category_seller++;
        }
        counter_category_all++;
    }
    fclose(file);
}

// Đọc hết dữ liệu trong file product
void read_product_data() {
    counter_product_all = 0;
    counter_product_seller = 0;
    FILE *file = fopen("data/products.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }

    Product product_tmp;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        // Skip empty lines
        trim_trailing_spaces(line);
        if(strlen(line) == 0) continue;
        
        // Read username
        strcpy(product_tmp.username, line);

        // Read category
        if(!fgets(line, sizeof(line), file)) break;
        trim_trailing_spaces(line);
        strcpy(product_tmp.category, line);

        // Read product name
        if(!fgets(line, sizeof(line), file)) break;
        trim_trailing_spaces(line);
        strcpy(product_tmp.name_product, line);

        // Read price
        if(!fgets(line, sizeof(line), file)) break;
        trim_trailing_spaces(line);
        product_tmp.price = atof(line);

        // Read quantity 
        if(!fgets(line, sizeof(line), file)) break;
        trim_trailing_spaces(line);
        product_tmp.quantity = atoi(line);

        // Read description
        if(!fgets(line, sizeof(line), file)) break;
        trim_trailing_spaces(line);
        strcpy(product_tmp.description, line);

        // Add to array
        product_data[counter_product_all] = product_tmp;
        
        // Update counters
        if(strcmp(product_tmp.username, current_user.username) == 0) {
            counter_product_seller++;
        }
        counter_product_all++;
    }

    fclose(file);
}