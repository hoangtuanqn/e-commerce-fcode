#include <string.h>
#include <ctype.h>

void trimTrailingSpaces(char *str) {
    int len = strlen(str);
    while (len > 0 && isspace(str[len - 1])) {
        len--;
    }
    str[len] = '\0';
}