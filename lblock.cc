#include "lblock.h"

using namespace std;

L_Block::L_Block(): PieceType{Xwindow::DarkGreen, 'L', new PieceCoords{vector<pair<int,int>>(make_pair(0,0), make_pair(1,0), make_pair(2,0), make_pair(2,1))}} {}

