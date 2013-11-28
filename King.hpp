#ifndef KING_H
#define KING_H


#include "ChessPiece.hpp"

class King: public ChessPiece 
{

 public:
  King(string piece_name, string piece_colour);

  ~King();

  virtual bool validMove(string src, string des, ChessBoard* board);
  
};

#endif
