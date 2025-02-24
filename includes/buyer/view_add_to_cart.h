#ifndef VIEW_ADD_TO_CART_H
#define VIEW_ADD_TO_CART_H

typedef struct {
    char username[50];
    int product_id[50];
    int quantity[50];
    int cnt;
} Cart; 

void view_add_to_cart();

#endif
