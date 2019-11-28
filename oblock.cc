#include "oblock.h"

using namespace std;

O_Block::O_Block(): PieceType{Xwindow::Green, 'O', new PieceCoords{vector<pair<int,int>>(make_pair(0,0), make_pair(1,0), make_pair(1,1), make_pair(0,1))}} {}
