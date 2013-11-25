#ifndef KING_H
#define KING_H

class King: public ChessPiece 
{

 public:
  King(string _name, string _colour);

  ~King();

  virtual bool validMove(string current, string next, ChessBoard* board);
  
};

#endif
