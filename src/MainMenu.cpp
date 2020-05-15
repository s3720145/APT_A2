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
    
    // Need to do end of game condition for every new round
    newRound(gameBoard);

}

void MainMenu::newRound(GameBoard* gameBoard) {
    cout << "=== Start Round ===" << "\n";
    
    // Player turns 
    do {
        currentPlayerTurn(gameBoard);
    } while (!(isEndOfRound(gameBoard)));
    
    // End of round

    // Player 1 transfer full row into mosaic 
    Player* playerOne = gameBoard->getPlayerOne();
    playerOne->clearStorageRows(*gameBoard->getBoxLid());
    // Player 2 transfer full row into mosaic 
    Player* playerTwo = gameBoard->getPlayerTwo();
    playerTwo->clearStorageRows(*gameBoard->getBoxLid());

    // Calculate points

    // Print player information
    playerOne->printPlayerBoard();
    playerTwo->printPlayerBoard();

    // Reset centre factory
    gameBoard->getCentreFactory().clear();
    // Refill
    gameBoard->initialiseFactories();
    
    cout << endl;
}

void MainMenu::currentPlayerTurn(GameBoard* gameBoard) {
    cout << "TURN FOR PLAYER: " << gameBoard->getCurrentPlayer()->getPlayerName();
    cout << endl;

    printFactories(gameBoard);

    printCurrentPlayerMozaic(gameBoard);

    string userTurn;
    std::vector<string> userTurnArray;
    std::vector<Tile::Colour> chosenTiles;
    int storageRow = 0;

    // Valid Rule check
    bool turnIsValid = false;
    do {
        // Complete argument error check
        do {
            userTurn = playerInput();
        } while (!(userTurnErrorCheck(userTurn, userTurnArray)));
        
        // Get commands
        int factory = std::stoi(userTurnArray.at(0))-1;
        string tileColour = userTurnArray.at(1);
        storageRow = std::stoi(userTurnArray.at(2));

        // Get tile/s from centre factory
        if (factory == -1) {
            for (Tile::Colour currentTile: gameBoard->getCentreFactory()) {
                if (Tile::getTileColourAsString(currentTile) == tileColour[0]) {
                    // Add correct tiles to temp vector
                    chosenTiles.push_back(currentTile);
                }
            }

        } // Otherwise get tiles from other factories
        else {
            for (int j = 0; j < FACTORY_WIDTH; j++) {
                Tile::Colour currentTile = gameBoard->getFactoryTile(factory, j);
                
                if (Tile::getTileColourAsString(currentTile) == tileColour[0]) {
                    // Add correct tiles to temp vector
                    chosenTiles.push_back(currentTile);
                }
            }
        }
        
        // First turn check
        if (gameBoard->isFirstTurn() && factory == -1) {
            cout << "Can't choose the centre factory on the first turn" << endl;
            userTurnArray.clear();
            chosenTiles.clear();
        } // Null check
        else if (chosenTiles.empty()) {
            cout << "No Tiles match your option. Try Again" << endl;
            userTurnArray.clear();
        } // Check first element for rule check
        else if (gameBoard->getCurrentPlayer()->insertIntoStorage(storageRow, chosenTiles.front())) {
            // Removed from temporary vector
            chosenTiles.pop_back();
            // Adjust the factories to reflect the valid move
            if (factory == -1) {
                // Check if first element is first player
                if (gameBoard->getCentreFactory().front() == Tile::FirstPlayer) {
                    // Insert into broken tiles
                    gameBoard->getCurrentPlayer()->insertIntoBrokenTiles(Tile::FirstPlayer);
                    gameBoard->getCentreFactory().erase(gameBoard->getCentreFactory().begin());
                }
                for (int i = 0; i < gameBoard->getCentreFactory().size(); i++) {
                    Tile::Colour currentTile = gameBoard->getCentreFactory()[i];
                    if (Tile::getTileColourAsString(currentTile) == tileColour[0]) {
                        gameBoard->getCentreFactory()[i] = Tile::NoTile;
                    }
                    
                }
                
                cout << endl;
            }
            else {
                for (int j = 0; j < FACTORY_WIDTH; j++) {
                    Tile::Colour currentTile = gameBoard->getFactoryTile(factory, j);
                    
                    if (Tile::getTileColourAsString(currentTile) == tileColour[0]) {
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
            }
            
            // No game rules violated
            turnIsValid = true;
            cout << "Turn successful" << endl;
        }
        else {
            cout << "Storage row has a different tile or mozaic already contains tile. Try Again" << endl;
            // Reset chosen tiles
            chosenTiles.clear();
            userTurnArray.clear();
        }
    } while (!(turnIsValid));
    
    // Add to players mozaic with storage row
    for (Tile::Colour tile: chosenTiles) {
        // If true tile will be added to the correct storage row
        if (gameBoard->getCurrentPlayer()->insertIntoStorage(storageRow, tile)) {
            // Removed from temporary vector
            chosenTiles.pop_back();
        } 
        else { // Otherwise add to broken tiles
            gameBoard->getCurrentPlayer()->insertIntoBrokenTiles(tile);
            // Removed from temporary vector
            chosenTiles.pop_back();
        }
    }

    cout << endl;

    // Change current player
    gameBoard->switchCurrentPlayer();
}

string MainMenu::playerInput() {
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
            if (!(factoryAsInt >= 0 && factoryAsInt <= 5) || !(storageAsInt >= 1 && storageAsInt <= 5)) {
                noErrors = false;
                userTurnArray.clear();
                cout << "You must enter an integer between 0 and 5 for factories" << endl;
                cout << "You must enter an integer between 1 and 5 for storage" << endl;
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
        if (Tile::getTileColourAsString(tile) != '.') {
            cout << Tile::getTileColourAsString(tile);
        }
    }
    cout << endl;
    
    // Print other factories
    for (int i = 0; i < DIM; i++) {
        cout << (i+1) << ": ";
        for (int j = 0; j < FACTORY_WIDTH; j++) {
            Tile::Colour tile = gameBoard->getFactoryTile(i, j);
            if (Tile::getTileColourAsString(tile) != '.') {
                cout << Tile::getTileColourAsString(gameBoard->getFactoryTile(i, j));
            }
        }
        cout << endl;
    }
}

bool MainMenu::isEndOfRound(GameBoard* gameBoard) {
    bool isEmpty = false;

    // Check centre factory
    bool isCentreFactoryEmpty = true;
    for (int i = 0; i < gameBoard->getCentreFactory().size() && isCentreFactoryEmpty == true; i++) {

        Tile::Colour currentTile = gameBoard->getCentreFactory()[i];
        if (Tile::getTileColourAsString(currentTile) != '.') {
            isCentreFactoryEmpty = false;
        }
        
    }

    bool areFactoriesEmpty = true;
    // Loop through 2d factories array 
    // breakLoop stops the for loop from continuing if it contains a tile colour
    bool breakLoop = false;
    for (int i = 0; i < DIM && breakLoop == false; i++) {
        for (int j = 0; j < FACTORY_WIDTH && breakLoop == false; j++) {

            Tile::Colour currentTile = gameBoard->getFactoryTile(i, j);
            if (Tile::getTileColourAsString(currentTile) != '.') {
                areFactoriesEmpty = false;
                breakLoop = true;
            }

        }
    }
    
    if (isCentreFactoryEmpty && areFactoriesEmpty) {
        cout << "=== END OF ROUND ===" << endl;
        isEmpty = true;
    }
    
    return isEmpty;
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