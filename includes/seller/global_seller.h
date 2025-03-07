#ifndef GLOBAL_SELLER_H
#define GLOBAL_SELLER_H
#define MAX_CATEGORIES 1000
typedef struct {
    char username[50];
    char category[100];
} Category;
extern int counter_category;
extern Category category_data[MAX_CATEGORIES];
#endif
