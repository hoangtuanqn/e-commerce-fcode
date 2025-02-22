#ifndef LOGIN_H
#define LOGIN_H

typedef struct {
    char username[50];
    char password[50];
    char role[10];
} User;
extern User user;
int loginUser();
#endif

