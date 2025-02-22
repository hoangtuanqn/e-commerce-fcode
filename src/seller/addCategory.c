#include <string.h>
#include <stdio.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/addCategory.h"

int isExistCategory(char *categoryName) {
    trimTrailingSpaces(categoryName);
    FILE *file = fopen("data/Categories.txt", "r");
    if (file == NULL) {
        msgError("Error opening file for reading!\n");
        return 0;
    }
    char category[100], username[100];
    while (!feof(file)) {
        fgets(username, sizeof(username), file);
        trimTrailingSpaces(username);
        
        fgets(category, sizeof(category), file);
        trimTrailingSpaces(category);

        if (strcmp(category, categoryName) == 0 && strcmp(username, currentUser.username) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int handleAddCategory(char *categoryName) {
    if(categoryName[0] == '\n') {
        msgError("Category name cannot be empty!\n\n");
        return 0;
    }
    if (isExistCategory(categoryName)) {
        msgError("Category already exists!\n\n");
        return 0;
    }
    FILE *file = fopen("data/Categories.txt", "a");
    if (file == NULL) {
        msgError("Error opening file for appending!\n");
        return 0;
    }
    fprintf(file, "%s\n%s\n", currentUser.username, categoryName); // Write username and category name
    fclose(file);
    msgSuccess("Category added successfully!\n\n");
    return 1;
}

void viewAddCategory() {
    char categoryName[100];
    int isSuccess = 0;
    do {
        printf("\n========== Add Category ==========\n");
        printf("Enter category name: ");
        getchar();
        fgets(categoryName, sizeof(categoryName), stdin);
        isSuccess = handleAddCategory(categoryName);
    } while (!isSuccess);
}