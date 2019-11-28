#include "jblock.h"

using namespace std;

J_Block::J_Block(): PieceType{Xwindow::Magenta, 'J', new PieceCoords{vector<pair<int,int>>(make_pair(0,1), make_pair(0,0), make_pair(1,0), make_pair(2,0))}} {}
