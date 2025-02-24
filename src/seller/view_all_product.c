#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/view_ui.h"
int view_all_product() {
    FILE *file = fopen("data/products.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return 0;
    }
    char username[100], category[100], nameProduct[100], price[100], quantity[100], description[100];
    printf("\n========== All Product ==========\n");
    int i = 0;
    while (!feof(file)) {
        fgets(username, sizeof(username), file);
        trim_trailing_spaces(username);

        fgets(category, sizeof(category), file);
        trim_trailing_spaces(category);

        fgets(nameProduct, sizeof(nameProduct), file);
        trim_trailing_spaces(nameProduct);

        fgets(price, sizeof(price), file);
        trim_trailing_spaces(price);

        fgets(quantity, sizeof(quantity), file);
        trim_trailing_spaces(quantity);

        fgets(description, sizeof(description), file);
        trim_trailing_spaces(description);

        if(username[0] != '\n' && strcmp(username, current_user.username) == 0) {
            printf("%d. Category: \033[32m%s\033[0m\n", ++i, category);
            printf("\tPrice: \033[32m$%s\033[0m\n", price);
            printf("\tName Product: \033[32m%s\033[0m\n", nameProduct);
            printf("\tQuantity: \033[32m%s\033[0m\n", quantity);
            printf("\tDescription: \033[32m%s\033[0m\n", description);
        } 
        username[0] = '\n';
        category[0] = '\n';
        price[0] = '\n';
        quantity[0] = '\n';
        description[0] = '\n';
    }
    if(!i) {
        msg_error("No category found!\n");
    }
    printf("============END============\n\n");
    fclose(file);
    return i;
}
