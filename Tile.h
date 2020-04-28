#ifndef TILE
#define TILE


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