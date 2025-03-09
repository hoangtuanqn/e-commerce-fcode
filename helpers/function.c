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
int is_validation_email(char *email) {
    if (!email || strlen(email) == 0) {
        return 0;
    }

    // Check for @ symbol
    char *at = strchr(email, '@');
    if (!at) {
        return 0;
    }

    // Check for . after @
    char *dot = strchr(at, '.');
    if (!dot || dot == at + 1) {
        return 0;
    }

    // Check minimum length requirements
    if (at - email < 1 || // At least 1 char before @
        strlen(dot) < 3 || // At least 2 chars after dot
        dot - at < 2) {    // At least 1 char between @ and dot
        return 0;
    }

    // Check for invalid characters
    for (int i = 0; email[i]; i++) {
        if (!isalnum(email[i]) && email[i] != '@' && email[i] != '.' && 
            email[i] != '_' && email[i] != '-') {
            return 0;
        }
    }

    return 1;
}
int is_validation_phone(char *phone) {
    if (!phone || strlen(phone) == 0) {
        return 0;
    }

    // Check length (assuming valid phone numbers are 10-11 digits)
    int len = strlen(phone);
    if (len < 10 || len > 11) {
        return 0;
    }

    // First digit should be 0
    if (phone[0] != '0') {
        return 0;
    }

    // Check if all characters are digits
    for (int i = 0; phone[i]; i++) {
        if (!isdigit(phone[i])) {
            return 0;
        }
    }

    return 1;
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

void read_cart_data() {
    counter_cart_all = 0;
    FILE *file = fopen("data/carts.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }
    char line[1000];

    while (fgets(line, sizeof(line), file)) {
        trim_trailing_spaces(line);
        if(strlen(line) == 0) {
            continue; // Skip empty lines between users
        }
        
        // Đọc username buyer
        strcpy(cart_data[counter_cart_all].buyer, line);
        cart_data[counter_cart_all].quantity = 0; // Reset counter for products

        // Check if this is current user's cart
        if(strcmp(line, current_user.username) == 0) {
            current_user.id_cart = counter_cart_all;
        }

        // Read products until empty line or EOF
        while (fgets(line, sizeof(line), file)) {
            trim_trailing_spaces(line);
            if(strlen(line) == 0) break; // Empty line means end of this user's cart

            // Read product ID and quantity
            int product_id, quantity;
            if(sscanf(line, "%d %d", &product_id, &quantity) == 2) {
                // Save product ID and its quantity
                cart_data[counter_cart_all].id_product[cart_data[counter_cart_all].quantity] = product_id;
                cart_data[counter_cart_all].quantity_product[cart_data[counter_cart_all].quantity] = quantity;
                cart_data[counter_cart_all].quantity++; // Increment number of products in cart
            }
        }

        counter_cart_all++; // Move to next user
    }

    fclose(file);
}
void write_cart_data() {
    read_product_data();
    FILE *file = fopen("data/carts.txt", "w");
    if (file == NULL) {
        msg_error("Error opening cart file for writing!\n");
        return;
    }

    // Write each cart to file
    for(int i = 0; i < counter_cart_all; i++) {
        // Skip empty carts
        if(strlen(cart_data[i].buyer) == 0) {
            continue;
        }

        int cnt = 0;
        // check trước khi thêm vào
        for(int j = 0; j < cart_data[i].quantity; j++) {
            int id_product = cart_data[i].id_product[j];
            if(cart_data[i].quantity > product_data[id_product].quantity) {
                ++cnt;
            }
        
        }
        if(cnt == cart_data[i].quantity) continue;


        // Write buyer username
        fprintf(file, "%s\n", cart_data[i].buyer);

        // Write product IDs and quantities
        for(int j = 0; j < cart_data[i].quantity; j++) {
            int id_product = cart_data[i].id_product[j];
            if(cart_data[i].quantity > product_data[id_product].quantity) {
                continue;
            }
            fprintf(file, "%d %d\n", 
                cart_data[i].id_product[j],
                cart_data[i].quantity_product[j]);
        }

        // Add empty line between carts unless it's the last cart
        if(i < counter_cart_all - 1) {
            fprintf(file, "\n");
        }
    }

    fclose(file);
}

void delete_all_cart() {
    int cart_index = current_user.id_cart;
    strcpy(cart_data[cart_index].buyer, "");
    write_cart_data();
}

void read_order_data() {
    FILE *file = fopen("data/orders.txt", "r");
    if (file == NULL) {
        msg_error("Error opening orders file for reading!\n");
        return;
    }

    counter_order_all = 0;
    char line[2000];

    while (fgets(line, sizeof(line), file)) {
        trim_trailing_spaces(line);
        if(strlen(line) == 0) {
            continue; // Skip empty lines between orders
        }

        // Read buyer username
        strcpy(order_data[counter_order_all].buyer, line);

        // Read email
        if(!fgets(line, sizeof(line), file)) break;
        trim_trailing_spaces(line);
        strcpy(order_data[counter_order_all].email, line);

        // Read phone
        if(!fgets(line, sizeof(line), file)) break;
        trim_trailing_spaces(line);
        strcpy(order_data[counter_order_all].phone, line);

        // Read full name
        if(!fgets(line, sizeof(line), file)) break;
        trim_trailing_spaces(line);
        strcpy(order_data[counter_order_all].full_name, line);

        // Read address
        if(!fgets(line, sizeof(line), file)) break;
        trim_trailing_spaces(line);
        strcpy(order_data[counter_order_all].address, line);

        // Read time
        if(!fgets(line, sizeof(line), file)) break;
        trim_trailing_spaces(line);
        strcpy(order_data[counter_order_all].time_buy, line);

        // Read note
        if(!fgets(line, sizeof(line), file)) break;
        trim_trailing_spaces(line);
        strcpy(order_data[counter_order_all].note, line);

        // Read shipping fee
        if(!fgets(line, sizeof(line), file)) break;
        order_data[counter_order_all].shipping_fee = atof(line);

        // Read products and their details
        int product_count = 0;
        while (fgets(line, sizeof(line), file)) {
            trim_trailing_spaces(line);
            if(strlen(line) == 0) break; // Empty line indicates end of order

            // Try to parse as product line first
            int id, quantity;
            float price;
            if(sscanf(line, "%d %d %f", &id, &quantity, &price) == 3) {
                order_data[counter_order_all].id_product[product_count] = id;
                order_data[counter_order_all].quantity_product[product_count] = quantity;
                order_data[counter_order_all].total_product[product_count] = price;
                product_count++;
            } else {
                // Not a product line, must be the total
                order_data[counter_order_all].total = atof(line);
                break;
            }
        }
        order_data[counter_order_all].quantity = product_count;


        counter_order_all++;
        if(counter_order_all >= MAX_ORDERS) {
            msg_error("Maximum orders limit reached!\n");
            break;
        }
    }

    fclose(file);
}

void write_order_data() {
    FILE *file = fopen("data/orders.txt", "w");
    if (file == NULL) {
        msg_error("Error opening orders file for writing!\n");
        return;
    }

    for(int i = 0; i < counter_order_all; i++) {
        // Skip empty orders
        if(strlen(order_data[i].buyer) == 0) {
            continue;
        }

        // Write order header information
        fprintf(file, "%s\n", order_data[i].buyer);
        fprintf(file, "%s\n", order_data[i].email);
        fprintf(file, "%s\n", order_data[i].phone);
        fprintf(file, "%s\n", order_data[i].full_name);
        fprintf(file, "%s\n", order_data[i].address);
        fprintf(file, "%s\n", order_data[i].time_buy);
        fprintf(file, "%s\n", order_data[i].note);
        fprintf(file, "%.2f\n", order_data[i].shipping_fee);

        // Write product details
        for(int j = 0; j < order_data[i].quantity; j++) {
            fprintf(file, "%d %d %.2f\n", 
                order_data[i].id_product[j],
                order_data[i].quantity_product[j],
                order_data[i].total_product[j]);
        }

        // Write total
        fprintf(file, "%.2f", order_data[i].total);

        // Add separator between orders
        if(i < counter_order_all - 1) {
            fprintf(file, "\n\n");
        }
    }

    fclose(file);
}

void write_product_data() {
    FILE *file = fopen("data/products.txt", "w");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }
    for(int i = 0; i < counter_product_all; ++i) {
        if(strlen(product_data[i].name_product) > 0) {
            fprintf(file, "%s\n%s\n%s\n%.2f\n%d\n%s\n\n", 
                product_data[i].username,
                product_data[i].category,
                product_data[i].name_product,
                product_data[i].price,
                product_data[i].quantity,
                product_data[i].description
            );
        }
    }
    fclose(file);
}