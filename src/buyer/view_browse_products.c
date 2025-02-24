#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/buyer/view_ui.h"
int view_browse_products() {
    FILE *file = fopen("data/products.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return 0;
    }
    char username[100], category[100], nameProduct[100], price[100], quantity[100], description[100];
    msg_error("\n========== All Product ==========\n\n");
    int i = 0;
    while (!feof(file)) {
        fgets(username, sizeof(username), file);
        trim_trailing_spaces(username);
        if(username[0] == '\n') {
            continue;
        }

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


        printf("ID Product: \033[32m%d\033[0m\n", ++i);
        printf("->\tSeller: \033[32m%s\033[0m\n", username);
        printf("->\tCategory: \033[32m%s\033[0m\n", category);
        printf("->\tPrice: \033[32m$%s\033[0m\n", price);
        printf("->\tName Product: \033[32m%s\033[0m\n", nameProduct);
        printf("->\tQuantity in stock: \033[32m%s\033[0m\n", quantity);
        printf("->\tDescription: \033[32m%s\033[0m\n", description);
        printf("--------------------------------\n");
        username[0] = '\n';
        category[0] = '\n';
        price[0] = '\n';
        quantity[0] = '\n';
        description[0] = '\n';
    }
    if(!i) {
        msg_error("No category found!\n");
    }
    msg_error("\n============END============\n\n");
    fclose(file);
    return i;
}
