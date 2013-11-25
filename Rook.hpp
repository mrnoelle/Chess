#ifndef ROOK_H
#define ROOK_H

class Rook:public ChessPiece {
 public:
  Rook (string _name, string _colour);

  ~Rook();
  
  virtual bool validMove(string current, string next, ChessBoard* board);

};

#endif
