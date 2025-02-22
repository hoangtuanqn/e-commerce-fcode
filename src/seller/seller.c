#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/viewui.h"
int isExistCategory(char *categoryName) {
    FILE *file = fopen("data/Categories.txt", "r");
    if (file == NULL) {
        msgError("Error opening file!\n");
        return 0;
    }
    char category[100], username[100];
    while(!feof(file)) {
        fgets(username, sizeof(username), file);
        trimTrailingSpaces(username);
        
        fgets(category, sizeof(category), file);
        trimTrailingSpaces(category);
        // printf("1. %s %s %d %d\n", username, category, strlen(username), strlen(category));
        // printf("2. %s %s %d %d\n\n", currentUser.username, categoryName, strlen(currentUser.username), strlen(categoryName));

        // printf("Chieu dai cua username la: %s - %s - %d\n", username, currentUser.username, strcmp(username, currentUser.username));
        printf("Category là: %s - %s - %d\n", category, categoryName, strcmp(category, categoryName));  
        if (strcmp(category, categoryName) == 0 && strcmp(username, currentUser.username) == 0) {
            fclose(file);
            return 1;
        }
        // Read the last 2 lines
        fgets(username, sizeof(username), file);


    }
    fclose(file);
    return 0;
}
void handleAddCategory(char *categoryName) {
    if (isExistCategory(categoryName)) {
        msgError("Category already exists!\n");
        return;
    }
    FILE *file = fopen("data/Categories.txt", "a");
    if (file == NULL) {
        msgError("Error opening file!\n");
        return;
    }
    fclose(file);
    msgSuccess("Category added successfully!\n\n");
}

void viewAddCategory() {
    char categoryName[100];
    printf("\n========== Add Category ==========\n");
    printf("Enter category name: ");
    getchar();
    fgets(categoryName, sizeof(categoryName), stdin);
    handleAddCategory(categoryName);
}

void seller() {
    int choice;
    int pause = 0; // 1 là pause, 0 là không pause
    viewUISellerHeader();
    do {
        viewUISeller();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                viewAddCategory();
                break;
            case 2:
                return;
            default:
                msgError("Invalid choice!\n");
                printf("Enter your choice: ");
        }
    } while (!pause);

}

