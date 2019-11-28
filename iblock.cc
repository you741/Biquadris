#include "iblock.h"

using namespace std;

I_Block::I_Block(): PieceType{Xwindow::Orange, 'I', new PieceCoords{vector<pair<int,int>>(make_pair(0,0), make_pair(1,0), make_pair(2,0), make_pair(3,0))}} {}
