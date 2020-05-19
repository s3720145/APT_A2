#include "Player.h"
#include "LinkedList.h"
#include <iostream>
#include <fstream>
#include <cstring>

using std::cout;

// Default constructor
Player::Player(string playerName, int score) {
    this->playerName = playerName;
    this->totalScore = score;
    initialiseStructures();
}

Player::Player(const Player& other) {
    // TODO
}


Player::Player(Player&& other) {
    // TODO
}

Player::~Player() {
    // TODO
}

void Player::initialiseStructures() {
    // Initialises the storage rows to Tile::NoTile
    for(int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
        for(int col_num = 0; col_num <= row_num; ++col_num) {
            storage[row_num][col_num] = Tile::NoTile;
        }
    }

    // Places tile colours into an array so that we can iterate through the enums
    Tile::Colour colourArray[] = {Tile::DarkBlue, Tile::Yellow, Tile::Red, 
        Tile::Black, Tile::LightBlue};

    // Populates the mosaic using lowercase char representations of the enums
    for(int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
        for(int col_num = 0; col_num < ARRAY_DIM; ++col_num) {
            mosaic[row_num][col_num] = tolower(getTileColourAsString(colourArray[col_num]));
        }

        // After a row is filled the elements in the colourArray are shifted by one
        Tile::Colour temp = colourArray[ARRAY_DIM - 1];
        for(int i = ARRAY_DIM - 1; i >= 0; --i) {
            colourArray[i + 1] = colourArray[i];
        }
        colourArray[0] = temp;
    }
}

string Player::getPlayerName() const {
    return playerName;
}

void Player::setScore(const int totalScore) {
    this->totalScore = totalScore;
}

int Player::getScore() const {
    return totalScore;
}

void Player::setStorage(string inputStorage) {
    int stringCounter = 0;
    for(int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
        for(int col_num = row_num; col_num >= 0; --col_num) {
            int tileInt = (int) inputStorage[stringCounter];
            storage[row_num][col_num] = (Tile::Colour) tileInt;
            ++stringCounter;
        }
    }
}

Tile::Colour* Player::getStorageTile(const int row_num, const int col_num) {
    Tile::Colour* storageTileRef;
    if((row_num >= 0 && row_num < ARRAY_DIM) && (col_num >= 0 && col_num <= row_num)) {
        storageTileRef = &storage[row_num][col_num];
    } else {
        storageTileRef = nullptr;
    }
    return storageTileRef;
}

void Player::setMosaic(string inputMosaic) {
    int stringCounter = 0;
    for(int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
        for(int col_num = 0; col_num < ARRAY_DIM; ++col_num) {
            mosaic[row_num][col_num] = inputMosaic[stringCounter];
            ++stringCounter;
        }
    }
}

char* Player::getMosaicTile(const int row_num, const int col_num) {
    char* mosaicTileReference;
    if((row_num >= 0 && row_num < ARRAY_DIM) && (col_num >= 0 && col_num <= ARRAY_DIM)) {
        mosaicTileReference = &mosaic[row_num][col_num];
    } else {
        mosaicTileReference = nullptr;
    }
    return mosaicTileReference;
}

void Player::setBrokenTiles(string inputBroken) {
    int stringCounter = 0;
    int length = inputBroken.length();
    for(int i = 0; i < length; ++i) {
        int tileInt = (int) inputBroken[stringCounter];
        brokenTiles[i] = (Tile::Colour) tileInt;
        ++numBrokenTiles;
        ++stringCounter;
    }
}

Tile::Colour* Player::getBrokenTile(const int col_num) {
    Tile::Colour* brokenTileRef;
    if(col_num >= 0 && col_num < MAX_BROKEN_TILES) {
        brokenTileRef = &brokenTiles[col_num];
    } else {
        brokenTileRef = nullptr;
    }
    return brokenTileRef;
}

int Player::getPointPenalty() {
    int pointPenalty = 0;
    for(int i = 0; i < numBrokenTiles; ++i) {
        if(i < 2) {
            pointPenalty += 1;
        } else if(i > 2 && i < 5) {
            pointPenalty += 2;
        } else {
            pointPenalty += 3;
        }
    }

    return pointPenalty;
}

int Player::getNumBrokenTiles() {
    return numBrokenTiles;
}

void Player::printPlayerBoard() const {
    for(int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
        cout << row_num + 1 << ':';
        // Prints the storage rows
        for(int col_num = 1; col_num < ARRAY_DIM - row_num ; ++col_num) {
            cout << ' ';
        }
        for(int col_num = row_num; col_num >= 0; --col_num) {
            cout << getTileColourAsString(storage[row_num][col_num]);
        }

        // Prints the mosaic
        cout << "||";
        for(int col_num = 0; col_num < ARRAY_DIM; ++col_num) {
            cout << mosaic[row_num][col_num];
        }
        cout << std::endl;
    }
    cout << "broken: ";
    for(int i = 0; i <= numBrokenTiles - 1; ++i) {
        cout << getTileColourAsString(brokenTiles[i]);
    }
    cout << std::endl;

    cout << "Score this round: " << roundScore << std::endl;
}

// Also calculates score
void Player::insertIntoMosaic(const int row_num, const Tile::Colour tile) {
    for(int col_num = 0; col_num < ARRAY_DIM; ++col_num) {
        if(tolower(getTileColourAsString(tile)) == mosaic[row_num][col_num]) {
            mosaic[row_num][col_num] = toupper(mosaic[row_num][col_num]);
            int insertionScore = 1;

            int modifier = 1;
            // check right
            while(getMosaicTile(row_num, col_num + modifier) != nullptr && 
            isupper(mosaic[row_num][col_num + modifier]) == true) {
                ++modifier;
                ++insertionScore;
            }

            modifier = -1;
            // check left
            while(getMosaicTile(row_num, col_num + modifier) != nullptr && 
            isupper(mosaic[row_num][col_num + modifier]) == true) {
                --modifier;
                ++insertionScore;
            }
            
            modifier = 1;
            // check up
            while(getMosaicTile(row_num + modifier, col_num) != nullptr && 
            isupper(mosaic[row_num + modifier][col_num]) == true) {
                ++modifier;
                ++insertionScore;
            }

            modifier = -1;
            // check down
            while(getMosaicTile(row_num + modifier, col_num) != nullptr && 
            isupper(mosaic[row_num + modifier][col_num]) == true) {
                --modifier;
                ++insertionScore;
            }

            cout << insertionScore;
            roundScore += insertionScore;
        }
    }
}

bool Player::isInMosaicRow(const int row_num, Tile::Colour tile) {
    bool isInMosaic = false;
    /**
    for(int i = 0; i < ARRAY_DIM; ++i) {
        int tileInt = (int) toupper(mosaic[row_num][i]);
        Tile::Colour mosaicTile = (Tile::Colour) tileInt;
        if(getTileColourAsString(mosaicTile) == getTileColourAsString(tile)) {
            isInMosaic = true;
        }
    }
    */
    Tile::Colour colourArray[] = {Tile::Red, Tile::Yellow, Tile::DarkBlue, 
        Tile::LightBlue, Tile::Black};
        
    for(int i = 0; i < ARRAY_DIM; ++i) {
        int tileInt = (int) mosaic[row_num][i];
        // Check if it matches current enums
        for (Tile::Colour tile: colourArray) {
            if (tileInt == tile) {
                isInMosaic = true;
            }
        }
    }

    return std::move(isInMosaic);
}

// IF there are no more rows to insert in, place into storage
bool Player::insertIntoStorage(int row_num, const Tile::Colour tile) {
    bool insertSuccess = false;

    if(row_num >= 1 && row_num <= 5) {
        // breakLoop stops the for loop from continuing if insertion is successful
        bool breakLoop = false;

        /**
         * Iterate through the row and find a free spot. IF the row is full or there 
         * is another tile with non-matching colours, break loop. Also breaks if there is a same
         * colour tile already inserted into the mosaic
         */
        for(int col_num = 0; col_num < row_num && breakLoop == false; ++col_num) {
            // IF the tile being inserted is already in the mosaic row, break loop
            if (isInMosaicRow(row_num - 1, tile) == true) {
                breakLoop = true;
            }
            if(getTileColourAsString(storage[row_num - 1][col_num]) == '.') {
                storage[row_num - 1][col_num] = std::move(tile);
                insertSuccess = true;
                breakLoop = true;
            } else if(getTileColourAsString(tile) != getTileColourAsString(storage[row_num - 1][col_num])) {
                breakLoop = true;
            }

            // IF we cannot insert a tile because all rows are full, insert into broken tile array
            if(col_num == row_num - 1 && breakLoop == false) {
                insertIntoBrokenTiles(tile);
            }
        }
    }

    return std::move(insertSuccess);
}

void Player::clearStorageRows(LinkedList& boxLid) {
    // Checks all 5 rows in storage
    for(int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
        /**
         * Checks if row is full. If row is full, take the last element and
         * insert into mosaic. Discard the rest into the box lid. 
         */
        if(getTileColourAsString(storage[row_num][row_num]) != '.') {
            insertIntoMosaic(row_num, storage[row_num][row_num]);
            storage[row_num][row_num] = Tile::NoTile;

            for(int col_num = 0; col_num <= row_num - 1; ++col_num) {
                boxLid.addBack(storage[row_num][col_num]);
                storage[row_num][col_num] = Tile::NoTile;
            }
        }
    }

    // resets broken tile array
    for(int i = 0; i < numBrokenTiles; ++i) {
        boxLid.addBack(brokenTiles[i]);
        brokenTiles[i] = Tile::NoTile;
        numBrokenTiles = 0;
    }
}

// MUST OPTIMISE
void Player::insertIntoBrokenTiles(Tile::Colour tile) {
    // bool insertSuccess = false;
    // int index = 0;

    // while(brokenTiles[index] != Tile::NoTile && index < MAX_BROKEN_TILES) ++index;

    // if(index < MAX_BROKEN_TILES) {
    //     brokenTiles[index] = tile;
    //     insertSuccess = true;
    // } 

    brokenTiles[numBrokenTiles] = tile;
    ++numBrokenTiles;
}

bool Player::hasFullRow() {
    bool hasFullRow = false;
    bool breakLoop = false;

    // for each row in mosaic. breaks loop if full row is found
    for(int row_num = 0; row_num < ARRAY_DIM && breakLoop == false; ++row_num) {
        for(int col_num = 0; col_num < ARRAY_DIM && isupper(mosaic[row_num][col_num]) == true; ++col_num) {
            if(col_num == ARRAY_DIM - 1) {
                hasFullRow = true;
                breakLoop = true;
            }
        }
    }

    return hasFullRow;
}