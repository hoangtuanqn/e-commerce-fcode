#ifndef GLOBAL_H
#define GLOBAL_H

extern void msgSuccess(char *message);
extern void msgError(char *message);
extern void msgCustom(char *message, char *color);
extern void trimTrailingSpaces(char *str);
extern int isEmailExists(const char *email);
extern int isPhoneExists(const char *phone);
#endif

