#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/view_ui.h"

float view_all_cart() {
    float total_amount = 0;
    int product_count = 0;
    
    printf("\n========== Shopping Cart ==========\n");

    // Lấy giỏ hàng của current user từ cart_data
    int cart_index = current_user.id_cart;
    
    // Kiểm tra xem có sản phẩm trong giỏ không
    if (cart_data[cart_index].quantity <= 0) {
        msg_error("Your cart is empty!\n");
        printf("============END============\n\n");
        return 0;
    }

    
    // Duyệt qua các sản phẩm trong giỏ hàng
    for(int j = 0; j < cart_data[cart_index].quantity; j++) {
      
        int product_id = cart_data[cart_index].id_product[j];
        int quantity = cart_data[cart_index].quantity_product[j];
        
        // Kiểm tra product_id hợp lệ
        if (product_id <= 0 || product_id > counter_product_all) {

            continue;
        }
        
        // Lấy thông tin sản phẩm từ product_data
        Product *product = &product_data[product_id - 1];
        float subtotal = product->price * quantity;
        total_amount += subtotal;
        
        printf("%d. Product: \033[32m%s\033[0m\n", ++product_count, product->name_product);
        printf("   Category: \033[32m%s\033[0m\n", product->category);
        printf("   Quantity: \033[32m%d\033[0m\n", quantity);
        printf("   Price per unit: \033[32m$%.2f\033[0m\n", product->price);
        printf("   Subtotal: \033[32m$%.2f\033[0m\n\n", subtotal);
    }
    
    if (product_count > 0) {
        printf("Order total: \033[32m$%.2f\033[0m\n", total_amount);
        printf("Shipping: \033[32m$%.2f\033[0m\n", SHIPPING_FEE);
        printf("Total: \033[31m$%.2f\033[0m\n", total_amount + SHIPPING_FEE);
    }
    
    printf("============END============\n\n");
    return total_amount;
}
