#ifndef GAMEBOARD
#define GAMEBOARD

#include "LinkedList.h"
#include <vector>

class GameBoard {

public:
    GameBoard();
    ~GameBoard();

    // Getter
    std::vector<Tile::Colour> getCentreFactory();
    Tile::Colour getFactoryTile(int row, int column);
    LinkedList getTileBag();
    LinkedList getBoxLid();
    
private:
    /* data */
    std::vector<Tile::Colour> centreFactory;
    Tile::Colour factories[DIM][FACTORY_WIDTH];

    LinkedList tileBag;
    LinkedList boxLid;

    // Players

    // Initialise tile bag with a randomize set of tiles
    void initialiseTileBag();
};

#endif // GAMEBOARD