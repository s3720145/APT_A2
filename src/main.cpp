#include <iostream>

#include "MainMenu.h"

#define EXIT_SUCCESS 0

int main() {
    MainMenu menu;

    try {
        menu.displayMenu();
    }
    catch(...) {
        menu.~MainMenu();
    }

    return EXIT_SUCCESS;
}