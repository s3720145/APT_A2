#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <iostream>
#include <climits>
#include <string>

using std::cout;
using std::cin;
using std::exception;
using std::string;

class MainMenu {
public:
    MainMenu();
    ~MainMenu();

    void displayMenu();

private:

    // Starts a new game
    void newGame();

    // Resumes a game from a save file
    void loadGame();

    // Show student information
    void showCredits();

    // Quit the game
    void quit();
};

#endif // MAIN_MENU_H
