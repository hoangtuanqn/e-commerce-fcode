#ifndef GLOBAL_SELLER_H
#define GLOBAL_SELLER_H
#define MAX_CATEGORIES 1000
#define MAX_PRODUCTS 1000
typedef struct {
    char username[50];
    char category[100];
} Category;
typedef struct {
    char username[50];
    char category[100];
    char name_product[2000];
    char price[100];
    char quantity[100];
    char description[2000];
} Product;
extern int counter_category_all;
extern int counter_category_seller;

extern int counter_product_all;
extern int counter_product_seller;
extern Category category_data[MAX_CATEGORIES];
extern Product product_data[MAX_PRODUCTS];
#endif
