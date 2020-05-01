#ifndef TILE
#define TILE

#define DIM  5
#define FACTORY_WIDTH 4
#define BAG_SIZE 100

namespace Tile {
    enum Colour {
        FirstPlayer,
        Red,
        Yellow,
        DarkBlue,
        LightBlue,
        Black,
        NoTile
    };

    const char getTileColourAsString(Colour colour);
}

#endif // TILE