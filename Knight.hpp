#ifndef KNIGHT_H
#define KNIGHT_H

class Knight: public ChessPiece {

 public:
  Knight (string _name, string _colour);

  ~Knight();
  
  virtual bool validMove(string current, string next, ChessBoard* board);
  
};

#endif
