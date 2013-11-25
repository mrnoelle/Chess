#ifndef QUEEN_H
#define QUEEN_H

class Queen: public ChessPiece 
{

 public:
  Queen(string _name, string _colour);
  
  ~Queen();
  
  virtual bool validMove(string current, string next, ChessBoard* board);

};

#endif
