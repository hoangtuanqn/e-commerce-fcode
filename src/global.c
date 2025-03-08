#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../includes/global.h"

int is_logged_in = 0; //= 0 là chưa login, = 1 là đã login
int is_pause_program = 0; //= 0 là không pause, = 1 là pause
int counter_user = 0;
User list_user[MAX_USERS]; // Sử dụng hằng số MAX_USERS
User current_user;


int counter_category_all = 0;
int counter_product_all = 0;
int counter_category_seller = 0;
int counter_product_seller = 0;

int counter_cart_all = 0;
Category category_data[MAX_CATEGORIES];
Product product_data[MAX_CATEGORIES];
Cart cart_data[MAX_CARTS];
