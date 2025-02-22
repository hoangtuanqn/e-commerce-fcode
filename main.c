#include <stdio.h>
#include <string.h>
#include "includes/viewui.h"
#include "includes/global.h"
#include "includes/function.h"
#include "includes/register.h"
#include "includes/login.h"
#include "includes/seller/seller.h"

int main() {
    int choice;
    User user;
    // The user is not logged in
    do {
        viewUIStart();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerForm(&user);
                break;
            case 2:
                loginForm(&user);
                break;
            case 3:
                printf("Exit successfully\n");
                return 0;
            default:
                msgError("Invalid choice. Please try again. \n");
        }
    } while (is_logged_in == 0);

    // Logged in user
    if(is_logged_in) {
        switch (currentUser.accountType) {
            case 1:
                // viewUIBuyer();
                break;
            case 2:
                seller();
                break;
        }
    }
    return 0;
}
