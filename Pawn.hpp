#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.hpp"

class Pawn: public ChessPiece {
private:
  bool firstMove;
  
 public:
  Pawn (string piece_name, string piece_colour, bool _firstMove);

  ~Pawn();
  
  virtual bool validMove(string current, string next, ChessBoard* board);
  
};

#endif
