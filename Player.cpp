#include "Player.h"
#include "LinkedList.h"
#include <iostream>

using std::cout;

Player::Player(string playerName) {
    this->playerName = playerName;
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

Tile::Colour& Player::getStorage() {
    Tile::Colour& storageRef = storage[0][0];
    return storageRef;
}

char& Player::getMosaic() {
    char& mosaicRef = mosaic[0][0];
    return mosaicRef;
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
            std::cout << mosaic[row_num][col_num];
        }
        cout << std::endl;
    }
}

void Player::InsertIntoMosaic(const int row_num, const Tile::Colour tile) {
    for(int i = 0; i < ARRAY_DIM; ++i) {
        if(tolower(getTileColourAsString(tile)) == mosaic[row_num][i]) {
            mosaic[row_num][i] = toupper(mosaic[row_num][i]);
        }
    }
}

bool Player::insertIntoStorage(int row_num, const Tile::Colour tile) {
    bool insertSuccess = false;

    if(row_num >= 1 && row_num <= 5) {
        // breakLoop stops the for loop from continuing if insertion is successful
        bool breakLoop = false;

        /**
         * Iterate through the row and find a free spot. IF the row is full or there 
         * is another tile with non-matching colours, break loop
         */
        for(int col_num = 0; col_num < row_num && breakLoop == false; ++col_num) {
            if(getTileColourAsString(storage[row_num - 1][col_num]) == '.') {
                storage[row_num - 1][col_num] = std::move(tile);
                insertSuccess = true;
                breakLoop = true;
            } else if(getTileColourAsString(tile) != getTileColourAsString(storage[row_num - 1][col_num])) {
                breakLoop = true;
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
         * insert into mosaic. Discard the rest into the box lid
         */
        if(getTileColourAsString(storage[row_num][row_num]) != '.') {
            InsertIntoMosaic(row_num, storage[row_num][row_num]);
            storage[row_num][row_num] = Tile::NoTile;

            for(int col_num = 0; col_num <= row_num - 1; ++col_num) {
                boxLid.addBack(storage[row_num][col_num]);
                storage[row_num][col_num] = Tile::NoTile;
            }
        }
    }
}