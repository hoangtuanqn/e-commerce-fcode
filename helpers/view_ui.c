#include <stdio.h>
#include <stdlib.h>
#include "../includes/function.h"
#include "../includes/view_ui.h"

void view_ui_start() {
    system("cls");
    printf("\n=== E-commerce System ===\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}


int view_ui_re_login() {
    int choice;
    printf("\n=== Do you want to login again? ===\n");
    printf("1. Yes\n");
    printf("2. No\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    if (choice != 1 && choice != 2) {
        msg_error("Invalid choice!\n");
        return view_ui_re_login();
    }
    return choice;
}
