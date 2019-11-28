#include "sblock.h"

using namespace std;

S_Block::S_Block(): PieceType{Xwindow::Red, 'S', new PieceCoords{vector<pair<int,int>>(make_pair(0,0), make_pair(1,0), make_pair(1,1), make_pair(2,1))}} {}
