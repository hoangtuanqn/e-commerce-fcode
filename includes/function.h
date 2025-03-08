#ifndef FUNCTION_H
#define FUNCTION_H
#include "global.h"
void msg_success(char *message);
void msg_error(char *message);
void msg_bold(char *message);
void trim_trailing_spaces(char *str);
void quick_sort(int *listCategory, int left, int right);
char *check_name_category(int category_id);
int is_username_exists(const char *username);
int is_email_exists(const char *email);
int is_phone_exists(const char *phone);
int contains_dangerous_chars(const char *input); // hàm kiểm tra kí tự độc hại
char *input_string(char *input); // xử lý dữ liệu đầu vào
int is_validation_number(float value, float min_value, float max_value);
void delete_cart();
// int load_products(Product products[]);


void read_user_data(); // Đọc dữ liệu từ file user xong lưu vào biến list_user
int write_user_data(User *user); // Ghi dữ liệu vào file users

void read_category_data();
void read_product_data();

void read_cart_data();
// void write_cart_data();

#endif

