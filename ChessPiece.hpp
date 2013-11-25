#ifndef CHESSPIECE_H
#define CHESSPIECE_H

class ChessBoard;

class ChessPiece 
{

 protected:
  string name;
  string colour;
  int file_change;
  int rank_change;

 public:
 
  ChessPiece(string _name, string _colour);
  ~ChessPiece();

  string getName() const;
  string getColour() const;
  
  virtual bool validMove(string current, string next, ChessBoard* board)=0;
  
};


#endif
