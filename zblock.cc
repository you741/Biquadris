#include "zblock.h"

using namespace std;

Z_Block::Z_Block(): PieceType{Xwindow::Cyan, 'Z', new PieceCoords{vector<pair<int,int>>(make_pair(1,0), make_pair(0,1), make_pair(1,1), make_pair(2,0))}} {}
