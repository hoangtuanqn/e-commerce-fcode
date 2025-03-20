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
#include "../../includes/buyer/view_change_password.h"

void buyer()
{
    int choice;
    view_ui_buyer_header();
    read_category_data();
    read_product_data();
    read_cart_data();
    read_order_data();
    do
    {
        view_ui_buyer();
        scanf("%d", &choice);
        getchar();
        system("cls");
        switch (choice)
        {
        case 0:
            is_logged_in = 0;
            remove_remember_login();
            return;
        case 1:
            view_browse_products();
            break;
        case 2:
            view_search_products();
            break;
        case 3:
            view_search_products();
            break;
        case 4:
            view_all_cart(1);
            break;
        case 5:
            view_browse_products();
            view_add_to_cart();
            break;
        case 6:
            view_delete_cart();
            break;
        case 7:
            view_check_out();
            break;
        case 8:
            view_order_history();
            break;
        case 9:
            view_change_password();
        default:
            msg_error("Invalid choice!\n\n");
        }
    } while (1);
}
