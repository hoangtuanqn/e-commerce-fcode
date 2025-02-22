#ifndef GLOBAL_H
#define GLOBAL_H
typedef struct {
    char username[50];
    char password[50];
    char email[100];
    char phone[20];
    char fullName[100];
    char address[200];
    int accountType; // 1 = Buyer, 2 = Seller
    char shopName[100];       // Only for sellers
    char warehouseAddress[200]; // Only for sellers
} User;
extern int is_logged_in;
extern User currentUser;
#endif

