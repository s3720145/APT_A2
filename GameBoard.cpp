#include "GameBoard.h"
#include <random>

GameBoard::GameBoard(std::string playerOneName, std::string playerTwoName) {
    
    // Fill the tile bag
    initialiseTileBag();

    // Add first player tile to the centre factory
    centreFactory.push_back(Tile::FirstPlayer);

    // Add tiles from the tile bag to the factories
    for (int i = 0; i < DIM; i++) {

       for (int j = 0; j < FACTORY_WIDTH; j++) {
           factories[i][j] = tileBag.dequeue()->getTileColour();
       }

    }

    // Initialise player mosaics
    playerOne = new Player(playerOneName);
    playerTwo = new Player(playerTwoName);
}

GameBoard::~GameBoard() {
    // Do something
}

void GameBoard::initialiseTileBag() {

    for (int i = 0; i < BAG_SIZE; i++) {
        // Get random number as a seed
        std::random_device randomNumber;
        // seed the mersenne twister engine
        std::mt19937 engine(randomNumber());
        //establish the range of values that the enum can be
        std::uniform_int_distribution<> range(1, Tile::NoTile-1);
        
        // Generate numbers and cast them into an enum type
        Tile::Colour randomTile = static_cast<Tile::Colour>(range(engine));
        tileBag.addBack(randomTile);
    }
    
}

std::vector<Tile::Colour> GameBoard::getCentreFactory() {
    return this->centreFactory;
}

Tile::Colour GameBoard::getFactoryTile(int row, int column) {
    return this->factories[row][column];
}

LinkedList GameBoard::getTileBag() {
    return this->tileBag;
}

LinkedList GameBoard::getBoxLid() {
    return this->boxLid;
}

