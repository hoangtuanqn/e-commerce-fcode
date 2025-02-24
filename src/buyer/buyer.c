#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/buyer/view_ui.h"
#include "../../includes/buyer/view_browse_products.h"
#include "../../includes/buyer/view_add_to_cart.h"

void buyer() {
    int choice;
    int pause = 0; // 1 là pause, 0 là không pause
    view_ui_buyer_header();
    do {
        view_ui_buyer();
        scanf("%d", &choice);
        switch (choice) {
            case 0:
                is_logged_in = 0;
                return;
            case 1:
                system("cls");
                view_browse_products();
                break;
            case 2:
                // view_search_products();
                break;
            case 3:
                view_add_to_cart();
                break;
            case 4:
                break;
            default:
                msg_error("Invalid choice!\n\n");
        }
    } while (!pause);

}
