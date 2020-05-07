#ifndef PLAYER
#define PLAYER

#include <string>
#include "Tile.h"

#define ARRAY_DIM           5
#define NUM_BROKEN_TILES    7

using std::string;

class LinkedList;

class Player {
public:
    // DEFAULT costructor for a new game
    Player(string playerName, int score);
    // COPY constructor
    Player(const Player& other);
    // MOVE constructor
    Player(Player&& other);
    ~Player();

    /**
     * Initialises the mosaic and storage ADTs. Only initialised
     * once which is when the constructor is called.
     */
    void initialiseStructures();

    // Returns playerName.
    string getPlayerName() const;

    void setScore(const int score);

    int getScore() const;

    void setStorage(char* inputStr[]);

    // Returns a reference of the storage rows.
    Tile::Colour& getStorage();

    void setMosaic(string inputMosaic);

    // Returns a reference of the mosaic.
    char& getMosaic();

    // Prints the player's mosaic and storage rows.
    void printPlayerBoard() const;

    // Inserts a tile into the mosaic.
    void InsertIntoMosaic(const int row, const Tile::Colour tile);

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
    bool insertIntoStorage(const int row_num, const Tile::Colour tile);

    /**
     * Call at the end of each round for each player. Checks all storage rows if they are full.
     * If a storage row is full, add the last tile in the row to the mosaic
     * place the rest in the box lid. 
     */
    void clearStorageRows(LinkedList& boxLid);

    bool insertIntoBrokenTiles(Tile::Colour tile);

private:
    string playerName;

    int score;

    // Storage rows on the left-hand side of the player's mosaic
    Tile::Colour storage[ARRAY_DIM][ARRAY_DIM];

    // Player mosaic 
    char mosaic[ARRAY_DIM][ARRAY_DIM];

    // Player broken tiles
    Tile::Colour brokenTiles[NUM_BROKEN_TILES];
};

#endif // PLAYER