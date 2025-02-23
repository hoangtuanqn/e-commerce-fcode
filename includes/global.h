#ifndef GLOBAL_H
#define GLOBAL_H

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
extern int is_logged_in;
extern User current_user;


#endif

