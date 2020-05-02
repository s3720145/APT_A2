#ifndef PLAYER
#define PLAYER

#include <string>
#include "Tile.h"

#define ARRAY_DIM  5

using std::string;

class LinkedList;

class Player {
public:
    Player(string playerName);
    ~Player();

    // Returns playerName
    string getPlayerName();

    // Returns storage rows
    Tile::Colour& getStorage();

    // Returns the mosaic
    char& getMosaic();

    // Inserts a tile into the mosaic
    void InsertIntoMosaic(int row, Tile::Colour tile);

    /**
     * Inserts a tile into a storage row. user specifies the storage row the 
     * tile is inserted in. 
     * return false if insertion fails. This can happen when:
     *  -attempting to insert the tile into a row with non-matching coloured tiles
     *  -the row is full and no more tiles can be inserted
     * 
     * Must discuss which class is responsible for:
     *  -IF insertion fail you must place tile in the broken section
     *  -Cannot place tile into storage if that row already has a same colour tile in the mosaic
     * 
     * rowNumber MUST be >= 1 and <= 5
     */
    bool insertIntoStorage(int rowNumber, Tile::Colour tile);

    /**
     * Call at the end of a round. Checks all storage rows if they are full.
     * If a storage row is full, add the last tile in the row to the mosaic
     * place the rest in the box lid. 
     */
    void clearStorageRows(LinkedList& boxLid);

private:
    string playerName;

    Tile::Colour storage[ARRAY_DIM][ARRAY_DIM];

    char mosaic[ARRAY_DIM][ARRAY_DIM];
};

#endif // PLAYER