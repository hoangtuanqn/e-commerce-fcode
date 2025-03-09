#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/buyer/view_ui.h"
#include "../../includes/buyer/view_browse_products.h"
#include "../../includes/buyer/view_all_cart.h"
#include "../../includes/buyer/view_add_to_cart.h"
#include "../../includes/buyer/view_delete_cart.h"
#include "../../includes/buyer/view_check_out.h"
#include "../../includes/buyer/view_search_products.h"
#include "../../includes/buyer/view_order_history.h"
void buyer() {
    int choice;
    int pause = 0; // 1 là pause, 0 là không pause
    view_ui_buyer_header();
    read_category_data();
    read_product_data();
    read_cart_data();
    read_order_data();
    do {
        view_ui_buyer();
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 0:
                is_logged_in = 0;
                return;
            case 1:
                system("cls");
                view_browse_products();
                break;
            case 2:
                view_search_products();
                break;
            case 3:
                system("cls");
                view_all_cart();
                break;
            case 4:
                system("cls");
                view_add_to_cart();
                break;
            case 5:
                system("cls");
                view_delete_cart();
                break;
            case 6:
                system("cls");
                view_check_out();
                break;
            case 7:
                system("cls");
                view_order_history();
                break;
            default:
                msg_error("Invalid choice!\n\n");
        }
    } while (!pause);

}
