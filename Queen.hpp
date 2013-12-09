#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.hpp"

class Queen: public ChessPiece 
{

 public:
  Queen(string piece_name, string piece_colour);
  
  ~Queen();
  
  virtual bool validMove(string src, string des, ChessBoard* board);

};

#endif
