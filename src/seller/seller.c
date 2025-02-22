#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/view_ui.h"
#include "../../includes/seller/add_category.h"
#include "../../includes/seller/view_all_category.h"
void seller() {
    int choice;
    int pause = 0; // 1 là pause, 0 là không pause
    view_ui_seller_header();
    do {
        view_ui_seller();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                view_all_category();
                break;
            case 2:
                view_add_category();
                return;
            default:
                msg_error("Invalid choice!\n");
                printf("Enter your choice: ");
        }
    } while (!pause);

}
