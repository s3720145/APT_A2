#ifndef GAMEBOARD
#define GAMEBOARD

#include "LinkedList.h"
#include "Player.h"
#include <vector>

class GameBoard {

public:
    GameBoard(std::string playerOneName, std::string playerTwoName, int seed);
    GameBoard(std::vector<Tile::Colour> centreFactory);
    ~GameBoard();

    // Getter
    std::vector<Tile::Colour> getCentreFactory();
    Tile::Colour getFactoryTile(int row, int column);
    LinkedList* getTileBag();
    LinkedList* getBoxLid();

    // Setter
    void setFactoryTile(Tile::Colour tile, int row, int column);
    void setTileBagElement(Tile::Colour tile);
    void setBoxLidElement(Tile::Colour tile);
    
private:
    /* data */
    std::vector<Tile::Colour> centreFactory;
    Tile::Colour factories[DIM][FACTORY_WIDTH];

    LinkedList* tileBag;
    LinkedList* boxLid;

    // Players
    Player* playerOne;
    Player* playerTwo;

    // Initialise tile bag with a randomize set of tiles
    void initialiseTileBag(int seed);
};

#endif // GAMEBOARD