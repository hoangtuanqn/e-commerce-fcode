#ifndef FUNCTION_H
#define FUNCTION_H
#include "global.h"
void msg_success(char *message);
void msg_error(char *message);
void msg_bold(char *message);
void trim_trailing_spaces(char *str);
void quick_sort(int *listCategory, int left, int right);
char *check_name_category(int category_id);
int is_email_exists(const char *email);
int is_phone_exists(const char *phone);
void delete_cart();
int load_products(Product products[]);
void get_all_user(); // get xong lưu vào biến list_user
#endif

