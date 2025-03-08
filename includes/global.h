#ifndef GLOBAL_H
#define GLOBAL_H
#define MAX_USERS 500
#define MAX_CATEGORIES 1000
#define MAX_PRODUCTS 1000
typedef struct {
    char username[50];
    char password[50];
    char email[100];
    char phone[20];
    char full_name[100];
    char address[200];
    int account_type; // 1 = Buyer, 2 = Seller
    char shop_name[100];       // Only for sellers
    char warehouse_address[200]; // Only for sellers
} User;

typedef struct {
    char username[50];
    int product_id[100];
    int quantity[100];
    int cnt;
} Cart;
typedef struct {
    char username[50];
    char category[100];
} Category;
typedef struct {
    char username[50];
    char category[100];
    char name_product[2000];
    float price;
    int quantity;
    char description[2000];
} Product;


extern int is_logged_in;
extern int is_pause_program;
extern User current_user;
extern int counter_user; // lưu số lượng thành viên
extern User list_user[MAX_USERS]; // Sử dụng hằng số MAX_USERS

extern int counter_category_all;
extern int counter_product_all;
extern Category category_data[MAX_CATEGORIES];
extern Product product_data[MAX_PRODUCTS];
extern int counter_category_seller;
extern int counter_product_seller;

#endif