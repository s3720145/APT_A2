#include "Player.h"
#include "LinkedList.h"
#include <iostream>

Player::Player(string playerName) {
    this->playerName = playerName;

    // Initialises the storage rows to Tile::NoTile
    for(int row = 0; row < ARRAY_DIM; ++row) {
        for(int column = 0; column <= row; ++column) {
            storage[row][column] = Tile::NoTile;
        }
    }

    // Places tile colours into an array so that we can iterate through the enums
    Tile::Colour colourArray[] = {Tile::DarkBlue, Tile::Yellow, Tile::Red, 
        Tile::Black, Tile::LightBlue};

    // Populates the mosaic using lowercase char representations of the enums
    for(int row = 0; row < ARRAY_DIM; ++row) {
        for(int column = 0; column < ARRAY_DIM; ++column) {
            mosaic[row][column] = tolower(getTileColourAsString(colourArray[column]));
        }

        // After a row is filled the elements in the colourArray are shifted by one
        Tile::Colour temp = colourArray[ARRAY_DIM - 1];
        for(int index = ARRAY_DIM - 1; index >= 0; --index) {
            colourArray[index + 1] = colourArray[index];
        }
        colourArray[0] = temp;
    }

    // DEBUG
    // for(int row = 0; row < ARRAY_DIM; ++row) {
    //     for(int column = 0; column < ARRAY_DIM; ++column) {
    //         std::cout << mosaic[row][column];
    //     }
    //     std::cout << std::endl;
    // }
}

Player::~Player() {
    //TODO
}

string Player::getPlayerName() {
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

void Player::InsertIntoMosaic(int row, Tile::Colour tile) {
    for(int index = 0; index < ARRAY_DIM; ++index) {
        if(tolower(getTileColourAsString(tile)) == mosaic[row][index]) {
            // check if there is a way to uppercase chars TODO
            mosaic[row][index] = getTileColourAsString(tile);
        }
    }
}

bool Player::insertIntoStorage(int rowNumber, Tile::Colour tile) {
    // breakLoop stops the for loop from continuing if insertion is successful
    bool insertSuccess = false;
    bool breakLoop = false;

    // The loop will not run if the contract is not upheld
    if(rowNumber >= 1 && rowNumber <= 5) {
        // Iterate through the row and find a free spot. IF the row is full or there 
        // is another tile with non-matching colours, break loop
        for(int column = 0; column < rowNumber && breakLoop == false; ++column) {
            if(getTileColourAsString(storage[rowNumber - 1][column]) == '.') {
                storage[rowNumber - 1][column] = tile;
                insertSuccess = true;
                breakLoop = true;
            } else if(getTileColourAsString(tile) != getTileColourAsString(storage[rowNumber - 1][column])) {
                breakLoop = true;
            }
        }
    }

    return insertSuccess;
}

void Player::clearStorageRows(LinkedList& boxLid) {
    for(int row = 0; row < ARRAY_DIM; ++row) {
        // Checks if row is full. If row is full, take the last element and
        // insert into mosaic. Discard the rest into the box lid
        if(getTileColourAsString(storage[row][row]) != '.') {
            InsertIntoMosaic(row, storage[row][row]);
            storage[row][row] = Tile::NoTile;

            for(int column = 0; column <= row - 1; ++column) {
                boxLid.addBack(storage[row][column]);
                storage[row][column] = Tile::NoTile;
            }
        }
    }
}