#include <string.h>
#include <stdio.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/global_seller.h"
#include "../../includes/seller/function_seller.h"
// Đọc hết dữ liệu category lưu vô biến này với 1000 phần tử
void read_category_data() {
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
            strcpy(category_data[counter_category].username, username);
            strcpy(category_data[counter_category].category, category);
            // printf("%s-%d-ok\n", category, strlen(category));
            counter_category++;
        }
        username[0] = '\n';
        category[0] = '\n';
    }
    fclose(file);
}