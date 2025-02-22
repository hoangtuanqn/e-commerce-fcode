#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../../includes/global.h"
#include "../../includes/function.h"
#include "../../includes/seller/viewui.h"
#include "../../includes/seller/addCategory.h"
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

