#include "MainMenu.h"
#include "Player.h"
#include "LinkedList.h"

using std::cout;
using std::cin;
using std::exception;
using std::string;

MainMenu::MainMenu() {
    
}

MainMenu::~MainMenu() {

}

void MainMenu::displayMenu() {
    cout << "Menu" << '\n' << "----" << '\n'
    << "1. New Game" << '\n'
    << "2. Load Game" << '\n'
    << "3. Credits (Show student information)" << '\n'
    << "4. Quit" << '\n' << "> " << '\n';

    int userInput;

    while (!(cin >> userInput) || userInput < 1 || userInput > 4) {
        if(cin.eof()) {
            quit();
        } else {
            cout << "Incorrect input - please try again: ";
            cin.clear();
            cin.ignore(INT_MAX,'\n');
        }
    }

    if(userInput == 1) {
        newGame();
    } else if(userInput == 2) {
        loadGame();
    } else if(userInput == 3) {
        showCredits();
    } else {
        quit();
    }
}

void MainMenu::newGame() {
    // TODO
}

void MainMenu::loadGame() {
    // TODO
}

void MainMenu::showCredits() {
    struct student {
        string name;
        string studentId;
        string eMail;
    };

    student students[] = {
        {"Marco Pereira Barros", "s3379774", "s3379774@student.rmit.edu.au"},
        {"Ivan Cedric Tomas Bulosan", "s3720145", "s3720145@student.rmit.edu.au"},
        {"Adama Fofana", "s3640426", "s3640426@student.rmit.edu.au"}
    };

    for (student student : students) {
        cout << student.name << '\n'
        << student.name << '\n'
        << student.name << '\n'
        << "----------------- \n";
    }

    displayMenu();
}

void MainMenu::quit() {
    throw exception();
}