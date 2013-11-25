#ifndef PAWN_H
#define PAWN_H


class Pawn: public ChessPiece {
private:
  bool firstMove;
  
 public:
  Pawn (string _name, string _colour, bool _firstMove);

  ~Pawn();
  
  virtual bool validMove(string current, string next, ChessBoard* board);
  
};

#endif
