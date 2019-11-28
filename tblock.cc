#include "tblock.h"

using namespace std;

T_Block::T_Block(): PieceType{Xwindow::Brown, 'T', new PieceCoords{vector<pair<int,int>>(make_pair(0,1), make_pair(1,1), make_pair(2,1), make_pair(1,0))}} {}
