#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../includes/global.h"

int is_logged_in = 0; //= 0 là chưa login, = 1 là đã login
int is_pause_program = 0; //= 0 là không pause, = 1 là pause
const int MAX_PRODUCTS = 1000;
User current_user;
