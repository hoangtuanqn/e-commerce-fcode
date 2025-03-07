#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/global_seller.h"
#include "../../includes/seller/function_seller.h"
#include "../../includes/seller/view_ui.h"
void view_all_category() {
    printf("\n========== All Category ==========\n");
    int cnt = 0;
    for(int i = 0; i < counter_category_all; ++i) {
        if(strcmp(category_data[i].username, current_user.username) == 0) {
            printf("%d. \033[32m%s\033[0m\n", ++cnt, category_data[i].category);
        }
    }
    if(!cnt) {
        msg_error("No category found!\n");
    }
    printf("============END============\n\n");
}
