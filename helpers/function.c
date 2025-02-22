#include <string.h>
#include <ctype.h>

void trimTrailingSpaces(char *str) {
    int len = strlen(str);
    while (len > 0 && isspace(str[len - 1])) {
        len--;
    }
    str[len] = '\0';
}
void msgSuccess(char *message) {
    printf("\033[32m%s\033[0m", message);
}
void msgError(char *message) {
    printf("\033[31m%s\033[0m", message);
}

