#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../includes/global.h"
void trim_trailing_spaces(char *str) {
    int len = strlen(str);
    while (len > 0 && isspace(str[len - 1])) {
        len--;
    }
    str[len] = '\0';
}
void msg_success(char *message) {
    printf("\033[32m%s\033[0m", message);
}
void msg_error(char *message) {
    printf("\033[31m%s\033[0m", message);
}
void msg_bold(char *message) {
    printf("\033[1m%s\033[0m", message);
}
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  
    int i = (low - 1);  

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}


void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // GỌI HÀM partition()
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}
char *check_name_category(int category_id) {
    FILE *file = fopen("data/categories.txt", "r");
    if (file == NULL) {
        msg_error("Error opening file for reading!\n");
        return NULL;
    }
    char username[100], category[100];
    int cnt = 0;
    while (fgets(username, sizeof(username), file) != NULL && fgets(category, sizeof(category), file) != NULL) {
        trim_trailing_spaces(username);
        trim_trailing_spaces(category);
        if (strcmp(username, current_user.username) == 0) {
            ++cnt;
        }
        if (cnt == category_id) {
            fclose(file);
            return strdup(category); // Use strdup to return a dynamically allocated copy of the category
        }
    }
    fclose(file);
    return NULL;
}