#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/view_ui.h"
#include "../../includes/seller/view_all_category.h"
void view_delete_category() {
    system("cls");
    FILE *file = fopen("data/categories.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return;
    }
    char list_id[1000];
    getchar();
    view_all_category();
    printf("Enter the list of category id to delete: ");
    fgets(list_id, sizeof(list_id), stdin);
    char *token = strtok(list_id, " ");
    while (token != NULL) {
        int category_id = atoi(token);
        printf("Category ID to delete: %d\n", category_id); // Example action
        token = strtok(NULL, " ");
    }
    fclose(file);
}
   