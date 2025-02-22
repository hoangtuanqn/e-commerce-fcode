#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/view_ui.h"
void view_all_category() {
    system("cls");
    FILE *file = fopen("data/categories.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }
    char username[100], category[100];
    printf("\n========== All Category ==========\n");
    int i = 0;
    while (!feof(file)) {
        fgets(username, sizeof(username), file);
        trim_trailing_spaces(username);
        fgets(category, sizeof(category), file);
        trim_trailing_spaces(category);
        if(username[0] != '\n' && strcmp(username, current_user.username) == 0) {
            printf("%d. \033[32m%s\033[0m\n", ++i, category);
        } 
        username[0] = '\n';
        category[0] = '\n';
    }
    printf("============END============\n\n");
    fclose(file);
}
