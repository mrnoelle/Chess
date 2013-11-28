#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.hpp"

class Bishop: public ChessPiece {

 public:
  Bishop(string piece_name, string piece_colour);

  ~Bishop();

  virtual bool validMove(string src, string des, ChessBoard* board);
  
};

#endif
