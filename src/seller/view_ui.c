#include <stdio.h>
#include <stdlib.h>
#include "../../includes/function.h"
#include "../../includes/seller/view_ui.h"
void view_ui_seller_header() {
    printf("\n========== Welcome to the system! ==========\n");
    printf("We are excited to support you in your selling journey.\n");
    printf("=====================================================\n\n");

    printf("\n========== Dashboard! ==========\n");
    printf("Stock available: [quantity]\n");
    printf("Number of orders sold: [number_of_orders]\n");
    printf("Total sales amount: [total_amount]\n");
    printf("=====================================================\n\n");
}
void view_ui_seller() {
    msg_bold("\n========== Seller Menu ==========\n");
    printf("1. View All Category\n");
    printf("2. Add Category\n");
    printf("3. Update Category\n");
    printf("4. Delete Category\n");
    printf("\n");
    printf("5. View All Product\n");
    printf("6. Add Product\n");
    printf("7. Update Product\n");
    printf("8. Delete Product\n");
    printf("\n");

    printf("9. View All Order\n");
    printf("10. Update Order Status\n");
    printf("\n");
    printf("11. Change password\n");
    printf("\n");
    msg_bold("\n========== TRASH ==========\n");
    printf("12. Category deleted\n");
    printf("13. Product deleted\n");
    printf("\n");

    printf("0. Logout\n");
    printf("Enter your choice: ");
}