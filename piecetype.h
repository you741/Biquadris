#ifndef PIECETYPE_H
#define PIECETYPE_H
#include <vector>
// #include <utility> 

enum class Colour { LightBlue, Red, Orange, Purple, Green, Yellow, DarkBlue };
enum class BlockType { I, Z, L, T, S, O, J };

class PieceType{
  protected:
    Colour colour;
    char sym;
    PieceCoords startingCoords;
  public:
    PieceType(Colour colour, char sym, PieceCoords startingCoords);
    PieceType getPieceType(BlockType b);
};
#endif
