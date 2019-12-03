#ifndef BOARD_STATE
#define BOARD_STATE

enum class StateType {BoardChange = 0, LevelChange, BlindChange, ScoreChange,
     PieceMoved, PieceDropped, NextPiece};


struct BoardState {
      StateType type;  // See above
};

#endif
