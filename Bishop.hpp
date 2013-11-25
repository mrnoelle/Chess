#ifndef BISHOP_H
#define BISHOP_H

class Bishop: public ChessPiece {

 public:
  Bishop(string _name, string _colour);

  ~Bishop();

  virtual bool validMove(string current, string next, ChessBoard* board);
  
};

#endif
