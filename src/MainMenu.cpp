#include "MainMenu.h"
#include "Player.h"
#include "LinkedList.h"
#include "tests/playerUnitTests/PlayerTests.h"

using std::cout;
using std::cin;
using std::exception;
using std::string;
using std::endl;

MainMenu::MainMenu() {
    /**
    PlayerTests* playerTests = new PlayerTests();
    playerTests->~PlayerTests();
    */
}

MainMenu::~MainMenu() {

}

void MainMenu::displayMenu(int seed) {
    cout << "Menu" << '\n' << "----" << '\n'
    << "1. New Game" << '\n'
    << "2. Load Game" << '\n'
    << "3. Credits (Show student information)" << '\n'
    << "4. Quit" << '\n' << "> ";

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
        newGame(seed);
    } else if(userInput == 2) {
        loadGame();
    } else if(userInput == 3) {
        showCredits(seed);
    } else {
        quit();
    }
}

void MainMenu::newGame(int seed) {
    cout << "Starting a New Game" << "\n\n";
    cout << "Enter a name for player 1" << "\n> ";
    string playerOneName;
    cin >> playerOneName;

    cout << endl;

    cout << "Enter a name for player 2" << "\n> ";
    string playerTwoName;
    cin >> playerTwoName;

    cout << "\n\n";
    cout << "Let's Play" << "\n\n";

    GameBoard* gameBoard = new GameBoard(playerOneName, playerTwoName, seed);
    newRound(gameBoard);
}

void MainMenu::newRound(GameBoard* gameBoard) {
    cout << "=== Start Round ===" << "\n";
    cout << "TURN FOR PLAYER: " << gameBoard->getCurrentPlayer()->getPlayerName();
    cout << endl;

    printFactories(gameBoard);

    printCurrentPlayerMozaic(gameBoard);

    string userTurn;
    std::vector<string> userTurnArray;

    // Complete error check
    do {
        userTurn = playerTurn();
    } while (!(userTurnErrorCheck(userTurn, userTurnArray)));

    
    // Get commands
    int factory = std::stoi(userTurnArray.at(0))-1;
    string tileColour = userTurnArray.at(1);
    int storageRow = std::stoi(userTurnArray.at(2));

    
    std::vector<Tile::Colour> chosenTiles;
    // Get tile/s from factory
    for (int j = 0; j < FACTORY_WIDTH; j++) {
        Tile::Colour currentTile = gameBoard->getFactoryTile(factory, j);
        
        if (Tile::getTileColourAsString(currentTile) == tileColour[0]) {
            // Add correct tiles to temp vector
            chosenTiles.push_back(currentTile);
            // set to no tile in factory 
            gameBoard->setFactoryTile(Tile::NoTile, factory, j);
        }
        else {
            // Add to centre factory
            gameBoard->getCentreFactory().push_back(currentTile);
            // set to no tile in factory 
            gameBoard->setFactoryTile(Tile::NoTile, factory, j);
        }
    }
    
    
    // Add to players mozaic with storage row
    for (Tile::Colour tile: chosenTiles) {
        // If true tile will be added to the correct storage row
        if (gameBoard->getCurrentPlayer()->insertIntoStorage(storageRow, tile)) {
            // Removed from temporary vector
            chosenTiles.pop_back();
        } // Otherwise add to broken tiles
        else {
            cout << gameBoard->getCurrentPlayer()->insertIntoBrokenTiles(tile);
        }
    }

    cout << endl;

    // Test
    printFactories(gameBoard);
    printCurrentPlayerMozaic(gameBoard);
    

    cout << endl;
}

string MainMenu::playerTurn() {
    string userTurn;
    // current player turn
    cout << "> turn ";
    
    getline(cin >> std::ws, userTurn);
    return userTurn;
}

bool MainMenu::userTurnErrorCheck(string userTurn, std::vector<string>& userTurnArray) {
    
    bool noErrors = true;
    
    size_t pos = 0;
    string token;

    // Split the string into a vector
    string delimiter = " ";

    while ((pos = userTurn.find(delimiter)) != string::npos) {
        token = userTurn.substr(0, pos);
        userTurnArray.push_back(token);
        userTurn.erase(0, pos + delimiter.length());
    }
    userTurnArray.push_back(userTurn);

    // Check for argument number error
    if (userTurnArray.size() != 3) {
        noErrors = false;
        userTurnArray.clear();
        cout << "Incorrect number of arguments" << endl;
        cin.clear();
    }  // Check for argument type error
    else {
        // Get commands
        string factory = userTurnArray.at(0);
        string tileColour = userTurnArray.at(1);
        string storageRow = userTurnArray.at(2);
        
        // Check conversion to an int
        bool factoryIsAnInt = (factory.find_first_not_of("0123456789") == string::npos);
        bool storageIsAnInt = (storageRow.find_first_not_of("0123456789") == string::npos);

        // Check Tile::Colour match
        Tile::Colour colourArray[] = {Tile::Red, Tile::Yellow, Tile::DarkBlue, 
        Tile::LightBlue, Tile::Black};

        bool tileMatch = false;
        for (Tile::Colour tile: colourArray) {
            if (Tile::getTileColourAsString(tile) == tileColour[0]) {
                tileMatch = true;
            }
        }

        if (factoryIsAnInt == false || storageIsAnInt == false) {
            noErrors = false;
            userTurnArray.clear();
            cout << "You must enter an integer between 1 and 5" << endl;
            cin.clear();
        }
        else if (tileMatch == false) {
            noErrors = false;
            userTurnArray.clear();
            cout << "You must provide the correct tile colour" << endl;
            cin.clear();
        }
        else { // Check if numbers are between 1 and 5
            int factoryAsInt = std::stoi(factory);
            int storageAsInt = std::stoi(storageRow);
            if (!(factoryAsInt >= 1 && factoryAsInt <= 5) || !(storageAsInt >= 1 && storageAsInt <= 5)) {
                noErrors = false;
                userTurnArray.clear();
                cout << "You must enter an integer between 1 and 5" << endl;
                cin.clear();
            }
        }
    }
    
    return noErrors;
}

void MainMenu::printFactories(GameBoard* gameBoard) {
    // Print centre Factory
    cout << "Factories:" << endl;
    cout << "0: ";
    for (Tile::Colour tile: gameBoard->getCentreFactory()) {
        cout << Tile::getTileColourAsString(tile);
    }
    cout << endl;
    
    // Print other factories
    for (int i = 0; i < DIM; i++) {
        cout << (i+1) << ": ";
        for (int j = 0; j < FACTORY_WIDTH; j++) {
            // do check for no tile Tile
            cout << Tile::getTileColourAsString(gameBoard->getFactoryTile(i, j));
        }
        cout << endl;
    }
}

void MainMenu::printCurrentPlayerMozaic(GameBoard* gameBoard) {
    // Print current player mozaic
    cout << "Mozaic for " << gameBoard->getCurrentPlayer()->getPlayerName() << ":" << endl;
    for (int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
        cout << row_num + 1 << ": ";
        // Prints the storage rows
        for(int col_num = 1; col_num < ARRAY_DIM - row_num ; ++col_num) {
            cout << ' ';
        }
        for(int col_num = row_num; col_num >= 0; --col_num) {
            cout << Tile::getTileColourAsString(*gameBoard->getCurrentPlayer()->getStorageTile(row_num, col_num));
        }

        // Prints the mosaic
        cout << "||";
        
        for(int col_num = 0; col_num < ARRAY_DIM; ++col_num) {
            cout << *gameBoard->getCurrentPlayer()->getMosaicTile(row_num, col_num);
        }
        
        cout << std::endl;
    }
    
    // Print broken tiles
    cout << "broken: ";
    for (int i = 0; i <= gameBoard->getCurrentPlayer()->getNumBrokenTiles() - 1; ++i) {
        cout << Tile::getTileColourAsString(*gameBoard->getCurrentPlayer()->getBrokenTile(i));
    }
    cout << endl;
}

void MainMenu::loadGame() {
    // TODO
}

void MainMenu::showCredits(int seed) {
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

    displayMenu(seed);
}

void MainMenu::quit() {
    throw exception();
}