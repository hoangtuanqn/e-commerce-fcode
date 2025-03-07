#include <string.h>
#include <stdio.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/global_seller.h"
#include "../../includes/seller/function_seller.h"
// Đọc hết dữ liệu category lưu vô biến này với 1000 phần tử
void read_category_data() {
    counter_category_all = 0;
    counter_category_seller = 0;
    FILE *file = fopen("data/categories.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }
    char username[50], category[100];
    while (fgets(username, sizeof(username), file) != NULL) {
        trim_trailing_spaces(username);
        fgets(category, sizeof(category), file);
        trim_trailing_spaces(category);
        if(username[0] != '\n') {
            strcpy(category_data[counter_category_all].username, username);
            strcpy(category_data[counter_category_all].category, category);

            if(strcmp(category_data[counter_category_all].username, current_user.username)) {
                counter_category_seller++;
            }
            // printf("%s-%d-ok\n", category, strlen(category));
            counter_category_all++;
        }
        username[0] = '\n';
        category[0] = '\n';
    }
    fclose(file);
}