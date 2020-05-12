#include "GameBoard.h"
#include <random>

GameBoard::GameBoard(std::string playerOneName, std::string playerTwoName, int seed) {
    // Initialise data structure
    tileBag = new LinkedList();
    boxLid = new LinkedList();

    // Initialise player mosaics
    playerOne = new Player(playerOneName, 1);
    playerTwo = new Player(playerTwoName, 2);
    
    // Fill the tile bag
    initialiseTileBag(seed);

    // Add first player tile to the centre factory
    centreFactory.push_back(Tile::FirstPlayer);

    // Add tiles from the tile bag to the factories
    for (int i = 0; i < DIM; i++) {

        for (int j = 0; j < FACTORY_WIDTH; j++) {
            factories[i][j] = tileBag->dequeue()->getTileColour();
        }

    }

}

GameBoard::GameBoard(std::vector<Tile::Colour> centreFactory) {
    // Initialise data structure
    tileBag = new LinkedList();
    boxLid = new LinkedList();
    
    // Centre factory
    this->centreFactory = centreFactory;

}

GameBoard::~GameBoard() {
    delete playerOne;
    delete playerTwo;
    delete tileBag;
    delete boxLid;
}

void GameBoard::initialiseTileBag(int seed) {

    for (int i = 0; i < BAG_SIZE; i++) {
        // seed the mersenne twister engine
        std::mt19937 engine(seed++);
        //establish the range of values that the enum can be
        std::uniform_int_distribution<> range(1, Tile::NoTile-1);
        
        // Generate numbers and cast them into an enum type
        Tile::Colour randomTile = static_cast<Tile::Colour>(range(engine));
        tileBag->addBack(randomTile);
    }
    
}

std::vector<Tile::Colour> GameBoard::getCentreFactory() {
    return this->centreFactory;
}

Tile::Colour GameBoard::getFactoryTile(int row, int column) {
    return this->factories[row][column];
}

void GameBoard::setFactoryTile(Tile::Colour tile, int row, int column) {
    this->factories[row][column] = tile;
}

LinkedList* GameBoard::getTileBag() {
    return this->tileBag;
}

void GameBoard::setTileBagElement(Tile::Colour tile) {
    this->tileBag->addBack(tile);
}

LinkedList* GameBoard::getBoxLid() {
    return this->boxLid;
}

void GameBoard::setBoxLidElement(Tile::Colour tile) {
    this->boxLid->addBack(tile);
}

