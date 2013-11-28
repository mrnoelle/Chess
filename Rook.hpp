#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.hpp"

class Rook:public ChessPiece {
 public:
  Rook (string piece_name, string piece_colour);

  ~Rook();
  
  virtual bool validMove(string current, string next, ChessBoard* board);

};

#endif
