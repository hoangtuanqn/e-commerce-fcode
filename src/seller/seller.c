#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/view_ui.h"
#include "../../includes/seller/view_add_category.h"
#include "../../includes/seller/view_all_category.h"
#include "../../includes/seller/view_delete_category.h"
#include "../../includes/seller/view_update_category.h"

#include "../../includes/seller/view_all_product.h"
#include "../../includes/seller/view_add_product.h"
#include "../../includes/seller/view_update_product.h"

void seller() {
    int choice;
    int pause = 0; // 1 là pause, 0 là không pause
    view_ui_seller_header();
    do {
        view_ui_seller();
        scanf("%d", &choice);
        switch (choice) {
            case 0:
                is_logged_in = 0;
                return;
            case 1:
                view_all_category();
                break;
            case 2:
                view_add_category();
                break;
            case 3:
                view_update_category();
                break;
            case 4:
                view_delete_category();
                break;
            case 5:
                view_all_product();
                break;
             case 6:
                view_add_product();
                break;
            case 7:
                view_update_product();
                break;
            default:
                msg_error("Invalid choice!\n\n");
        }
    } while (!pause);

}
