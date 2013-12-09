#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.hpp"

class Knight: public ChessPiece 
{

 public:
  Knight (string piece_name, string piece_colour);

  ~Knight();
  
  virtual bool validMove(string src, string des, ChessBoard* board);
  
};

#endif
