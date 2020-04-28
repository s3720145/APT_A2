#include "Tile.h"

const char Tile::getTileColourAsString(Colour tileColour) {
    char colour = '\0';

    if (tileColour == Tile::FirstPlayer) {
        colour = 'F';
    }
    else if (tileColour == Tile::Red) {
        colour = 'R';
    }
    else if (tileColour == Tile::Yellow) {
        colour = 'Y';
    }
    else if (tileColour == Tile::DarkBlue) {
        colour = 'B';
    }
    else if (tileColour == Tile::LightBlue) {
        colour = 'L';
    }
    else if (tileColour == Tile::Black) {
        colour = 'U'; 
    }
    else if (tileColour == Tile::NoTile) {
        colour = '.';
    }

    return colour;
}
