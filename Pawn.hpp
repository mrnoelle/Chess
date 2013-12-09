#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.hpp"

class Pawn: public ChessPiece {


  
 public:
  Pawn (string piece_name, string piece_colour);

  ~Pawn();
  
  virtual bool validMove(string current, string next, ChessBoard* board);
  
};

#endif
